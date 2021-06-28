#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

/* Custom Vector Class (minimal STL Vector) */

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
	Vector(__uint64 n,const T& val)noexcept://i.e. ctor for initializing whole vector with given value
		_size(0),_capacity((n>max_capacity)?throw:n),data(new __uchar[sizeof(T)*_capacity]){
		while(_size<_capacity)
			new(data+sizeof(T)*_size++) T(val);
	}
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
	
 	/*i.e. Accessors */
	T& operator[](__uint32 n)const{//i.e. gives read & write both access
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*n);
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
private:
	void reallocate(__uint64 n){
		__uchar* new_data=new __uchar[sizeof(T)*n];
		for(__uint64 i=0;i<(sizeof(T)*_size);++i)
			new_data[i]=data[i];//i.e. copying buffer (byte by byte)
		delete[] data;
		data=new_data;
	}
public:
    void push_back(const T& val){//i.e. stack order: LILO
    	if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
			//i.e. if capacity is '0' then set it to '1' else twice it
    	new(data+sizeof(T)*_size++) T(val);
	}
	T pop_back(){
		if(_size)
			return *(T*)(data+sizeof(T)*--_size);
	}
	void clear(){ _size=0; }
	bool reserve(__uint64 n){
		if(n>max_capacity)
			return false;
		if(n>_capacity)
			reallocate(_capacity=n);
		return true;
	}
	void resize(__uint64 n,const T& val=T()){
		if(n>_size&&reserve(n))
	    	while(_size<_capacity)
    			new(data+sizeof(T)*_size++) T(val);
    	else if(n<_size)
			_size=n;
	}
	void shrink_to_fit(){//i.e. opppsite to reserve func
		if(_size<_capacity)
   	 	    reallocate(_capacity=_size);
	}

 	/*i.e. Iterators */
 	typedef Iterator<T> iterator; 
	typedef Reverse_Iterator<T> r_iterator;
	
	iterator begin()const{ return iterator((T*)data); }//i.e. points to first element
	iterator end()const{ return iterator((T*)data+_size); }//i.e. points to last element
    r_iterator rbegin()const{ return r_iterator((T*)data+_size-1); }//i.e. points to last element
	r_iterator rend()const{ return r_iterator((T*)data-1); }//i.e. points to first element
	//Note: these func return rvalue/temporary iterator objs
#if __cplusplus >= 201103L
private:
	struct reverse_adapter{//i.e. defined to use reverse_iterator on 'range-based' loop
		reverse_adapter(const Vector& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const Vector& ref;
	};
public:
	//i.e. reversely traverse vector inside range-based loop
	reverse_adapter reverse_it()const{ return reverse_adapter(*this); }
#endif
	
	~Vector(){ delete[] data; }//i.e. dtor
};
#endif
