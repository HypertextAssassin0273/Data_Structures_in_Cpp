/* Segmented Vector Class (improved version of Vector container) */
/*  Highlights:
	1) provides same utility as Vector with some additional improvements.
	2) ability to store large amount of heavy-weight objects in less amount of time.
	3) doesn't invalidates pointers & references to elements.
	   (note: iterators still gets invalidated after using modifiers)
	4) doesn't reallocate previously assigned resources.
	   (i.e. gives improved performance on constant use of push_backs & pop_backs)
	5) Supports 'LIFO' stack order operations.
	Note:
	   this container is only offered in C++11 & higher versions since 
	   its performance heavily relies on "move semantics"
*/
#ifndef SEGMENTED_VECTOR_GUARD
#define SEGMENTED_VECTOR_GUARD 1

#include "Vector.hpp" //acts as handler class for main array of pointers to fixed_size arrays in heap
#include "../Stacks_&_Queues/HF_Stack.hpp" //acts as 1D fixed_size array chunk stored in heap as object

template<typename T, size_t chunk_size=1>
class Segmented_Vector{//same as one-sided implementation of custom segmented_deque or STL::deque
	typedef Segmented_Vector __SV;
	typedef HF_Stack<T, chunk_size> chunk_type;
	
	/* Private Member Attributes */
	size_t _size;
	Vector<chunk_type> data_chunks;//stores chunks of data-buffer on heap
	
public:
	/*** Constructors & Assignment Operators ***/
	template<typename... _T>
	Segmented_Vector(size_t n=0, _T&&... val)noexcept://default & emplaced fill ctor
		_size(n){
		if(n>data_chunks.max_capacity) throw false;//exception safety
		if(n--){
			size_t total_chunks=n/chunk_size+1;
			data_chunks.reserve(total_chunks--);
			while(total_chunks--)//loops total_chunks-1 times
				data_chunks.emplace_back(chunk_type(chunk_size, std::forward<_T>(val)...));
			//insert remaining copies of 'val' in last chunk:
			data_chunks.emplace_back(chunk_type(n%chunk_size+1, std::forward<_T>(val)...));
		}
	}
	
	//copy-semantics (deep copy operations):
	Segmented_Vector(const __SV& other)noexcept://copy ctor
		data_chunks(other.data_chunks), _size(other._size){}
	
	__SV& operator=(const __SV& other)noexcept{//copy assignment operator
		data_chunks=other.data_chunks;
		_size=other._size;
		return *this;
	}
	
	//move-semantics (shallow copy operations):
	Segmented_Vector(__SV&& other)noexcept://move ctor
		data_chunks(std::move(other.data_chunks)), _size(other._size){ other._size=0; }
	
	__SV& operator=(__SV&& other)noexcept{//move assignment operator
	  	data_chunks=std::move(other.data_chunks);
  		_size=other._size; other._size=0;
		return *this;
	}
	
	//move initializer_list ctor:
	template<typename _T, size_t N>
	Segmented_Vector(_T (&&list)[N])noexcept://works best for r-values
		data_chunks(N?(N-1)/chunk_size+1:0),//default constructs r-value empty HF_Stack<T> objects
		_size(0){
		if(!N) return;//empty list exception safety
		size_t j;//represents total elements in current chunk
		for(size_t i=0;i<(N-1)/chunk_size;++i)//loops total_chunks-1 times
			for(j=chunk_size;j--;)
				data_chunks[i].push(std::move(list[_size++]));//elements of list are move constructed
		//insert remaining elements in last chunk:
		for(j=(N-1)%chunk_size+1;j--;)
			data_chunks.back().push(std::move(list[_size++]));//move constructed
	}
	
 	/*** Accessors ***/
	T& operator[](size_t n){//gives read & write both access
		return data_chunks[n/chunk_size][n%chunk_size];
	}
	const T& operator[](size_t n)const{//gives only read access
		return data_chunks[n/chunk_size][n%chunk_size];
	}
	
	T* operator+(size_t n){//returns address of nth first pointed element
		return data_chunks[n/chunk_size]+(n%chunk_size);
	}
	const T* operator+(size_t n)const{
		return data_chunks[n/chunk_size]+(n%chunk_size);
	}
	
