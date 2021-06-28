#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

/* Custom String Class (minimal std::string) */

#ifndef STRING_GUARD
#define STRING_GUARD 1

#if !ITERATOR_GUARD
#include"Iterator.hpp"
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class Vector;//i.e. forward declaration

template<>
class Vector<char>{
	typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	static const __uint32 max_capacity=~((__uint32)0);
	__uint32 _size,_capacity;
	char *data;
public:
	Vector(__uint64 n=0)noexcept:
		_size((n>max_capacity)?throw:n),_capacity(_size),data(new char[_size]()){}
	Vector(__uint64 n,const char& val)noexcept:
		_size((n>max_capacity)?throw:n),_capacity(_size),data(new char[_size]){
		for(__uint64 i=0;i<_size;++i)
			data[i]=val;
	}
	template<__uint64 n>
	Vector(const char (&str)[n])noexcept://i.e. ctor for taking const char* type string
		_size((n>max_capacity)?throw:n-1),_capacity(_size),data(new char[_size]){
	 	for(__uint64 i=0;i<_size;++i)
			data[i]=str[i];
	}
	Vector(char* str)noexcept:
		_size(0),_capacity(0),data(nullptr){
	 	for(;str[_capacity]!='\0';_capacity++);
		data=new char[_capacity];
		while(_size<_capacity)
			data[_size]=str[_size++];
	}
	Vector(const string& str)noexcept:
		_size((str.size()>max_capacity)?throw:str.size()),_capacity(_size),data(new char[_size]){
	 	for(__uint64 i=0;i<_size;++i)
			data[i]=str[i];
	}
#if __cplusplus >= 201103L
	Vector(const std::initializer_list<char>& list)noexcept:
		_size(0),_capacity(list.size()),data(new char[_capacity]){
		for(const auto& it:list)
			data[_size++]=it;
	}
#endif
	Vector(const Vector& other)noexcept:
		_size(other._size),_capacity(other._capacity),data(new char[_capacity]()){
 		for(__uint64 i=0;i<_size;++i)
			data[i]=other.data[i];
	}
	Vector& operator=(const Vector& other)noexcept{
		if(this==&other)
			return *this;
  		delete[] data;
  		data=new char[other._capacity];
 		for(__uint64 i=0;i<_size;++i)
			data[i]=other.data[i];
 		_size=other._size;
 		_capacity=other._capacity;
	 	return *this;
 	}
 	template<__uint64 n>
	Vector& operator=(const char (&str)[n])noexcept{//i.e. copy assignment for string
		delete[] data;
		data=new char[_capacity=_size=n-1];
	 	for(__uint64 i=0;i<_size;++i)
			data[i]=str[i];
		return *this;
	}
#if __cplusplus >= 201103L
 	Vector(Vector&& other)noexcept:
  		data(other.data),_size(other._size),_capacity(other._capacity){
		other.data=nullptr;
  		other._size=other._capacity=0;
	}
	Vector& operator=(Vector&& other)noexcept{
  		if(this==&other)
			return *this;
  		delete[] data;
  		data=other.data;
  		_size=other._size;
  		_capacity=other._capacity;
  		other.data=nullptr;
  		other._size=other._capacity=0;
  		return *this;
	}
#endif
	
 	/*i.e. Accessors & Mutators */
	char& operator[](__uint32 n)const{
		if (n>=_size){
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		throw false;
		}
		return data[n];
	}
	char* operator+(__uint32 n)const{
		if (n>=_size){
			cout<<"\nError: Given Index is Out of Bound!\n";
	 		throw false;
		}
		return data+n;
	}
	char& front()const{
		if (_size)
			return data[0];
		throw false;
	}
	char& back()const{
		if (_size)
			return data[_size-1];
		throw false;
	}
	__uint32 size()const{ return _size; }
 	__uint32 capacity()const{ return _capacity; }
	
