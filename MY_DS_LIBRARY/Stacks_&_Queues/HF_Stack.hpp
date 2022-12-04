/* Important Notes:
	1) only offered in C++11 & higher versions (since its performance heavily relies on move-semantics).
	2) uses 'object mapping technique' for saving extra inital value construction cost
 	   & allows us to destruct objects in stack when not in use.
 	   [ref: 'mapping objects' with 'placement new operator' in c++]
	3) '(T*)(data+sizeof(T)*n)' returns address of mapped object 'T' at 'n' index.
	4) this version of stack has slight disadvantage in term of accessing speed as compare to F_Stack
	   since, it is located inside heap, instead of stack-memory.
	
*/
#ifndef HF_STACK_GUARD
#define HF_STACK_GUARD 1

#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#include "../Utilities/Swap.hpp"
#include "../Utilities/Iterator.hpp"
#include "../Utilities/Reverse_Iterator_Adapter.hpp"

template<typename T, size_t _capacity=1>
class HF_Stack{//Heap {based} Fixed {Size} Stack (LIFO order)
	typedef HF_Stack __HFS;
	typedef unsigned char u_char;
	
	/* private member attributes */
	size_t current;//current index {ptr}
	u_char *data;//data buffer on heap
public:
	/* default constructor */
	template<typename... _T>
	HF_Stack(size_t n=0, _T&&... attributes)noexcept://also works as emplaced fill ctor
		data(new u_char[_capacity*sizeof(T)]),//allocates memory for 'N' elements in bytes on heap data buffer
		current(n>_capacity?throw:0){
		while(current<n)
			new(data+sizeof(T)*current++) T(std::forward<_T>(attributes)...);//perfect forwarding
	}
	
	/* copy semantics (performs deep copy for stored values) */
	HF_Stack(const __HFS& other)noexcept://copy ctor
		current(0), data(new u_char[_capacity*sizeof(T)]){//initializing respective resources
			while(current<other.current)
				new(data+sizeof(T)*current++) T(other[current]);//copy constructing values from 'other'
	}
	__HFS& operator=(const __HFS& other)noexcept{//copy assignment operator
		if(this!=&other){//self-assignment protection
			clear(); delete[] data;//clear existing resources
			data=new u_char[sizeof(T)*_capacity];//allocate new buffer
			for(current=0;current<other.current;++current)
				new(data+sizeof(T)*current) T(other[current]);//copy constructing values from 'other'
		}
		return *this;
 	}
 	
 	/* move semantics (performs shallow copy for stored values) */
	HF_Stack(__HFS&& other)noexcept://move ctor
		current(other.current), data(other.data){//steal others's data
		other.data=nullptr;	other.current=0;//set others's data to null state
	}
	__HFS& operator=(__HFS&& other)noexcept{//move assignment operator
		if(this!=&other){//self-assignment protection
			clear(); delete[] data;//clear existing resources
			data=other.data; current=other.current;//steal other's data
			other.data=nullptr;	other.current=0;//set others's data to null state
		}
		return *this;
 	}
 	
	/* move initializer_list constructor (works best for r-values) */
 	template<typename _T, size_t N>
	HF_Stack(_T (&&list)[N])noexcept://Note: _T(&&)[N] is not an array of universal_references
		current(N>_capacity?throw:0), data(new u_char[sizeof(T)*_capacity]){
		for(;current<N;++current)
			new(data+sizeof(T)*current) T(std::move(list[current]));//elements of list are move constructed
	}
	
	/* special move constructor (for type conversion) */
	HF_Stack(u_char *new_data, size_t new_current)noexcept:
		current(new_current), data(new_data){}
	/* Note: set the source pointer to null state after pointing 'data' buffer to resource
	   Warning: use this ctor only for moving resource of current pointed type only! */
	
	/* accessors (getters & setters) */
	size_t size()const{ return current; }
	size_t capacity()const{ return _capacity; }
	
	T& peek(){ return *(T*)(data+sizeof(T)*(current-1)); }//gives read & write both access
	const T& peek()const{ return *(T*)(data+sizeof(T)*(current-1)); }//gives read access only
	
	T& operator[](size_t n){ return *(T*)(data+sizeof(T)*n); }
	const T& operator[](size_t n)const{ return *(T*)(data+sizeof(T)*n); }
	
	T* operator+(size_t n){ return (T*)(data+sizeof(T)*n); }//returns address of nth first pointed element
	const T* operator+(size_t n)const{ return (T*)(data+sizeof(T)*n); }
	
	T* operator-(size_t n){ return (T*)(data+sizeof(T)*(current-1-n)); }//returns address of nth last pointed element
	const T* operator-(size_t n)const{ return (T*)(data+sizeof(T)*(current-1-n)); }
	
