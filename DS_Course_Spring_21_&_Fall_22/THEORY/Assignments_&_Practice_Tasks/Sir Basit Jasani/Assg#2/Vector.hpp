#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

/* Custom Vector Class (minimal STL Vector) */
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Elements are mapped/constructed on dynamically allocated buffer (i.e. use of 'placement new' operator)
	3) Safe when accessing elements with accessors (Exception somewhat handled)
	4) Perfect container for other classes & itself (i.e. 2D,3D,... Nested Vector)
	5) All neccessary STL Vector class 'modifiers' & 'iterators' are provided
*/
#ifndef VECTOR_GUARD
#define VECTOR_GUARD 1

#if !ITERATOR_GUARD
#include"Iterator.hpp"
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class Vector{
	typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	typedef unsigned char __uchar;
	
	static const __uint32 max_capacity=~((__uint32)0);
	//Tip: negate the min. value with extension (by typecasting) to get max. of any predefined datatype.
	__uint32 _size,_capacity;
	__uchar *data;//i.e. data-buffer on heap
	
public:
	Vector(__uint64 n=0)noexcept://i.e. default ctor
		_size(0),_capacity((n>max_capacity)?throw:n),data(new __uchar[sizeof(T)*_capacity]){//i.e. allocating new buffer 'data'
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T();
		/*Note: empty-brackets initializes primitives with '0','\0',"\0" & for non-primitives,
				it invokes default ctors */
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	Vector(__uint64 n,_T&&... val)noexcept://i.e. emplaced ctor for initializing whole vector with given value
		_size(0),_capacity((n>max_capacity)?throw:n),data(new __uchar[sizeof(T)*_capacity]){
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T(val...);
	}
#else
	Vector(__uint64 n,const T& val)noexcept:
		_size(0),_capacity((n>max_capacity)?throw:n),data(new __uchar[sizeof(T)*_capacity]){
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T(val);
	}
#endif
#if __cplusplus >= 201103L
	Vector(const std::initializer_list<T>& list)noexcept://i.e. ctor for initializer-list (C++11 Construct)
		_size(0),_capacity(list.size()),data(new __uchar[sizeof(T)*_capacity]){
		for(const auto& it:list)//i.e. initializer_list can only be traversed with iterators
			new(data+sizeof(T)*_size++) T(it);//i.e. performs copy of list iterator's elements
	}
#endif
	Vector(const Vector& other)noexcept://i.e. copy ctor
		_size(0),_capacity(other._capacity),data(new __uchar[sizeof(T)*_capacity]){
			while(_size<other._size)
				new(data+sizeof(T)*_size++) T(other[_size]);
	}
	Vector& operator=(const Vector& other)noexcept{//i.e. copy assignment func
		if(this==&other)//i.e. self-assignment protection
			return *this;
 		clear();//1) clear existing resources
  		delete[] data;
  		data=new __uchar[sizeof(T)*other._capacity];
 		for(__uint64 i=0;i<other._size;++i)//2) constructing & copying resource from 'other'
			new(data+sizeof(T)*i) T(other[i]);
 		_size=other._size;
 		_capacity=other._capacity;
	 	return *this;
 	}
#if __cplusplus >= 201103L
 	Vector(Vector&& other)noexcept://i.e. move ctor (C++11 Construct)
  		data(other.data),_size(other._size),_capacity(other._capacity){//1) steal other's data
		other.data=nullptr;//2) set other's ptr to null state
  		other._size=other._capacity=0;
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	Vector& operator=(Vector&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		delete[] data;
  		data=other.data;//2) steal other's data
  		_size=other._size;
  		_capacity=other._capacity;
  		other.data=nullptr;//3) set other to null state
  		other._size=other._capacity=0;
  		return *this;
	}
#endif
	
 	/*i.e. Accessors */
	T& operator[](__uint32 n)const{//i.e. gives read & write both access
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*n);
	}
	T* operator+(__uint32 n)const{//i.e. returns address of current pointed element (stored in 'data' buffer)
		if (n>=_size){
			cout<<"\nError: Given Index is Out of Bound!\n";
	 		throw false;
		}
		return (T*)(data+sizeof(T)*n);
		//Note: use with '*' operator to access elements of 'data' buffer, i.e. cout<<*(vec+2);
	}
	T& front()const{
		if (_size)
			return *(T*)data;
		throw false;
	}
	T& back()const{
		if (_size)
			return *(T*)(data+sizeof(T)*(_size-1));
		throw false;
	}
	__uint32 size()const{ return _size; }
 	__uint32 capacity()const{ return _capacity; }
	
	/*i.e. Modifiers */
	bool empty()const{ return _size?false:true; }
private:
	void reallocate(__uint64 n){
		__uchar* new_data=new __uchar[sizeof(T)*n];
		for(__uint64 i=0;i<(sizeof(T)*_size);++i)
			new_data[i]=data[i];//i.e. copying buffer (byte by byte)
		/*Note: 
			->this saves us from extra constructions & destructions
			->also copies ptr addresses, so no loss for non-P.O.D mapped objs */
		
		/*Alternate for copying objs (slower process): */
//		for(__uint64 i=0;i<_size;++i)//i.e. constructing & copying resource from 'other'
//				new(new_data+sizeof(T)*i) T(*(T*)(data+sizeof(T)*i));
//		for(__uint64 i=0;i<_size;++i)//i.e. destroying previously stored objs from 'data' buffer
//			((T*)(data+sizeof(T)*i))->~T();
		delete[] data;
		data=new_data;
	}
public:
#if __cplusplus >= 201103L
	void push_back(T&& val){
		if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
			//i.e. if capacity is '0' then set it to '1' else twice it
    	new(data+sizeof(T)*_size++) T(move(val));
	}
#endif
	void push_back(const T& val){
    	if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
    	new(data+sizeof(T)*_size++) T(val);
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void emplace_back(_T&&... val){//i.e. more efficient (as direct obj initialization is possible)
    	if(_size>=_capacity)
    		reallocate(_capacity?_capacity*=2:++_capacity);
    	new(data+sizeof(T)*_size++) T(std::forward<_T>(val)...);
	}
#endif
	void pop_back(){
		if(_size)
			((T*)(data+sizeof(T)*--_size))->~T();
	}
	void clear(){
		while(_size)
			((T*)(data+sizeof(T)*--_size))->~T();//i.e. explicit dtor call
		/*Note: we can destruct objects of 'T' type that are mapped on buffer 'data'
				by simply type-casting the buffer to object's ptr type */
	}
	bool reserve(__uint64 n){
		if(n>max_capacity)
			return false;
		if(n>_capacity)
			reallocate(_capacity=n);
		return true;
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void resize(__uint64 n,_T&&... val){//i.e. emplaced_resize
#else
	void resize(__uint64 n,const T& val=T()){
#endif
		if(n>_size&&reserve(n))
	    	while(_size<_capacity)
	    	#if __cplusplus >= 201103L
    			new(data+sizeof(T)*_size++) T(val...);
    		#else
    			new(data+sizeof(T)*_size++) T(val);
    		#endif
    	else
			while(n<_size)
			((T*)(data+sizeof(T)*--_size))->~T();
	}
	void shrink_to_fit(){//i.e. opppsite to reserve func
		if(_size<_capacity)
   	 	    reallocate(_capacity=_size);
	}
	
	/*i.e. Comparison Operators */
	bool operator==(const Vector& other)const{
		if(other._size<_size)
			return false;
		for (__uint64 i=0;i<_size;++i)
    		if (*(T*)(data+sizeof(T)*i)!=*(T*)(other.data+sizeof(T)*i))
      			return false;
  		return true;
	}
	bool operator!=(const Vector& other)const{ return !(*this==other); }
	
	bool operator<(const Vector& other)const{//i.e. follows lexicographical-order (Dictionary order)
  		__uint64 i=0;
  		for (;i!=_size;++i){
  			if(i==other._size||*(T*)(other.data+sizeof(T)*i)<*(T*)(data+sizeof(T)*i))
  				return false;
  			else if(*(T*)(data+sizeof(T)*i)<*(T*)(other.data+sizeof(T)*i))
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const Vector& other)const{ return other<*this; }

 	/*i.e. Iterators */
 	typedef Iterator<T> iterator;
 	typedef Reverse_Iterator<T> r_iterator;
 	
	iterator begin()const{ return iterator((T*)data); }//i.e. points to first element
	iterator end()const{ return iterator((T*)data+_size); }//i.e. points to last element
    r_iterator rbegin()const{ return r_iterator((T*)data+_size-1); }//i.e. points to last element
	r_iterator rend()const{ return r_iterator((T*)data-1); }//i.e. points to first element
	//Note: these func return rvalue/temporary iterator objs
#if __cplusplus >= 201103L
	struct reverse_adapter{//i.e. defined to use reverse_iterator directly on 'range-based' loop
	reverse_adapter(const Vector& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const Vector& ref;
	};
	//i.e. reversely traverse vector inside range-based loop
	reverse_adapter reverse_iterator()const{ return reverse_adapter(*this); }
#endif
	
	/* Overloaded 'cin/cout' Methods */
	friend ostream& operator<<(ostream& out,const Vector& vec){
		for(unsigned int i=0;i<vec._size;++i)
			out<<*(T*)(vec.data+sizeof(T)*i)<<" ";
		return out;
	}
	friend istream& operator>>(istream& in,Vector& vec){
		vec.clear();
		in.sync();//i.e. clears remaining content from buffer
		for(T temp;vec._size<vec._capacity;++vec._size){
			in>>temp;
		#if __cplusplus >= 201103L
			new(vec.data+sizeof(T)*vec._size) T(move(temp));
		#else
			new(vec.data+sizeof(T)*vec._size) T(temp);
		#endif
		}
		return in;
	}
	
	~Vector(){//i.e. dtor
		clear();
		delete[] data;
	}
};
#endif
