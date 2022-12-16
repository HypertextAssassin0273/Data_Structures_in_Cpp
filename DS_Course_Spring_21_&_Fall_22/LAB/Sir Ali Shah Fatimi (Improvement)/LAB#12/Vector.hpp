/* Custom Vector Class (same as minimal STL::vector) */
/* Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Elements are mapped/constructed on dynamically allocated buffer (by using 'placement new' operator)
	3) Perfect container for other classes & itself (i.e. 2D,3D,... Nested Vector)
	4) All neccessary STL Vector class 'modifiers' & 'iterators' are provided
	5) Supports 'LIFO' stack order operations.
*/
#ifndef VECTOR_GUARD
#define VECTOR_GUARD 1

#include "Swap.hpp"
#include "Iterator.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class Vector{
	typedef Vector __V;
	typedef unsigned char u_char;
	
	/* Private Member Attributes */
	size_t _size, _capacity;
	u_char *data;//data-buffer on heap
public:
	static const unsigned int max_capacity=~((unsigned int)0);//range: 0 to 4,294,967,295 (upto 10 digits)
	//Tip: negate the min. value of any predefined datatype (in unsigned format) to get its max. range
	
	/* Constructors & Assignment Operators */
#if __cplusplus >= 201103L
	template<typename... _T>
	Vector(size_t n=0, _T&&... attributes)noexcept://default & emplaced fill ctor
		_size(0), _capacity(n>max_capacity?throw:n),
		data(new u_char[sizeof(T)*_capacity]){//allocating new data-buffer
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T(std::forward<_T>(attributes)...);//perfect forwarding
	}
	/*Note: always perform perfect forwarding with universal reference '_T&&',
			in order to implement 'reference collapsing rules' efficiently */
#else
	Vector(size_t n=0, const T& value=T())://default & fill ctor
		_size(0), _capacity(n>max_capacity?throw:n), data(new u_char[sizeof(T)*_capacity]){
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T(value);
	}//Note: T() invokes default ctor of type 'T' & returns it as rvalue
#endif
	//copy semantics (rule of three):
	Vector(const __V& other)noexcept://(deep) copy ctor
		_size(0), _capacity(other._capacity), data(new u_char[sizeof(T)*_capacity]){
			while(_size<other._size)
				new(data+sizeof(T)*_size++) T(other[_size]);
	}
	__V& operator=(const __V& other)noexcept{//(deep) copy assignment operator
		if(this!=&other){//self-assignment protection
 			clear();//1) clear existing resources
 	 		delete[] data;
 	 		data=new u_char[sizeof(T)*(_capacity=other._capacity)];
 			for(_size=0;_size<other._size;++_size)//2) constructing & copying resource from 'other'
				new(data+sizeof(T)*_size) T(other[_size]);
		}
		return *this;
 	}
 	
#if __cplusplus >= 201103L
	//move semantics (rule of five):
 	Vector(__V&& other)noexcept://move (shallow copy) ctor
  		data(other.data), _size(other._size), _capacity(other._capacity){//1) steal other's data
		other.data=nullptr;//2) set other's ptrs to null state
  		other._size=other._capacity=0;
  		//Note: use "-fno-elide-constructors" flag to disable compiler optimization for 'move ctor' (GCC Compilers)
	}
	__V& operator=(__V&& other)noexcept{//move (shallow copy) assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			delete[] data;
  			data=other.data;//2) steal other's data
  			_size=other._size;
  			_capacity=other._capacity;
  			other.data=nullptr;//3) set other's ptrs to null state
  			other._size=other._capacity=0;
  		}
		return *this;
	}
	
	//move initializer_list ctor (works best for r-values):
	template<typename _T, size_t N>
	Vector(_T (&&list)[N])noexcept://Note: _T(&&)[N] is not an array of universal_references
		_size(0), _capacity((N>max_capacity)?throw:N), data(new u_char[sizeof(T)*_capacity]){
		for(;_size<N;++_size)
			new(data+sizeof(T)*_size) T(std::move(list[_size]));//elements of list are move constructed
	}
