/* Custom Forward_Deque Class (improved version of Vector container) */
/*  Highlights:
	1) provides same utility as Vector with some additional improvements
	2) ability to store large amount of heavy-weight objects in less amount of time
	3) doesn't invalidates pointers & references to elements
	   (note: iterators still gets invalidated after using modifiers)
	4) doesn't reallocate previously assigned resources 
	   (i.e. gives improved performance on constant use of push_backs & pop_backs)
	Notes:
	1) this container is only offered in C++11 & higher versions since 
	   its performance heavily relies on "move semantics"
	2) this implementation can easily become more memory-efficient by making it a 
	   "vector of fixed-size dynamic arrays" with only size attribute instead of taking 
	   "vector of vectors" (as we don't need capacity attribute for our 1D Vector).
*/
#ifndef FORWARD_DEQUE_GUARD
#define FORWARD_DEQUE_GUARD 1

#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#include"Vector.hpp"

template<typename T,size_t chunk_size=1>
class Forward_Deque{//i.e. same as one-sided STL::deque
	size_t _size;
	Vector<Vector<T>> data_chunks;//i.e. stores chunks of data-buffer on heap
public:
	template<typename... _T>
	Forward_Deque(size_t n=0,_T&&... val):_size(n){//i.e. default & emplaced fill ctor
		if(n>data_chunks.max_capacity)
			throw false;
		if(n--){
			data_chunks.reserve(n/chunk_size+1);
			for(size_t i=0,j;i<n/chunk_size+1;++i){
				data_chunks.push_back(Vector<T>());
				data_chunks[i].reserve(chunk_size);
				for(j=0;(j<chunk_size)&&(i*chunk_size+j<n+1);++j)
					data_chunks[i].emplace_back(std::forward<_T>(val)...);
			}
		}
	}
	Forward_Deque(const Forward_Deque& other)noexcept://i.e. (deep) copy ctor
		data_chunks(other.data_chunks),_size(other._size){}
	
	Forward_Deque& operator=(const Forward_Deque& other)noexcept{//i.e. copy assignment operator
		data_chunks=other.data_chunks;
		_size=other._size;
		return *this;
	}
	Forward_Deque(Forward_Deque&& other)noexcept://i.e. move ctor
		data_chunks(std::move(other.data_chunks)),_size(other._size){ other._size=0; }
	
	Forward_Deque& operator=(Forward_Deque&& other)noexcept{//i.e. move assignment operator
	  	data_chunks=move(other.data_chunks);
  		_size=other._size; other._size=0;
		return *this;
	}
	Forward_Deque(const std::initializer_list<T>& list)noexcept://i.e. ctor for initializer-list
		_size(list.size()){
		if(_size){
			auto&& it=list.begin();
			data_chunks.reserve((_size-1)/chunk_size+1);
			for(size_t i=0,j;i<(_size-1)/chunk_size+1;++i){
				data_chunks.push_back(Vector<T>());
				data_chunks[i].reserve(chunk_size);
				for(j=0;(j<chunk_size)&&(it!=list.end());++j)
					data_chunks[i].push_back(*it++);
			}
		}
	}
	
 	/*** Accessors ***/
	T& operator[](const size_t& n)const{//i.e. gives read & write both access
		return data_chunks[n/chunk_size][n-(n/chunk_size)*chunk_size];//i.e. n/chunk_size == chunk_index
	}
	T* operator+(const size_t& n)const{//i.e. returns address of current pointed element
		return data_chunks[n/chunk_size]+(n-(n/chunk_size)*chunk_size);
		//Note: use with '*' operator to access elements of data-buffer (i.e. cout<<*(vec+2); )
	}
	
	bool empty()const{ return data_chunks.empty(); }
	
	T& front()const{ return data_chunks[0].front(); }
	T& back()const{ return data_chunks[(_size-1)/chunk_size].back(); }
	
	__int64 size()const{ return _size; }
	__int64 capacity()const{ return data_chunks.size()*chunk_size; }
	