	T& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if (n>=current){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(current-1-n):n));
	}
	const T& at(size_t n, bool df=false)const{
		if (n>=current){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(current-1-n):n));
	}
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'size()==true' for 'peek' accessor.
		2) use condition 'n<size()' for '[]', '+' & '-' operator accessors.
	  Side Note:
		- passing -ve index means getting illegal memory access, hence
		  all random accessors have unsigned index parameter.
	*/
	
	/* desicion checking methods */
	bool full()const{ return current==_capacity; }
	bool empty()const{ return !current; }
	
	/* stack general operations (modifiers) */
	template<typename... types>
	void push(types&&... values){//O(1) complexity, Note: types&&... == universal_references
		if(current!=_capacity)
			new(data+sizeof(T)*current++) T(std::forward<types>(values)...);
			//constructing mapped_object format: new(memory_address) type_ctor();
	}//Note: this method can also be used to emplace/construct objects directly
	
	template<typename _T>
	void insert(_T&& value, size_t n=0){//O(N-n) complexity [similar to: push_front (when n=0)]
		if(n==current){ push(std::forward<_T>(value)); return; }
		if(n>current||current==_capacity) return;//exception safety checks
		//if not empty or equal to nth index, then perform shifting upto nth index:
		new(data+sizeof(T)*current) T(std::move(peek()));//move construct last value to new last position
		for(size_t i=current-1;i>n;--i)//shifting values downwards (starting from old last position)
			swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i-1)));
		*(T*)(data+sizeof(T)*n)=std::forward<_T>(value);//insert new value at nth index
		++current;
	}
	void pop(){//O(1) complexity
		if(current)
			((T*)(data+sizeof(T)*--current))->~T();//explicit dtor call
	}
	void erase(size_t n=0){//O(N-n) complexity [similar to: pop_front (when n=0)]
		if(n>=current) return;//if not empty, then perform shifting from nth index
		--current;//swapping needs to be N-1 times [N=total_values_before_shifting] 
		for(size_t i=n;i<current;++i)//shifting values upwards (upto new last position)
			swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i+1)));
		((T*)(data+sizeof(T)*current))->~T();//remove/destruct last value
	}
	void clear(){
		while(current)
			((T*)(data+sizeof(T)*--current))->~T();
	}
	
	/* comparators */
	bool operator==(const __HFS& other)const{
		if(current!=other.current) return false;
		for (size_t i=0;i<current;++i)
    		if (*(T*)(data+sizeof(T)*i)!=*(T*)(other.data+sizeof(T)*i))
      			return false;
  		return true;
	}
	bool operator!=(const __HFS& other)const{ return !(*this==other); }
	
	bool operator<(const __HFS& other)const{//follows lexicographical-order (Dictionary order)
  		size_t i=0;
  		for (;i!=current;++i){
  			if(i==other.current||*(T*)(other.data+sizeof(T)*i)<*(T*)(data+sizeof(T)*i))
  				return false;
  			else if(*(T*)(data+sizeof(T)*i)<*(T*)(other.data+sizeof(T)*i))
  				return true;
		}
		return i!=other.current;
	}
    bool operator>(const __HFS& other)const{ return other<*this; }
	bool operator<=(const __HFS& other)const{ return !(other<*this); }
	bool operator>=(const __HFS& other)const{ return !(*this<other); }
	
	/* Iterators */
 	//available fixed-size stack iterator objects (const/non-const):
 	typedef Iterator<T> iterator;
 	typedef Iterator<const T> const_iterator;
 	
 	typedef Reverse_Iterator<T> r_iterator;
 	typedef Reverse_Iterator<const T> const_r_iterator;
 	
 	//available fixed-size stack iterator methods (return rvalue/temporary iterator):
	iterator begin(){ return iterator((T*)data); }//points to first element
	iterator end(){ return iterator((T*)data+current); }//points to last element
	
	const_iterator begin()const{ return const_iterator((T*)data); }//const (read only) version
	const_iterator end()const{ return const_iterator((T*)data+current); }
    
	r_iterator rbegin(){ return r_iterator((T*)data+current-1); }//points to last element
	r_iterator rend(){ return r_iterator((T*)data-1); }//points to first element
	
	const_r_iterator rbegin()const{ return const_r_iterator((T*)data+current-1); }//const (read only) version
	const_r_iterator rend()const{ return const_r_iterator((T*)data-1); }
	
	//reversely traverse fixed-size stack using these methods (inside range-based loop):
	reverse_iterator_adapter<__HFS, r_iterator> r_iterator_adapter(){ 
		return reverse_iterator_adapter<__HFS, r_iterator>(*this);
	}
	reverse_iterator_adapter<const __HFS, const_r_iterator> r_iterator_adapter()const{
		return reverse_iterator_adapter<const __HFS, const_r_iterator>(*this);
	}
	
	/* overloaded 'cout & cin' methods */
	friend std::ostream& operator<<(std::ostream& out, const __HFS& self){
		for(size_t i=0;i<self.current;++i)
			out<<*(T*)(self.data+sizeof(T)*i)<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __HFS& self){//updates existing values
		in.sync();//clears remaining content from buffer
		for(size_t i=0;i<self.current;++i)
			in>>*(T*)(self.data+sizeof(T)*i);
		return in;
	}
	
	/* destructor */
	~HF_Stack(){ clear(); delete[] data; }

#if TYPE_CONVERTORS_GUARD
	friend class convert;
#endif
};

#endif

#endif
