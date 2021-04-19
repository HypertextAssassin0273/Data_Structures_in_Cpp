#ifndef ITERATOR_GUARD
#define ITERATOR_GUARD 1

#ifndef __int64
#define __int64 long long
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#endif

template<typename T>
struct Iterator{
	typedef Iterator self;
	
	Iterator():ptr(nullptr){}
	Iterator(T* ptr):ptr(ptr){}
	
	/*i.e. Accessors */
	T& operator*()const{ return *ptr; }
	T* operator->()const{ return ptr; }
	T& operator[](__int64 index)const{ return ptr[index]; }
	
	/*i.e. Arithmetic Operators */
	self& operator++(){ ++ptr; return *this; }//i.e. pre-increment
	self& operator--(){ --ptr; return *this; }//i.e. pre-decrement
	self operator++(int){ self temp(*this); ++ptr; return temp; }//i.e. post-increment
	self operator--(int){ self temp(*this); --ptr; return temp; }//i.e. post-deccrement
	self& operator+=(__int64 index){ ptr+=index; return *this; }
	self& operator-=(__int64 index){ ptr-=index; return *this; }
	self operator+(__int64 index)const{ return self(ptr+index); }
	self operator-(__int64 index)const{ return self(ptr-index); }
	friend self operator+(__int64 index,const self& other){ return self(index+other.ptr); }
	__int64 operator-(const self& other)const{ return ptr-other.ptr; }//i.e. returns difference_type
	
	/*i.e. Comparison Operators */
	bool operator==(const self& other)const{ return ptr==other.ptr; }
	bool operator!=(const self& other)const{ return ptr!=other.ptr; }
	bool operator>(const self& other)const{ return ptr>other.ptr; }
	bool operator<(const self& other)const{ return ptr<other.ptr; }
	bool operator>=(const self& other)const{ return ptr>=other.ptr; }
	bool operator<=(const self& other)const{ return ptr<=other.ptr; }
private:
	T* ptr;
};

template<typename T>
struct Reverse_Iterator{
	typedef Reverse_Iterator self;
	
	Reverse_Iterator():ptr(nullptr){}
	Reverse_Iterator(T* ptr):ptr(ptr){}
	
	/*i.e. Accessors */
	T& operator*()const{ return *ptr; }
	T* operator->()const{ return ptr; }
	T& operator[](__int64 index)const{ return ptr[index]; }
	
	/*i.e. Arithmetic Operators */
	self& operator++(){ --ptr; return *this; }
	self& operator--(){ ++ptr; return *this; }
	self operator++(int){ self temp(*this); --ptr; return temp; }
	self operator--(int){ self temp(*this); ++ptr; return temp; }
	self& operator+=(__int64 index){ ptr-=index; return *this; }
	self& operator-=(__int64 index){ ptr+=index; return *this; }
	self operator+(__int64 index)const{ return self(ptr-index); }
	self operator-(__int64 index)const{ return self(ptr+index); }
	friend self operator+(__int64 index,const self& other){ return self(index+other.ptr); }
	__int64 operator-(const self& other)const{ return other.ptr-ptr; }
	
	/*i.e. Comparison Operators */
	bool operator==(const self& other)const{ return ptr==other.ptr; }
	bool operator!=(const self& other)const{ return ptr!=other.ptr; }
	bool operator>(const self& other)const{ return ptr<other.ptr; }
	bool operator<(const self& other)const{ return ptr>other.ptr; }
	bool operator>=(const self& other)const{ return ptr<=other.ptr; }
	bool operator<=(const self& other)const{ return ptr>=other.ptr; }
private:
	T* ptr;
};

#endif