	T* operator-(size_t n){//returns address of nth last pointed element
		return data_chunks[(_size-1-n)/chunk_size]+((_size-1-n)%chunk_size);
	}
	const T* operator-(size_t n)const{
		return data_chunks[(_size-1-n)/chunk_size]+((_size-1-n)%chunk_size);
	}
	
	T& front(){ return data_chunks[0][0]; }
	const T& front()const{ return data_chunks[0][0]; }
	
	T& back(){ return data_chunks[(_size-1)/chunk_size].peek(); }
	const T& back()const{ return data_chunks[(_size-1)/chunk_size].peek(); }
	
	T& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if(n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return df?data_chunks[(_size-1-n)/chunk_size][(_size-1-n)%chunk_size]:
				  data_chunks[n/chunk_size][n%chunk_size];
	}
	const T& at(size_t n, bool df=false)const{
		if(n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return df?data_chunks[(_size-1-n)/chunk_size][(_size-1-n)%chunk_size]:
				  data_chunks[n/chunk_size][n%chunk_size];
	}
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'size()==true' for 'front' & 'back' accessors.
		2) use condition 'n<size()' for '[]', '+' & '-' operator accessors.
	  Side Note:
		- passing -ve index means getting illegal memory access, hence
		  all random accessors have unsigned index parameter.
	*/
	
	size_t size()const{ return _size; }
	size_t capacity()const{ return data_chunks.size()*chunk_size; }
	
	bool empty()const{ return !_size; }
	
	/*** Modifiers ***/
	template<typename... _T>
	void push_back(_T&&... val){//constructs element (directly) at last position [complexity: O(1)]
		if(_size>=capacity())
			data_chunks.emplace_back();//default constructs r-value empty HF_Stack<T> object
		data_chunks[_size++/chunk_size].push(std::forward<_T>(val)...);
	}
	template<typename _T>
	void insert(_T&& val, size_t n=0){//O(N-n) complexity [similar to: push_front (when n=0)]
		if(n>_size) return;
		if(_size>=capacity())
			data_chunks.emplace_back();
		for(__int64 i=data_chunks.size()-2, N=n/chunk_size;i>=N;--i){//loops 'total_chunks-n' times
			data_chunks[i+1].insert(std::move(data_chunks[i].peek()));
			data_chunks[i].pop();
		}
		data_chunks[n/chunk_size].insert(std::forward<_T>(val), n%chunk_size);
		++_size;
	}
	void pop_back(){//removes element from last position [complexity: O(1)]
		if(!_size) return;//empty segmented_vector exception safety
		if(--_size%chunk_size)//if more than 1 elements are present in last chunk
			data_chunks[_size/chunk_size].pop();//then remove the last element
		else//otherwise
			data_chunks.pop_back();//completely remove the last chunk {contains only 1 element at this point}
	}
	void erase(size_t n=0){//O(N-n) complexity [similar to: pop_front (when n=0)]
		if(n>=_size) return;
		data_chunks[n/chunk_size].erase(n%chunk_size);
		for(size_t i=n/chunk_size;i<data_chunks.size()-1;++i){//loops 'total_chunks-n' times
			data_chunks[i].push(std::move(data_chunks[i+1][0]));
			data_chunks[i+1].erase();
		}
		if(!(--_size%chunk_size))
			data_chunks.pop_back();
	}
	bool reserve(size_t n){//only increases capacity (i.e. doesn't construct values)
		if(--n>data_chunks.max_capacity) return true;
		while(data_chunks.size()<n/chunk_size+1)
			data_chunks.emplace_back();
		return false;
	}
	template<typename... _T>
	void resize(size_t n, _T&&... val){//doesn't decrease the capacity (i.e. no chunk gets released)
		if(reserve(n)) return;
	    while(_size<n)
	    	data_chunks[_size++/chunk_size].push(std::forward<_T>(val)...);
		while(_size>n)
			data_chunks[--_size/chunk_size].pop();
	}
	chunk_type release_chunk(size_t n=0){//removes front chunk by default [complexity: O(N-n)]
		if(n>=data_chunks.size()) return chunk_type();//bound exception safety (i.e. returns empty object)
		_size-=data_chunks[n].size();
		chunk_type c=std::move(data_chunks[n]);
		data_chunks.erase(n);
		return c;//no need for explicit move as compiler itself performs R.V.O (Return Value Optimization)
	}
	void insert_chunk(chunk_type&& c, size_t n=0){//inserts chunk at front by default
		/* WARNING: NOT ALL CASES ARE HANDLED */
		if(n>data_chunks.size()) return;//bound exception safety
		size_t chunk_position=_size/chunk_size;//must be stored at this point (since _size will be modified)
		if(n>=chunk_position){//complexity: O(1)
			_size+=c.size();
			data_chunks.emplace_back(std::move(c)); 
			if(chunk_position) swap(data_chunks.back(), data_chunks[chunk_position]);
		}
		else{//complexity: O(N-n)
			if(c.size()!=chunk_size) return;//chunk inserted before last-one must be fully constructed
			data_chunks.insert(std::move(c), n);
			_size+=chunk_size;
		}
	}
	void shrink_to_fit(){//opppsite to reserve method (i.e. sets capacity near to size w.r.t chunk_size)
		while((_size-1)/chunk_size+1<data_chunks.size())
			data_chunks.pop_back();
	}
	void clear(){ _size=0; data_chunks.clear(); }
	
