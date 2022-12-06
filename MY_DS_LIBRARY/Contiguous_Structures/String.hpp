/* Custom String Class (same as minimal std::string) */

#ifndef STRING_GUARD
#define STRING_GUARD 1

#include <iostream>
#include <fstream>
#include "../Utilities/Iterator.hpp"
#include "../Utilities/Reverse_Iterator_Adapter.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename>
class Vector;//forward declaration

template<>
class Vector<char>{
	typedef Vector __S;
	
	/* Private Member Attributes */
	size_t _size, _capacity;
	char *data;
public:
	static const unsigned int max_capacity=~((unsigned int)0);
	
	/* Constructors & Assignment Operators */	
	Vector(const size_t& n=0, const char& val='\0')://default & fill ctor
		_size(0), _capacity((n>max_capacity)?throw:n), data(new char[_capacity]){
		while(_size<_capacity)
			data[_size++]=val;
	}
	
	//copy semantics (rule of three):
	Vector(const __S& other)noexcept://(deep) copy ctor
		_size(0), _capacity(other._capacity), data(new char[_capacity]()){
 		while(_size<other.size())
			data[_size]=other.data[_size++];
	}
	__S& operator=(const __S& other)noexcept{//(deep) copy assignment operator
		if(this!=&other){
	  		delete[] data;
	  		data=new char[_capacity=other._capacity];
 			for(_size=0;_size<other.size();++_size)
				data[_size]=other.data[_size];
	 	}
		return *this;
 	}
 	
	//copy semantics for const char* (temp_string) type:
	template<size_t n>
	Vector(const char (&str)[n])://(deep) copy ctor
		_size(0), _capacity((n>max_capacity)?throw:n-1), data(new char[_capacity]){
	 	while(_size<_capacity)
			data[_size]=str[_size++];
	}
	template<size_t n>
	__S& operator=(const char (&str)[n]){//(deep) copy assignment operator
		if(n<=max_capacity){
			delete[] data;
			data=new char[_capacity=n-1];//neglecting null of str
		 	for(_size=0;_size<_capacity;++_size)
				data[_size]=str[_size];
		}
		return *this;
	}
	
	//copy semantics for std::string type:
	Vector(const std::string& str)noexcept://(deep) copy ctor
		_size(0), _capacity(str.capacity()), data(new char[_capacity]){
	 	while(_size<str.size())
			data[_size]=str[_size++];
	}
	__S& operator=(const std::string& str){//(deep) copy assignment operator
		delete[] data;
		data=new char[_capacity=str.capacity()];
		while(_size<str.size())
			data[_size]=str[_size++];
		return *this;
	}
	
#if __cplusplus >= 201103L
	//move semantics (rule of five):
 	Vector(__S&& other)noexcept://move (shallow copy) ctor
  		data(other.data), _size(other._size), _capacity(other._capacity){
		other.data=nullptr;
  		other._size=other._capacity=0;
	}
	__S& operator=(__S&& other)noexcept{//move (shallow copy) assignment operator
  		if(this!=&other){
	  		delete[] data;
	  		data=other.data;
	  		_size=other._size;
	  		_capacity=other._capacity;
	  		other.data=nullptr;
	  		other._size=other._capacity=0;
		}
  		return *this;
	}
#endif
	//type convertor:
	Vector(char *new_data, size_t new_size, size_t new_capacity)noexcept://special move ctor
		_size(new_size), _capacity(new_capacity), data(new_data){}
		/* Note: set the source pointer to null state after pointing 'data' buffer to resource
		   Warning: use this ctor only for moving resource of current pointed type only! */
	
 	/* Accessors */
 	char& operator[](size_t n){ return data[n]; }
	const char& operator[](size_t n)const{ return data[n]; }
	
	char* operator+(size_t n){ return data+n; }
	const char* operator+(size_t n)const{ return data+n; }
	//Note: requires to append '\0' at end for const char* version in some std::methods
	
	char* operator-(size_t n){ return data+(_size-1-n); }
	const char* operator-(size_t n)const{ return data+(_size-1-n); }
	
	char& front(){ return data[0]; }
	const char& front()const{ return data[0]; }
	
	char& back(){ return data[_size-1]; }
	const char& back()const{ return data[_size-1]; }
	
