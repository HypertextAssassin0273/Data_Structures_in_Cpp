/* Custom String Class (same as minimal std::string) */

#ifndef STRING_GUARD
#define STRING_GUARD 1

#include<iostream>
#include<fstream>
#include"Iterator.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class Vector;//i.e. forward declaration

template<>
class Vector<char>{
	static const unsigned int max_capacity=~((unsigned int)0);
	size_t _size,_capacity;
	char *data;
public:
	Vector(const size_t& n=0)://i.e. default ctor
		_size((n>max_capacity)?throw:n),_capacity(_size),data(new char[_size]()){}
	Vector(const size_t& n,const char& val)://i.e. fill ctor
		_size(0),_capacity((n>max_capacity)?throw:n),data(new char[_capacity]){
		while(_size<_capacity)
			data[_size++]=val;
	}
	template<size_t n>
	Vector(const char (&str)[n])://i.e. copy ctor for taking const char* type string
		_size(0),_capacity((n>max_capacity)?throw:n-1),data(new char[_capacity]){
	 	while(_size<_capacity)
			data[_size]=str[_size++];
	}
	template<size_t n>
	Vector& operator=(const char (&str)[n]){//i.e. copy assignment for const char* type
		if(n<=max_capacity){
			delete[] data;
			data=new char[_capacity=n-1];//i.e. neglecting null of str
		 	for(_size=0;_size<_capacity;++_size)
				data[_size]=str[_size];
		}
		return *this;
	}
	Vector(const std::string& str)noexcept://i.e. copy ctor for taking std::string type
		_size(0),_capacity(str.capacity()),data(new char[_capacity]){
	 	while(_size<str.size())
			data[_size]=str[_size++];
	}
	Vector& operator=(const std::string& str){//i.e. copy assignment for std::string type
		delete[] data;
		data=new char[_capacity=str.capacity()];
		while(_size<str.size())
			data[_size]=str[_size++];
		return *this;
	}
	Vector(const Vector& other)noexcept://i.e. copy ctor
		_size(0),_capacity(other._capacity),data(new char[_capacity]()){
 		while(_size<other.size())
			data[_size]=other.data[_size++];
	}
	Vector& operator=(const Vector& other)noexcept{//i.e. copy assignment
		if(this!=&other){
	  		delete[] data;
	  		data=new char[_capacity=other._capacity];
 			for(_size=0;_size<other.size();++_size)
				data[_size]=other.data[_size];
	 	}
		return *this;
 	}
#if __cplusplus >= 201103L
 	Vector(Vector&& other)noexcept://i.e. move ctor
  		data(other.data),_size(other._size),_capacity(other._capacity){
		other.data=nullptr;
  		other._size=other._capacity=0;
	}
	Vector& operator=(Vector&& other)noexcept{//i.e. move assignment
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
	Vector(const std::initializer_list<char>& list)noexcept://i.e. brace initializer-list ctor
		_size(0),_capacity(list.size()),data(new char[_capacity]){
		for(const auto& it:list)
			data[_size++]=it;
	}
#endif
	Vector(char *new_data,size_t new_size,size_t new_capacity)noexcept://i.e. special move ctor
		_size(new_size),_capacity(new_capacity),data(new_data){}
		/* Note: set the source pointer to null state after pointing 'data' buffer to resource
		   Warning: use this ctor only for moving resource of current pointed type only! */
	
 	/*i.e. Accessors & Mutators */
	char& operator[](size_t n)const{
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";			
	 		throw false;
		}
		return data[n];
	}
	char* operator+(size_t n)const{
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
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
	const char* c_str()const{ return data; }//Note: use it with '\0'
	size_t size()const{ return _size; }
 	size_t capacity()const{ return _capacity; }
	bool empty()const{ return _size?false:true; }
	
	/*i.e. Modifiers */
private:
	void reallocate(size_t n){
		char* new_data=new char[n];
		for(size_t i=0;i<_size;++i)
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
	bool reserve(size_t n){
		if(n>max_capacity)
			return false;
		if(n>_capacity)
			reallocate(_capacity=n);
		return true;
	}
	void resize(size_t n,const char& val='\0'){
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
	template<size_t n>
	Vector operator+(const char (&str)[n]){
		Vector temp=*this;
		temp.reallocate(temp._size+n-1);
		for(size_t i=0;i<n-1;++i)
			temp.data[temp._size++]=str[i];
		return temp;
	}
	Vector operator+(const Vector& other){
		Vector temp=*this;
		temp.reallocate(temp._size+other._size);
		for(size_t i=0;i<other._size;++i)
			temp.data[temp._size++]=other.data[i];
		return temp;
	}
	template<size_t n>
	Vector& operator+=(const char (&str)[n]){//i.e. appends the string
		if(n-1){
			reallocate(_size+n-1);//i.e. neglecting null of str
			for(size_t i=0;i<n-1;++i)
				data[_size++]=str[i];
		}
		return *this;
	}
	Vector& operator+=(const Vector& other){//i.e. appends the elements of 'other'
		if(other._size){
			reallocate(_size+other._size);
			if(this==&other){
				Vector temp=other;
				/*Note: we can't perform read & write operations simultaneously on same memory segment, 
					    so temporary is created */
				for(size_t i=0;i<temp._size;++i)
					data[_size++]=temp.data[i];
			}
			else
				for(size_t i=0;i<other._size;++i)
					data[_size++]=other.data[i];
		}
		return *this;
	}

	/*i.e. Comparison Operators */
	bool operator==(const Vector& other)const{
		if(other._size<_size)
			return false;
		for (size_t i=0;i<_size;++i)
    		if (data[i]!=other.data[i])
      			return false;
  		return true;
	}
	bool operator!=(const Vector& other)const{ return !(*this==other); }
	
	bool operator<(const Vector& other)const{
  		size_t i=0;
  		for (;i!=_size;++i){
  			if(i==other._size||other.data[i]<data[i])
  				return false;
  			else if(data[i]<other.data[i])
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const Vector& other)const{ return other<*this; }
	bool operator<=(const Vector& other)const{ return !(other<*this); }
	bool operator>=(const Vector& other)const{ return !(*this<other); }
	
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
	friend std::ostream& operator<<(std::ostream& out,const Vector& self){
		for(size_t i=0;i<self._size;++i)
			out<<self.data[i];
		return out;
	}
	friend std::istream& operator>>(std::istream& in,Vector& self){
		self._size=0;
		for(char reader;(reader=getchar())!=10;self.push_back(reader));
		return in;
	}
	
	/* Overloaded 'fin/fout' Methods */
	friend std::ofstream& operator<<(std::ofstream& out,const Vector& self){//i.e. 'fout' operator for .csv files
		bool dq_flag=false;//i.e. outer double_quote flag for checking any commas or inner double_quotes
		for(size_t i=0;i<self._size;++i)
			if(self.data[i]==','||self.data[i]=='"'){
				dq_flag=true;
				break;
			}
		if(dq_flag){
			out<<'"';
			for(size_t i=0;i<self._size;++i){
				if(self.data[i]=='"')//i.e. checks for inner double_quote & then adds one more for proper format
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
//	friend std::ofstream& operator<<(std::ofstream& out,const Vector& self){//i.e. 'fout' operator for .txt files
//		for(size_t i=0;i<self._size;++i)
//			out<<self.data[i];
//		return out;
//	}
	
	friend std::ifstream& operator>>(std::ifstream& in,Vector& self){//i.e. 'fin' operator for .csv files
		self._size=0;//i.e. over-writing previous buffer
		bool dq_flag=true;//i.e. double_quote flag
		while(true){
			switch(in.peek()){
				case '"':
					in.get();//i.e. discarding double_quote
					if(in.peek()=='"')
						self.push_back(in.get());
					else
						dq_flag=(dq_flag?false:true);
					continue;
				case EOF:
				case '\n':
					return in;
			}
			if(dq_flag&&in.peek()==',') return in;
			self.push_back(in.get());
		}
	}
//	friend ifstream& operator>>(ifstream& in,Vector& self){//i.e. 'fin' operator for .txt files
//		self._size=0;
//		for(char reader='\0';(reader=in.get())!='\n'&&!in.eof();self.push_back(reader));
//		return in;
//	}
	
	~Vector(){ _size=0; delete[] data; }//i.e. dtor
};
typedef Vector<char> String;

#endif