	/*** Modifiers ***/
	template<typename... _T>
	void push_back(_T&&... val){//i.e. more efficient (as direct object initialization is possible)
		if(_size>=capacity()){
			data_chunks.emplace_back();
			data_chunks[_size/chunk_size].reserve(chunk_size);
		}
		data_chunks[_size++/chunk_size].emplace_back(std::forward<_T>(val)...);
	}
	void pop_back(){
		if(_size)
			data_chunks[--_size/chunk_size].pop_back();
	}
	bool reserve(size_t n){
		if(n<1||n-->data_chunks.max_capacity)
			return false;
		while(n/chunk_size+1>data_chunks.size()){
			data_chunks.push_back(Vector<T>());
			data_chunks[data_chunks.size()-1].reserve(chunk_size);
		}
		return true;
	}
	template<typename... _T>
	void resize(const size_t& n,_T&&... val){//i.e. emplaced_resize
		if(n>_size&&reserve(n))
	    	while(_size<n)
	    		data_chunks[_size++/chunk_size].emplace_back(std::forward<_T>(val)...);
		else
			while(n<_size)
				data_chunks[--_size/chunk_size].pop_back();
	}
	Vector<T> release_chunk(){
		if(data_chunks.empty())
			return Vector<T>();//i.e. returns empty vector if no chunk_vector is found
		_size-=data_chunks.back().size();
		Vector<T> temp=move(data_chunks.back());
		data_chunks.pop_back();
		return temp;
		//Note: no need for explicit move as compiler itself performs R.V.O (Return Value Optimization)		
	}
	void shrink_to_fit(){//i.e. opppsite to reserve func
		while((_size-1)/chunk_size+1<data_chunks.size())
			data_chunks.pop_back();
	}
	void clear(){ _size=0; data_chunks.clear(); }
	
	/*** Comparators ***/
	bool operator==(const Forward_Deque& other)const{
		if(_size!=other._size)
			return false;
		for (size_t i=0;i<data_chunks.size();++i)
			if (!(data_chunks[i]==other.data_chunks[i]))
				return false;
		return true;
	}
	bool operator!=(const Forward_Deque& other)const{ return !(*this==other); }
	
	bool operator<(const Forward_Deque& other)const{//i.e. follows lexicographical-order (Dictionary order)
		size_t i=0;
		for (;i<data_chunks.size();++i)
			if(i==other.data_chunks.size()||data_chunks[i]>other.data_chunks[i])
				return false;
			else if(data_chunks[i]<other.data_chunks[i])
				return true;
		return i!=other.data_chunks.size();
	}
	bool operator>(const Forward_Deque& other)const{ return other<*this; }
	bool operator<=(const Forward_Deque& other)const{ return !(other<*this); }
	bool operator>=(const Forward_Deque& other)const{ return !(*this<other); }
	
 	/*** Iterators ***/
private:
 	class base_iterator{
 		typedef base_iterator self;
 	protected:
 		Vector<T> *ptr;
		__int64 index;
		
    	base_iterator(Vector<T>* ptr,const size_t& element_index)noexcept://i.e. ctor
			ptr(ptr),index(element_index){}
 	public:
 		/* accessors */
		T& operator*()const{ return (*ptr)[index-(index/chunk_size)*chunk_size]; }
		T* operator&()const{ return *ptr+(index-(index/chunk_size)*chunk_size); }//i.e. returns address of element
		T& operator[](__int64 n)const{
			return (*(ptr+n/chunk_size))[(index+n)-(index+n)/chunk_size*chunk_size];
		}
		/* comparators */
		bool operator==(const self& other)const{ return index==other.index; }
		bool operator!=(const self& other)const{ return index!=other.index; }
	};
public:
	class iterator:public base_iterator{//i.e. forward iterator
		typedef iterator self;
		typedef base_iterator base;
	public:
    	iterator(Vector<T>* ptr,const __int64& element_index)noexcept://i.e. ctor
			base(ptr,element_index){}
		