#endif
	//type convertor:
	Vector(u_char *new_data, size_t new_size, size_t new_capacity)noexcept://special move ctor
		_size(new_size), _capacity(new_capacity), data(new_data){}
	/* Note: set the source pointer to null state after pointing 'data' buffer to resource
	   Warning: use this ctor only for moving resource of current pointed type only! */
	
 	/* Accessors */
	T& operator[](size_t n){ return *(T*)(data+sizeof(T)*n); }//gives read & write both access
	const T& operator[](size_t n)const{ return *(T*)(data+sizeof(T)*n); }//gives only read access
	
	T* operator+(size_t n){ return (T*)(data+sizeof(T)*n); }//returns address of nth first pointed element
	const T* operator+(size_t n)const{ return (T*)(data+sizeof(T)*n); }
	
	T* operator-(size_t n){ return (T*)(data+sizeof(T)*(_size-1-n)); }//returns address of nth last pointed element
	const T* operator-(size_t n)const{ return (T*)(data+sizeof(T)*(_size-1-n)); }
	
	T& front(){ return *(T*)data; }
	const T& front()const{ return *(T*)data; }
	
	T& back(){ return *(T*)(data+sizeof(T)*(_size-1)); }
	const T& back()const{ return *(T*)(data+sizeof(T)*(_size-1)); }
	
	T& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if (n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(_size-1-n):n));
	}
	const T& at(size_t n, bool df=false)const{
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(_size-1-n):n));
	}
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'size()==true' for 'front' & 'back' accessors.
		2) use condition 'n<size()' for '[]', '+' & '-' operator accessors.
	 Side Note:
		- passing -ve index means getting illegal memory access, hence
		  all random accessors have unsigned index parameter.
	*/
	
	size_t size()const{ return _size; }
 	size_t capacity()const{ return _capacity; }
 	
 	/* Desicion Checking Methods */
	bool full()const{ return _size==_capacity; }
	bool empty()const{ return !_size; }
	
	/* Modifiers */
private:
	bool reallocate(size_t n){//Note: must remain 'private' since it's a helper function (containing depandant workflows)
		if(n>max_capacity) return true;
		u_char* new_data=new u_char[sizeof(T)*n];
		for(size_t i=0;i!=_size;++i){
		#if __cplusplus >= 201103L
			new(new_data+sizeof(T)*i) T(std::move(*(T*)(data+sizeof(T)*i)));//move construction
			//Note: 'std::move' is used to convert lvalue-resources to rvalues
		#else
			new(new_data+sizeof(T)*i) T(*(T*)(data+sizeof(T)*i));//copy construction (slower process)
		#endif
			((T*)(data+sizeof(T)*i))->~T();
			//explicit dtor call for manually destruct previously stored obj from data-buffer
		}
		delete[] data; data=new_data; _capacity=n;
		return false;
	}
public:
	void push_back(const T& value){
    	if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
			//if capacity is '0' then set it to '1' else twice it
    	new(data+sizeof(T)*_size++) T(value);
	}
#if __cplusplus >= 201103L//methods with rvalue direct construction support
	template<typename... _T>
	void emplace_back(_T&&... attrbs){//more efficient (as direct object initialization is possible)
    	if(_size==_capacity)
    		if(reallocate(_capacity?_capacity*2:1)) return;
    	new(data+sizeof(T)*_size++) T(std::forward<_T>(attrbs)...);
	}
	template<typename _T>
	void insert(_T&& value, size_t n=0){//O(N-n) complexity [similar to: push_front (when n=0)]
		if(n>_size) return;//bound exception safety check
		if(n==_size){ emplace_back(std::forward<_T>(value)); return; }
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		//if not empty or equal to nth index, then perform shifting upto nth index:
		new(data+sizeof(T)*_size) T(std::move(back()));//move construct last value to new last position
		for(size_t i=_size-1;i>n;--i)//shifting values upwards (starting from old last position)
			swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i-1)));
		*(T*)(data+sizeof(T)*n)=std::forward<_T>(value);//insert new value at nth index
		++_size;
	}
#else
	void insert(const T& value, size_t n=0){
		if(n>_size) return;
		if(n==_size){ push_back(value); return; }
		if(_size>=_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		new(data+sizeof(T)*_size) T(back());//copy construct last value to new last position
		for(size_t i=_size-1;i>n;--i)//shifting values upwards
			swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i-1)));
		*(T*)(data+sizeof(T)*n)=value;
		++_size;
	}
