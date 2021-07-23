#ifndef ITERATOR_GUARD
#define ITERATOR_GUARD 1

#ifndef __int64
#define __int64 long long
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#endif

template<typename T>
class Base_Iterator{
 	typedef Base_Iterator self;
public:
	/*i.e. Accessors */
	T& operator*()const{ return *ptr; }
	T* operator&()const{ return ptr; }
	T& operator[](const __int64& index)const{ return ptr[index]; }
		
	/*i.e. Comparison Operators */
	bool operator==(const self& other)const{ return ptr==other.ptr; }
	bool operator!=(const self& other)const{ return ptr!=other.ptr; }
protected:
	Base_Iterator(T* ptr):ptr(ptr){}//i.e. ctor
	
	T* ptr;
};

template<typename T>
class Iterator:public Base_Iterator<T>{
	typedef Iterator self;
	typedef Base_Iterator<T> base;
public:
	Iterator(T* ptr):base(ptr){}//i.e. default ctor
	
	/*i.e. Arithmetic Operators */
	self& operator++(){ ++base::ptr; return *this; }//i.e. pre-increment
	self& operator--(){ --base::ptr; return *this; }//i.e. pre-decrement
	self operator++(int){ self temp(*this); ++base::ptr; return temp; }//i.e. post-increment
	self operator--(int){ self temp(*this); --base::ptr; return temp; }//i.e. post-decrement
	self& operator+=(const __int64& index){ base::ptr+=index; return *this; }
	self& operator-=(const __int64& index){ base::ptr-=index; return *this; }
	self operator+(const __int64& index)const{ return self(base::ptr+index); }
	friend self operator+(const __int64& index,const self& other){ return self(index+other.ptr); }
	self operator-(const __int64& index)const{ return self(base::ptr-index); }
	__int64 operator-(const self& other)const{ return base::ptr-other.base::ptr; }//i.e. returns difference_type
	
	/*i.e. Comparison Operators */
	bool operator>(const self& other)const{ return base::ptr>other.base::ptr; }
	bool operator<(const self& other)const{ return base::ptr<other.base::ptr; }
	bool operator>=(const self& other)const{ return base::ptr>=other.base::ptr; }
	bool operator<=(const self& other)const{ return base::ptr<=other.base::ptr; }
};

template<typename T>
class Reverse_Iterator:public Base_Iterator<T>{
	typedef Reverse_Iterator self;
	typedef Base_Iterator<T> base;
public:
	Reverse_Iterator(T* ptr):base(ptr){}
	
	/*i.e. Arithmetic Operators */
	self& operator++(){ --base::ptr; return *this; }
	self& operator--(){ ++base::ptr; return *this; }
	self operator++(int){ self temp(*this); --base::ptr; return temp; }
	self operator--(int){ self temp(*this); ++base::ptr; return temp; }
	self& operator+=(const __int64& index){ base::ptr-=index; return *this; }
	self& operator-=(const __int64& index){ base::ptr+=index; return *this; }
	self operator+(const __int64& index)const{ return self(base::ptr-index); }
	friend self operator+(const __int64& index,const self& other){ return self(index+other.ptr); }
	self operator-(const __int64& index)const{ return self(base::ptr+index); }
	__int64 operator-(const self& other)const{ return other.base::ptr-base::ptr; }
	
	/*i.e. Comparison Operators */
	bool operator>(const self& other)const{ return base::ptr<other.base::ptr; }
	bool operator<(const self& other)const{ return base::ptr>other.base::ptr; }
	bool operator>=(const self& other)const{ return base::ptr<=other.base::ptr; }
	bool operator<=(const self& other)const{ return base::ptr>=other.base::ptr; }
};

#endif