	char& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return data[df?(_size-1-n):n];
	}
	const char& at(size_t n, bool df=false)const{
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return data[df?(_size-1-n):n];
	}
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'size()==true' for 'front' & 'back' accessors.
		2) use condition 'n<size()' for '[]', '+' & '-' operator accessors.
	*/
	
	size_t size()const{ return _size; }
 	size_t capacity()const{ return _capacity; }
 	
 	/* Desicion Checking Methods */
 	bool full()const{ return _size==_capacity; }
	bool empty()const{ return !_size; }
	
	/* Modifiers */
private:
	bool reallocate(size_t n){
		if(n>max_capacity) return false;
		char* new_data=new char[n];
		for(size_t i=0;i<_size;++i)
			new_data[i]=data[i];
		delete[] data;
		data=new_data; _capacity=n;
		return true;
	}
public:
    void push_back(const char& value){
    	if(_size==_capacity)
			if(!reallocate(_capacity?_capacity*2:1)) return;
    	data[_size++]=value;
	}
	void insert(const char& value, size_t n=0){
		if(n>_size) return;
		if(_size==_capacity)
			if(!reallocate(_capacity?_capacity*2:1)) return;
		if(_size!=n){
			data[_size]=data[_size-1];
			for(size_t i=_size-1;i>n;--i)
				std::swap(data[i], data[i-1]);
		}
		data[n]=value;
		++_size;
	}
	void pop_back(){
		if(_size)
			--_size;
	}
	void erase(size_t n=0){
		if(n>=_size) return; --_size;
		for(size_t i=n;i<_size;++i)
			std::swap(data[i], data[i+1]);
	}
	
	void clear(){ _size=0; }
	
	void reserve(size_t n){
		if(n>_capacity) reallocate(n);
	}
	void resize(size_t n, const char& value='\0'){
		if(n>_capacity)
			if(!reallocate(n)) return;
	    if(_size>n) _size=n;
		while(_size<n)
    		data[_size++]=value;
	}
	void shrink_to_fit(){
		if(_size<_capacity) reallocate(_size);
	}
	
	template<size_t n>
	__S operator+(const char (&str)[n]){
		__S temp(*this);
		if(temp.reallocate(temp._size+n-1))
			for(size_t i=0;i<n-1;++i)
				temp.data[temp._size++]=str[i];
		return temp;
	}
	__S operator+(const __S& other){
		__S temp(*this);
		if(temp.reallocate(temp._size+other._size))
			for(size_t i=0;i<other._size;++i)
				temp.data[temp._size++]=other.data[i];
		return temp;
	}
	
	template<size_t n>
	__S& operator+=(const char (&str)[n]){//appends the (temporary) string
		if((n-1)&&reallocate(_size+n-1))//neglecting null of str
			for(size_t i=0;i<n-1;++i)
				data[_size++]=str[i];
		return *this;
	}
	__S& operator+=(const __S& other){//appends the elements of 'other'
		if(other._size&&this!=&other&&reallocate(_size+other._size))
			for(size_t i=0;i<other._size;++i)
				data[_size++]=other.data[i];
		return *this;
	}
	
	/* Comparators */
	//for same class string type:
	bool operator==(const __S& other)const{
		if(other._size!=_size) return false;
		for(size_t i=0;i<_size;++i)
    		if(data[i]!=other.data[i])
      			return false;
  		return true;
	}
	bool operator!=(const __S& other)const{ return !(*this==other); }
	
	bool operator<(const __S& other)const{
  		size_t i=0;
  		for(;i!=_size;++i){
  			if(i==other._size||other.data[i]<data[i])
  				return false;
  			else if(data[i]<other.data[i])
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const __S& other)const{ return other<*this; }
	bool operator<=(const __S& other)const{ return !(other<*this); }
	bool operator>=(const __S& other)const{ return !(*this<other); }
	
	//for const char* (i.e. string literal) type:
	template<size_t n>
	bool operator==(const char (&str)[n])const{
		if(n-1!=_size) return false;
		for(size_t i=0;i<_size;++i)
    		if(data[i]!=str[i])
      			return false;
  		return true;
	}
	template<size_t n>
	friend bool operator==(const char (&str)[n], const __S& self){ return self==str; }
	
	template<size_t n>
	bool operator!=(const char (&str)[n])const{ return !(*this==str); }
	template<size_t n>
	friend bool operator!=(const char (&str)[n], const __S& self){ return !(self==str); }
	
	template<size_t n>
	bool operator<(const char (&str)[n])const{
  		size_t i=0;
  		for(;i!=_size;++i){
  			if(i==n-1||str[i]<data[i])
  				return false;
  			else if(data[i]<str[i])
  				return true;
		}
		return i!=n-1;
	}
	template<size_t n>
	friend bool operator>(const char (&str)[n], const __S& self){ return self<str; }
	
	template<size_t n>
    bool operator>(const char (&str)[n])const{ return __S(str)<*this; }
	template<size_t n>
	friend bool operator<(const char (&str)[n], const __S& self){ return __S(str)<self; }
	
	template<size_t n>
	bool operator<=(const char (&str)[n])const{ return !(__S(str)<*this); }
	template<size_t n>
	friend bool operator>=(const char (&str)[n], const __S& self){ return !(__S(str)<self); }
	
	template<size_t n>
	bool operator>=(const char (&str)[n])const{ return !(*this<str); }
	template<size_t n>
	friend bool operator<=(const char (&str)[n], const __S& self){ return !(self<str); }
	
	/* Iterators */
	//available string iterator objects:
 	typedef Iterator<char> iterator;
 	typedef Iterator<const char> const_iterator;
 	
 	typedef Reverse_Iterator<char> r_iterator;
 	typedef Reverse_Iterator<const char> const_r_iterator;
 	
 	//available string iterator methods:
	iterator begin(){ return iterator(data); }
	iterator end(){ return iterator(data+_size); }
	
	const_iterator begin()const{ return const_iterator(data); }
	const_iterator end()const{ return const_iterator(data+_size); }
    
	r_iterator rbegin(){ return r_iterator(data+_size-1); }
	r_iterator rend(){ return r_iterator(data-1); }
	
	const_r_iterator rbegin()const{ return const_r_iterator(data+_size-1); }
	const_r_iterator rend()const{ return const_r_iterator(data-1); }
	
#if __cplusplus >= 201103L
	//reversely traverse string using these methods (inside range-based loop):
	reverse_iterator_adapter<__S, r_iterator> r_iterator_adapter(){
		return reverse_iterator_adapter<__S, r_iterator>(*this);
	}
	reverse_iterator_adapter<const __S, const_r_iterator> r_iterator_adapter()const{
		return reverse_iterator_adapter<const __S, const_r_iterator>(*this);
	}
#endif
	
	/* Overloaded 'cout & cin' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __S& self){
		for(size_t i=0;i<self._size;++i)
			out<<self.data[i];
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __S& self){
		self._size=0;
		for(char reader;(reader=getchar())!=10;self.push_back(reader));
		return in;
	}
	
	/* Overloaded 'fout & fin' Methods */
	friend std::ofstream& operator<<(std::ofstream& out, const __S& self){//'fout' operator for .csv files
		bool dq_flag=false;//outer double_quote flag for checking any commas or inner double_quotes
		for(size_t i=0;i<self._size;++i)
			if(self.data[i]==','||self.data[i]=='"'){
				dq_flag=true;
				break;
			}
		if(dq_flag){
			out<<'"';
			for(size_t i=0;i<self._size;++i){
				if(self.data[i]=='"')//checks for inner double_quote & then adds one more for proper format
					out<<'"';
				out<<self.data[i];
			}
			out<<'"';
			}
		else
			for(size_t i=0;i<self._size;++i){
				if(self.data[i]=='"')
					out<<'"';
				out<<self.data[i];
			}
		return out;
	}
//	friend std::ofstream& operator<<(std::ofstream& out, const __S& self){//'fout' operator for .txt files
//		for(size_t i=0;i<self._size;++i)
//			out<<self.data[i];
//		return out;
//	}
	
	friend std::ifstream& operator>>(std::ifstream& in, __S& self){//'fin' operator for .csv files
		self._size=0;//over-writing previous buffer
		bool dq_flag=true;//double_quote flag
		while(true){
			switch(in.peek()){
				case '"':
					in.get();//discarding double_quote
					if(in.peek()=='"')
						self.push_back(in.get());
					else
						dq_flag=!dq_flag;
					continue;
				case EOF:
				case '\n':
					return in;
			}
			if(dq_flag&&in.peek()==',') return in;
			self.push_back(in.get());
		}
	}
//	friend ifstream& operator>>(ifstream& in, __S& self){//'fin' operator for .txt files
//		self._size=0;
//		for(char reader='\0';(reader=in.get())!='\n'&&!in.eof();self.push_back(reader));
//		return in;
//	}
	
	~Vector(){ _size=0; delete[] data; }//dtor
};

typedef Vector<char> String;

#endif
