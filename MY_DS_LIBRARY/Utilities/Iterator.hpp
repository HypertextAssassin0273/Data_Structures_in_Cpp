/* Note: Only Applicable to Complete Contiguous Structures */

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
 	typedef Base_Iterator __self;
 	
public:
	/* Accessors (getters & setters) */
	T& operator*()const{ return *ptr; }
	T* operator&()const{ return ptr; }
	
	T& operator[](__int64 index)const{ return ptr[index]; }
	
	/* Comparators (comparison operators) */
	bool operator==(const __self& other)const{ return ptr==other.ptr; }
	bool operator!=(const __self& other)const{ return ptr!=other.ptr; }
	
protected:
	Base_Iterator(T* ptr)://parameterized ctor (default)
		ptr(ptr){}
	
	T* ptr;
};

template<typename T>
class Iterator://traverses in forward direction
	public Base_Iterator<T>{
	//simplified type names:
	typedef Iterator __self;
	typedef Base_Iterator<T> base;
	
	using base::ptr;
public:
	Iterator(T* ptr=nullptr)://default & parameterized ctor
		base(ptr){}
	
	/* Modifiers (arithmetic operators) */
	//prefix operators:
	__self& operator++(){ ++ptr; return *this; }
	__self& operator--(){ --ptr; return *this; }
	
	//postfix operators:
	__self operator++(int){ __self temp(*this); ++ptr; return temp; }
	__self operator--(int){ __self temp(*this); --ptr; return temp; }
	
	__self& operator+=(__int64 index){ ptr+=index; return *this; }
	__self& operator-=(__int64 index){ ptr-=index; return *this; }
	
	__self operator+(__int64 index)const{ return __self(ptr+index); }
	__self operator-(__int64 index)const{ return __self(ptr-index); }
	
	friend __self operator+(__int64 index, const __self& other){
		return __self(index+other.ptr);
	}
	
	__int64 operator-(const __self& other)const{ return ptr-other.ptr; }//returns difference_type
	//note: returns difference_type (required for some STL::algorithms)
	
	/* (additional) Comparators */
	bool operator>(const __self& other)const{ return ptr>other.ptr; }
	bool operator<(const __self& other)const{ return ptr<other.ptr; }
	bool operator>=(const __self& other)const{ return ptr>=other.ptr; }
	bool operator<=(const __self& other)const{ return ptr<=other.ptr; }
};

template<typename T>
class Reverse_Iterator://traverses in backward direction
	public Base_Iterator<T>{
	//simplified type names:
	typedef Reverse_Iterator __self;
	typedef Base_Iterator<T> base;
	
	using base::ptr;
public:
	Reverse_Iterator(T* ptr=nullptr):
		base(ptr){}
	
	/* Modifiers (arithmetic operators) */
	__self& operator++(){ --ptr; return *this; }
	__self& operator--(){ ++ptr; return *this; }
	
	__self operator++(int){ __self temp(*this); --ptr; return temp; }
	__self operator--(int){ __self temp(*this); ++ptr; return temp; }
	
	__self& operator+=(__int64 index){ ptr-=index; return *this; }
	__self& operator-=(__int64 index){ ptr+=index; return *this; }
	
	__self operator+(__int64 index)const{ return __self(ptr-index); }
	__self operator-(__int64 index)const{ return __self(ptr+index); }
	
	friend __self operator+(__int64 index, const __self& other){
		return __self(index+other.ptr);
	}
	
	__int64 operator-(const __self& other)const{ return other.ptr-ptr; }
	
	/* (additional) Comparators */
	bool operator>(const __self& other)const{ return ptr<other.ptr; }
	bool operator<(const __self& other)const{ return ptr>other.ptr; }
	bool operator>=(const __self& other)const{ return ptr<=other.ptr; }
	bool operator<=(const __self& other)const{ return ptr>=other.ptr; }
};

#endif