		/* modifiers (arithmetic operators) */
		//prefix//
		self& operator++(){ if(++base::index%chunk_size==0) ++base::ptr; return *this; }
		self& operator--(){ if(base::index--%chunk_size==0) --base::ptr; return *this; }
		//postfix//
		self operator++(int){ self temp(*this); if(++base::index%chunk_size==0) ++base::ptr; return temp; }
		self operator--(int){ self temp(*this); if(base::index--%chunk_size==0) --base::ptr; return temp; }
		
		__int64 operator-(const self& other)const{ return base::index-other.base::index; }//i.e. returns difference_type
		
		/* comparators */
		bool operator>(const self& other)const{ return base::index>other.base::index; }
		bool operator<(const self& other)const{ return base::index<other.base::index; }
		bool operator>=(const self& other)const{ return base::index>=other.base::index; }
		bool operator<=(const self& other)const{ return base::index<=other.base::index; }
	};
	
	class sf_iterator:public iterator{//i.e. special forward iterator
		typedef sf_iterator self;
		typedef iterator base;
		
		Vector<T> *b_ptr;
	public:
		sf_iterator(Vector<T>* base_ptr,Vector<T>* ptr,const __int64& element_index)noexcept:
			b_ptr(base_ptr),base(ptr,element_index){}
		
		/* modifiers */
		//Note: following operator definitions are re-written/overloaded in order to avoid object-slicing
		self& operator++(){ if(++base::index%chunk_size==0) ++base::ptr; return *this; }
		self& operator--(){ if(base::index--%chunk_size==0) --base::ptr; return *this; }
		self operator++(int){ self temp(*this); if(++base::index%chunk_size==0) ++base::ptr; return temp; }
		self operator--(int){ self temp(*this); if(base::index--%chunk_size==0) --base::ptr; return temp; }
		
		self& operator+=(const __int64& n){ base::ptr=b_ptr+(base::index+=n)/chunk_size; return *this; }
		self& operator-=(const __int64& n){ base::ptr=b_ptr+(base::index-=n)/chunk_size; return *this; }
		self operator+(const __int64& n)const{ return self(b_ptr,b_ptr+(base::index+n)/chunk_size,base::index+n); }
 		friend self operator+(const __int64& n,const self& other){ 
 			return self(other.b_ptr,other.b_ptr+(other.base::index+n)/chunk_size,other.base::index+n);
		}
		self operator-(const __int64& n)const{ return self(b_ptr,b_ptr+(base::index-n)/chunk_size,base::index-n); }
		
		//Note: below operator version is redefined since its above version is also overloaded in same class-hierarchy
		__int64 operator-(const self& other)const{ return base::index-other.base::index; }
	};
	
	class reverse_iterator:public base_iterator{//i.e. backward iterator
		typedef reverse_iterator self;
		typedef base_iterator base;
	public:
    	reverse_iterator(Vector<T>* ptr,const __int64& element_index)noexcept://i.e. ctor
			base(ptr,element_index){}
		
		/* modifiers */
		self& operator++(){ if(base::index--%chunk_size==0) --base::ptr; return *this; }
		self& operator--(){ if(++base::index%chunk_size==0) ++base::ptr; return *this; }
		self operator++(int){ self temp(*this); if(base::index--%chunk_size==0) --base::ptr; return temp; }
		self operator--(int){ self temp(*this); if(++base::index%chunk_size==0) ++base::ptr; return temp; }
		
		__int64 operator-(const self& other)const{ return other.base::index-base::index; }
		
		/* comparators */
		bool operator>(const self& other)const{ return base::index<other.base::index; }
		bool operator<(const self& other)const{ return base::index>other.base::index; }
		bool operator>=(const self& other)const{ return base::index<=other.base::index; }
		bool operator<=(const self& other)const{ return base::index>=other.base::index; }		
	};
	