#endif
	void pop_back(){
		if(_size)
			((T*)(data+sizeof(T)*--_size))->~T();//explicit dtor call
		/*Note: we can destruct objects of 'T' type that are mapped on data-buffer
				by simply type-casting the buffer to object's pointer type */
	}
	void erase(size_t n=0){//O(N-n) complexity [similar to: pop_front (when n=0)]
		if(n>=_size) return;//if not empty, then perform shifting from nth index
		--_size;//swapping needs to be N-1 times [N=total_values_before_shifting] 
		for(size_t i=n;i<_size;++i)//shifting values downwards (upto new last position)
			swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i+1)));
		((T*)(data+sizeof(T)*_size))->~T();//remove/destruct last value
	}
	void clear(){
		while(_size)
			((T*)(data+sizeof(T)*--_size))->~T();
	}
	void reserve(size_t n){
		if(n>_capacity) reallocate(n);
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void resize(size_t n, _T&&... attrbs){//emplaced_resize
		if(n>_capacity)
			if(reallocate(n)) return;
	    while(_size<n)//construct till it reaches 'n'
    		new(data+sizeof(T)*_size++) T(std::forward<_T>(attrbs)...);
     	while(_size>n)//destruct till it reaches 'n'
			((T*)(data+sizeof(T)*--_size))->~T();
	}
#else
	void resize(size_t n, const T& value=T()){
		if(n>_capacity)
			if(reallocate(n)) return;
	    while(_size<n)
    		new(data+sizeof(T)*_size++) T(value);
    	while(_size>n)
			((T*)(data+sizeof(T)*--_size))->~T();
	}
#endif
	void shrink_to_fit(){//opppsite to reserve modifier
		if(_size<_capacity) reallocate(_size);
	}
	
	/* Comparators */
	bool operator==(const __V& other)const{
		if(_size!=other._size) return false;
		for(size_t i=0;i<_size;++i)
    		if(*(T*)(data+sizeof(T)*i)!=*(T*)(other.data+sizeof(T)*i))
      			return false;
  		return true;
	}
	bool operator!=(const __V& other)const{ return !(*this==other); }
	
	bool operator<(const __V& other)const{//follows lexicographical-order (Dictionary order)
  		size_t i=0;
  		for(;i!=_size;++i){
  			if(i==other._size||*(T*)(other.data+sizeof(T)*i)<*(T*)(data+sizeof(T)*i))
  				return false;
  			else if(*(T*)(data+sizeof(T)*i)<*(T*)(other.data+sizeof(T)*i))
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const __V& other)const{ return other<*this; }
	bool operator<=(const __V& other)const{ return !(other<*this); }
	bool operator>=(const __V& other)const{ return !(*this<other); }
	
	/* Iterators */
 	//available vector iterator objects (const/non_const):
 	typedef Iterator<T> iterator;
 	typedef Iterator<const T> const_iterator;
 	
 	typedef Reverse_Iterator<T> r_iterator;
 	typedef Reverse_Iterator<const T> const_r_iterator;
 	
 	//available vector iterator methods (return rvalue/temporary iterator):
	iterator begin(){ return iterator((T*)data); }//points to first element
	iterator end(){ return iterator((T*)data+_size); }//points to next position after last element
	
	const_iterator begin()const{ return const_iterator((T*)data); }//const (read only) version
	const_iterator end()const{ return const_iterator((T*)data+_size); }
    
	r_iterator rbegin(){ return r_iterator((T*)data+_size-1); }//points to last element
	r_iterator rend(){ return r_iterator((T*)data-1); }//points to previous position before first element
	
	const_r_iterator rbegin()const{ return const_r_iterator((T*)data+_size-1); }//const (read only) version
	const_r_iterator rend()const{ return const_r_iterator((T*)data-1); }
	
	/* Overloaded 'cout & cin' Methods */
	friend std::ostream& operator<<(std::ostream& out,const __V& self){
		for(unsigned int i=0;i<self._size;++i)
			out<<*(T*)(self.data+sizeof(T)*i)<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,__V& self){
		in.sync();//clears remaining content from buffer
		for(size_t i=0;i<self._size;++i)
			in>>*(T*)(self.data+sizeof(T)*i);
		return in;
	}
	
	~Vector(){//dtor
		clear();
		delete[] data;
	}

#if TYPE_CONVERTORS_GUARD
	friend class convert;
#endif
};

#endif