	/*** Comparators ***/
	bool operator==(const __SV& other)const{
		if(_size!=other._size)
			return false;
		for (size_t i=0;i<data_chunks.size();++i)
			if (!(data_chunks[i]==other.data_chunks[i]))
				return false;
		return true;
	}
	bool operator!=(const __SV& other)const{ return !(*this==other); }
	
	bool operator<(const __SV& other)const{//follows lexicographical-order (Dictionary order)
		size_t i=0;
		for (;i<data_chunks.size();++i)
			if(i==other.data_chunks.size()||data_chunks[i]>other.data_chunks[i])
				return false;
			else if(data_chunks[i]<other.data_chunks[i])
				return true;
		return i!=other.data_chunks.size();
	}
	bool operator>(const __SV& other)const{ return other<*this; }
	bool operator<=(const __SV& other)const{ return !(other<*this); }
	bool operator>=(const __SV& other)const{ return !(*this<other); }
	
 	/*** Iterators ***/
private:
	template<typename CT,//chunk_type
			 typename ET>//element_type
 	class SV_Base_Iterator{//handles both const & non_const versions
 		typedef SV_Base_Iterator __self;
 		
 	protected:
 		CT* ptr;//points main (0th) address of 1D vector
		__int64 index;//points current element index
		
    	SV_Base_Iterator(CT* main_ptr, //parameterized ctor (default)
						 __int64 element_index)noexcept:
			ptr(main_ptr), index(element_index){}
		
 	public:
 		/* accessors (getters & setters) */
		ET& operator*()const{ return ptr[index/chunk_size][index%chunk_size]; }
		ET* operator&()const{ return ptr[index/chunk_size]+(index%chunk_size); }
		
		ET& operator[](__int64 n)const{ return ptr[(n+index)/chunk_size][(n+index)%chunk_size]; }
		
		/* comparators (comparison operators) */
		bool operator==(const __self& other)const{ return index==other.index; }
		bool operator!=(const __self& other)const{ return index!=other.index; }
	};
	
	template<typename CT, typename ET>
	class SV_Iterator final://traverses in forward direction
		public SV_Base_Iterator<CT, ET>{
		
		typedef SV_Iterator __self;
		typedef SV_Base_Iterator<CT, ET> base;
		
	public:
    	SV_Iterator(CT* main_ptr=nullptr, //default & parameterized ctor
					__int64 element_index=0)noexcept:
			base(main_ptr, element_index){}
		
		/* modifiers (arithmetic operators) */
		//prefix operators:
		__self& operator++(){ ++base::index; return *this; }
		__self& operator--(){ --base::index; return *this; }
		
		//postfix operator:
		__self operator++(int){ __self temp(*this); ++base::index; return temp; }
		__self operator--(int){ __self temp(*this); --base::index; return temp; }
		
		__self& operator+=(__int64 n){ base::index+=n; return *this; }
		__self& operator-=(__int64 n){ base::index-=n; return *this; }
		
		__self operator+(__int64 n){ return __self(base::ptr, base::index+n); }
		__self operator-(__int64 n){ return __self(base::ptr, base::index-n); }
		
 		friend __self operator+(__int64 n, const __self& other){
		 	return __self(other.base::ptr, other.base::index+n);
		}
		
		__int64 operator-(const __self& other)const{ return base::index-other.base::index; }
		//note: returns difference_type (required for some STL::algorithms)
		
		/* (additional) comparators */
		bool operator>(const __self& other)const{ return base::index>other.base::index; }
		bool operator<(const __self& other)const{ return base::index<other.base::index; }
		bool operator>=(const __self& other)const{ return base::index>=other.base::index; }
		bool operator<=(const __self& other)const{ return base::index<=other.base::index; }
	};
	