	class sr_iterator:public reverse_iterator{//i.e. special reverse iterator
		typedef sr_iterator self;
		typedef reverse_iterator base;
		
		Vector<T> *b_ptr;
	public:
		sr_iterator(Vector<T>* base_ptr,Vector<T>* ptr,const __int64& element_index)noexcept://i.e. ctor
			b_ptr(base_ptr),base(ptr,element_index){}
		
		/* modifiers */
		self& operator++(){ if(base::index--%chunk_size==0) --base::ptr; return *this; }
		self& operator--(){ if(++base::index%chunk_size==0) ++base::ptr; return *this; }
		self operator++(int){ self temp(*this); if(base::index--%chunk_size==0) --base::ptr; return temp; }
		self operator--(int){ self temp(*this); if(++base::index%chunk_size==0) ++base::ptr; return temp; }
		
		self& operator+=(const __int64& n){ base::ptr=b_ptr+(base::index-=n)/chunk_size; return *this; }
		self& operator-=(const __int64& n){ base::ptr=b_ptr+(base::index+=n)/chunk_size; return *this; }
		self operator+(const __int64& n)const{ return self(b_ptr,b_ptr+(base::index-n)/chunk_size,base::index-n); }
		friend self operator+(const __int64& n,const self& other){ 
 			return self(other.b_ptr,other.b_ptr+(other.base::index-n)/chunk_size,other.base::index-n);
		}
		self operator-(const __int64& n)const{ return self(b_ptr,b_ptr+(base::index+n)/chunk_size,base::index+n); }
		
		__int64 operator-(const self& other)const{ return other.base::index-base::index; }
	};
	
	iterator begin()const{ return iterator(data_chunks+0,0); }
	iterator end()const{ return iterator(data_chunks+data_chunks.size(),_size); }
	reverse_iterator rbegin()const{ return reverse_iterator(data_chunks+data_chunks.size()-1,_size-1); }
	reverse_iterator rend()const{ return reverse_iterator(data_chunks+(-1),-1); }
	
	sf_iterator sfbegin()const{ return sf_iterator(data_chunks+0,data_chunks+0,0); }
	sf_iterator sfend()const{ return sf_iterator(data_chunks+0,data_chunks+data_chunks.size(),_size); }
	sr_iterator srbegin()const{ return sr_iterator(data_chunks+0,data_chunks+data_chunks.size()-1,_size-1); }
	sr_iterator srend()const{ return sr_iterator(data_chunks+0,data_chunks+(-1),-1); }
	
private:
	//Note: following structs are defined to use reverse & special_reverse iterators on 'range-based' loop
	struct reverse_adapter{//i.e. light-weight adapter
		reverse_adapter(const Forward_Deque& reference):ref(reference){}
		
		reverse_iterator begin()const{ return ref.rbegin(); }
		reverse_iterator end()const{ return ref.rend(); }
	private:
		const Forward_Deque& ref;
	};
	struct special_reverse_adapter{//i.e. heavy-weight adapter
		special_reverse_adapter(const Forward_Deque& reference):ref(reference){}
		
		sr_iterator begin()const{ return ref.srbegin(); }
		sr_iterator end()const{ return ref.srend(); }
	private:
		const Forward_Deque& ref;
	};
public:
	//Note: reversely traverse forward_deque using below methods (inside range-based loop)
	reverse_adapter r_iterator()const{ return reverse_adapter(*this); }
	special_reverse_adapter s_r_iterator()const{ return special_reverse_adapter(*this); }
	
	/*** Overloaded 'cin/cout' Methods ***/
	friend std::ostream& operator<<(std::ostream& out,const Forward_Deque& self){
		for(size_t i=0;i<self.data_chunks.size();++i)
			out<<self.data_chunks[i];
		return out;
	}
	friend std::istream& operator>>(std::istream& in,Forward_Deque& self){
		for(size_t i=0;i<self.data_chunks.size();++i)
			in>>self.data_chunks[i];
		return in;
	}
};
#endif

#endif