	/*i.e. Modifiers */
	bool empty()const{ return _size?false:true; }
private:
	void reallocate(__uint64 n){
		char* new_data=new char[n];
		for(__uint64 i=0;i<_size;++i)
			new_data[i]=data[i];
		delete[] data;
		data=new_data;
	}
public:
    void push_back(const char& val){
    	if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
    	data[_size++]=val;
	}
	void pop_back(){
		if(_size)
			--_size;
	}
	void clear(){ _size=0; }
	bool reserve(__uint64 n){
		if(n>max_capacity)
			return false;
		if(n>_capacity)
			reallocate(_capacity=n);
		return true;
	}
	void resize(__uint64 n,const char& val='\0'){
		if(n>_size&&reserve(n))
	    	while(_size<_capacity)
    			data[_size++]=val;
    	else if(n<_size)
			_size=n;
	}
	void shrink_to_fit(){
		if(_size<_capacity)
   	 	    reallocate(_capacity=_size);
	}
	template<__uint64 n>
	Vector operator+(const char (&str)[n]){
		Vector temp=*this;
		temp.reallocate(temp._size+n-1);
		for(__uint64 i=0;i<n-1;++i)
			temp.data[temp._size++]=str[i];
		return temp;
	}
	Vector operator+(const Vector& other){
		Vector temp=*this;
		temp.reallocate(temp._size+other._size);
		for(__uint64 i=0;i<other._size;++i)
			temp.data[temp._size++]=other.data[i];
		return temp;
	}
	template<__uint64 n>
	Vector& operator+=(const char (&str)[n]){//i.e. appends the string
		if(n-1){
			reallocate(_size+n-1);//i.e. neglecting null of str
			for(__uint64 i=0;i<n-1;++i)
				data[_size++]=str[i];
		}
		return *this;
	}
	Vector& operator+=(const Vector& other){//i.e. appends the elements of 'other'
		if(other._size){
			reallocate(_size+other._size);
			if(this==&other){
				Vector temp=other;
				//i.e. can't perform read & write operations simultaneously on same memory segment, 
				//	   so temporary is created
				for(__uint64 i=0;i<temp._size;++i)
					data[_size++]=temp.data[i];
			}
			else
				for(__uint64 i=0;i<other._size;++i)
					data[_size++]=other.data[i];
		}
		return *this;
	}

	/*i.e. Comparison Operators */
	bool operator==(const Vector& other)const{
		if(other._size<_size)
			return false;
		for (__uint64 i=0;i<_size;++i)
    		if (data[i]!=other.data[i])
      			return false;
  		return true;
	}
	bool operator!=(const Vector& other)const{ return !(*this==other); }
	
	bool operator<(const Vector& other)const{
  		__uint64 i=0;
  		for (;i!=_size;++i){
  			if(i==other._size||other.data[i]<data[i])
  				return false;
  			else if(data[i]<other.data[i])
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const Vector& other)const{ return other<*this; }

 	/*i.e. Iterators */
 	typedef Iterator<char> iterator;
 	typedef Reverse_Iterator<char> r_iterator;
 	
	iterator begin()const{ return iterator(data); }
	iterator end()const{ return iterator(data+_size); }
    r_iterator rbegin()const{ return r_iterator(data+_size-1); }
	r_iterator rend()const{ return r_iterator(data-1); }
#if __cplusplus >= 201103L
	struct reverse_adapter{
	reverse_adapter(const Vector& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const Vector& ref;
	};
	reverse_adapter reverse_iterator()const{ return reverse_adapter(*this); }
#endif
	
	/* Overloaded 'cin/cout' Methods */
	friend ostream& operator<<(ostream& out,const Vector& vec){
		for(__uint32 i=0;i<vec._size;++i)
			out<<vec.data[i];
		return out;
	}
	friend istream& operator>>(istream& in,Vector& vec){
		vec._size=0;
		for(char temp;(temp=getchar())!=10;vec.push_back(temp));
		return in;
	}
	
	~Vector(){ delete[] data; }
};
typedef Vector<char> String;

#endif