	template<typename CT, typename ET>
	class SV_Reverse_Iterator final://traverses in backward direction
		public SV_Base_Iterator<CT, ET>{
		
		typedef SV_Reverse_Iterator __self;
		typedef SV_Base_Iterator<CT, ET> base;
		
	public:
    	SV_Reverse_Iterator(CT* main_ptr=nullptr, //default & parameterized ctor
							__int64 element_index=0)noexcept:
			base(main_ptr, element_index){}
		
		/* modifiers (arithmetic operators) */
		__self& operator++(){ --base::index; return *this; }//prefix operator
		__self& operator--(){ ++base::index; return *this; }
		
		__self operator++(int){ __self temp(*this); --base::index; return temp; }
		__self operator--(int){ __self temp(*this); ++base::index; return temp; }
		
		__self& operator+=(__int64 n){ base::index-=n; return *this; }//postfix operator
		__self& operator-=(__int64 n){ base::index+=n; return *this; }
		
		__self operator+(__int64 n){ return __self(base::ptr, base::index-n); }
		__self operator-(__int64 n){ return __self(base::ptr, base::index+n); }
		
		friend __self operator+(__int64 n, const __self& other){
			return __self(other.base::ptr, other.base::index-n);
		}
		
		__int64 operator-(const __self& other)const{ return other.base::index-base::index; }
		
		/* (additional) comparators */
		bool operator>(const __self& other)const{ return base::index<other.base::index; }
		bool operator<(const __self& other)const{ return base::index>other.base::index; }
		bool operator>=(const __self& other)const{ return base::index<=other.base::index; }
		bool operator<=(const __self& other)const{ return base::index>=other.base::index; }		
	};
	
public:
	//available segmented_vector iterator objects (const/non_const):
	typedef SV_Iterator<chunk_type, T> iterator;
	typedef SV_Iterator<const chunk_type, const T> const_iterator;
	
 	typedef SV_Reverse_Iterator<chunk_type, T> r_iterator;
 	typedef SV_Reverse_Iterator<const chunk_type, const T> const_r_iterator;
	
	//available segmented_vector iterator methods (const/non_const):
	iterator begin(){ return iterator(data_chunks+0, 0); }
	iterator end(){ return iterator(data_chunks+0, _size); }
	
	const_iterator begin()const{ return const_iterator(data_chunks+0, 0); }
	const_iterator end()const{ return const_iterator(data_chunks+0, _size); }
	
	r_iterator rbegin(){ return r_iterator(data_chunks+0, _size-1); }
	r_iterator rend(){ return r_iterator(data_chunks+0, -1); }
	
	const_r_iterator rbegin()const{ return const_r_iterator(data_chunks+0, _size-1); }
	const_r_iterator rend()const{ return const_r_iterator(data_chunks+0, -1); }
	
	//reversely traverse segmented_vector using these methods (inside range-based loop):
	reverse_iterator_adapter<__SV, r_iterator> r_iterator_adapter(){ 
		return reverse_iterator_adapter<__SV, r_iterator>(*this);
	}
	reverse_iterator_adapter<const __SV, const_r_iterator> r_iterator_adapter()const{
		return reverse_iterator_adapter<const __SV, const_r_iterator>(*this);
	}
	
	/*** Overloaded 'cin/cout' Methods ***/
	friend std::ostream& operator<<(std::ostream& out, const __SV& self){
		for(size_t i=0;i<self.data_chunks.size();++i)
			out<<self.data_chunks[i];
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __SV& self){
		for(size_t i=0;i<self.data_chunks.size();++i)
			in>>self.data_chunks[i];
		return in;
	}
};

#endif
