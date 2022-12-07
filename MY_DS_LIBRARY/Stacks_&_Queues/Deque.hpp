/* Dynamic Size Circular Array Deque (Double Ended Queue) */
/* Highlights:
	1) supports all 'queue' & 'stack' order operations. [e.g. FIFO, LILO, LIFO, FILO]
	2) all 'acessors' give guranteed access in O(1) amount of time.
	3) uses local fixed-array in 'circular manner' in order to get better performance.
 	   [i.e. O(1) complexity for any operation done on either end]
	4) uses 'object mapping technique' for saving extra inital value construction cost
 	   & allows us to destruct objects in circular array when not in use.
 	   [ref: 'mapping objects' with 'placement new operator' in c++]
 	5) elements are mapped/constructed on dynamically allocated buffer.
 	6) 'move semantics' applicable with C++11 settings.
 	7) all neccessary vector-class like 'modifiers' & 'iterators' are provided.
 	8) shifting modifiers take O((N-n)/2) amount of time insead of O(N-n).
*/
#ifndef DEQUE_GUARD
#define DEQUE_GUARD 1

#include "../Utilities/Swap.hpp"
#include "../Utilities/Reverse_Iterator_Adapter.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>//element data-type
class Deque{
	typedef Deque __D;
	typedef unsigned char u_char;
	
	/*** Private Member Attributes ***/
	size_t _capacity,//keeps track of circular range (i.e. max available memory space on heap)
		   _size;//keeps track of constructed element count
	__int64 _front,//index ptr (points first value)
		    _back;//index ptr (points last value)
	u_char *data;//points data buffer on heap
public:
	static const unsigned int max_capacity=~((unsigned int)0);//range: 0 to 4,294,967,295
	
	/*** Default & Fill Constructor ***/
	Deque(__int64 n=0, const T& value=T())noexcept:
		_capacity((n>max_capacity)?throw:n), _size(0), _front(n--?0:-1), _back(-1),
		data(new u_char[sizeof(T)*_capacity]){//allocates memory for 'N' elements in bytes
		while(_back<n)
			new(data+sizeof(T)*(_back=_size++)) T(value);
	}//Note: T() invokes default ctor of type 'T' & returns it as rvalue
	
	/*** Copy Semantics (deep copy) ***/
	Deque(const __D& other)noexcept://copy ctor
		_capacity(other._capacity), _size(other._size), _front(other._front),
			data(new u_char[sizeof(T)*_capacity]){
			while(_size--){
				_back=_front++%_capacity;
				new(data+sizeof(T)*_back) T(*(T*)(other.data+sizeof(T)*_back));//copy constructing values from 'other'
			}
			_size=other._size; _front=other._front; _back=other._back;
	}
	__D& operator=(const __D& other)noexcept{//copy assignment operator
		if(this!=&other){//self-assignment protection
			clear(); delete[] data;//clear existing resources
			data=new u_char[sizeof(T)*(_capacity=other._capacity)];//allocate new buffer
			_front=other._front; _size=other._size;//initializing for below loop
 			while(_size--){
				_back=_front++%_capacity;
				new(data+sizeof(T)*_back) T(*(T*)(other.data+sizeof(T)*_back));//copy constructing values from 'other'
			}
			_size=other._size; _front=other._front; _back=other._back;//reseting to original
		}
		return *this;
 	}
 	
#if __cplusplus >= 201103L
 	/*** Move Semantics (shallow copy) ***/
	Deque(__D&& other)noexcept://move ctor
		data(other.data), _capacity(other._capacity), _size(other._size),
		_front(other._front), _back(other._back){//steal others's resources
			other.data=nullptr;//set others's resources to null state
			other._capacity=other._size=0; other._front=other._back=-1;
	}
	__D& operator=(__D&& other)noexcept{//move assignment operator
		if(this!=&other){
			clear(); delete[] data;//clear existing resources
			data=other.data; _capacity=other._capacity; _size=other._size;//steal others's resources
			_front=other._front; _back=other._back;
			other.data=nullptr;//set others's resources to null state
			other._capacity=other._size=0; other._front=other._back=-1;
		}
		return *this;
 	}
 	
 	/*** Move Initializer List Constructor ***/
 	template<typename _T, __int64 N>
	Deque(_T (&&list)[N])noexcept://works best for r-values
		_capacity((N>max_capacity)?throw:N), _size(0), _front(N?0:-1), _back(-1),
		data(new u_char[sizeof(T)*_capacity]){
		while(_back<N-1){
			_back=_size++;
			new(data+sizeof(T)*_back) T(std::move(list[_back]));//elements of list are move constructed
		}
	}
#endif
	
	/*** Accessors (Getters & Setters) ***/
	size_t size()const{ return _size; }
	size_t capacity()const{ return _capacity; }
	
	T& front(){ return *(T*)(data+sizeof(T)*_front); }//gives read & write both access
	const T& front()const{ return *(T*)(data+sizeof(T)*_front); }//gives read access only
	
	T& back(){ return *(T*)(data+sizeof(T)*_back); }
	const T& back()const{ return *(T*)(data+sizeof(T)*_back); }
	
	T& operator[](size_t n){ return *(T*)(data+sizeof(T)*((_front+n)%_capacity)); }
	const T& operator[](size_t n)const{ return *(T*)(data+sizeof(T)*((_front+n)%_capacity)); }
	
	T* operator+(size_t n){//returns address of nth first pointed element
		return (T*)(data+sizeof(T)*((_front+n)%_capacity));
	}
	const T* operator+(size_t n)const{ return (T*)(data+sizeof(T)*((_front+n)%_capacity)); }
	
	T* operator-(size_t n){//returns address of nth last pointed element
		return (T*)(data+sizeof(T)*((_back-n)%_capacity));
	}
	const T* operator-(size_t n)const{ return (T*)(data+sizeof(T)*((_back-n)%_capacity)); }
	
	T& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if (n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*((df?_back-n:_front+n)%_capacity));
	}
	const T& at(size_t n, bool df=false)const{
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*((df?_back-n:_front+n)%_capacity));
	}
	/*Important Note (for ensuring exception safety manually):
		- use condition 'empty()==false' or 'size()==true' before using accessors
		  which provide access to data-elements.
	  Side Notes:
	    1) '(T*)(data+sizeof(T)*n)' returns address of mapped object 'T' at 'n' index.
		2) (_front+n)%_capacity => returns 'nth' index forward from '1st' pointed value in circular order.
		3) there is no sense for having -ve index accessing in circular array,
		   hence all random accessors have unsigned index parameter.
	*/
	
	/*** Desicion Checking Methods ***/
	bool full()const{ return _size==_capacity; }//OR: (!_front&&_back==_capacity-1)||(_front==_back+1);
	bool empty()const{ return !_size; }//OR: _front==-1;
	
	/*** Deque General Operations (Modifiers) ***/
private:
	bool reallocate(size_t n){//Note: must remain 'private' since it's a helper function (containing depandant workflows)
		if(n>max_capacity) return true;
		u_char* new_data=new u_char[sizeof(T)*n];
		for(size_t i=0, j=_front;i!=_size;++i, ++j){//copying/moving previous data
		#if __cplusplus >= 201103L
			new(new_data+sizeof(T)*i) T(std::move(*(T*)(data+sizeof(T)*(j%_capacity))));//move construction
			//Note: 'std::move' is used to convert lvalue-resources to rvalues
		#else
			new(new_data+sizeof(T)*i) T(*(T*)(data+sizeof(T)*(j%_capacity)));//copy construction (slower process)
		#endif
			((T*)(data+sizeof(T)*(j%_capacity)))->~T();
			//explicit dtor call for manually destructing previously stored obj from data-buffer
		}
		delete[] data; data=new_data; _capacity=n;
		_front=(_size?0:-1); _back=_size-1;
		return false;
	}
public:
#if __cplusplus >= 201103L
	template<typename... type>
	void push_front(type&&... attrbs){//constructs element (directly) at first position [complexity: O(1)]
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		_front=(_front==-1?_back=0:(_front==0?_capacity-1:_front-1));
		//if only 1 value is present, then initialize both, otherwise, decrease front in circular order.
		new(data+sizeof(T)*_front) T(std::forward<type>(attrbs)...); ++_size;
		//constructing mapped_object format: new(memory_address) type_ctor();
	}
	template<typename... type>
	void push_back(type&&... attrbs){//constructs element (directly) at last position [complexity: O(1)]
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		_back=(_back==-1?_front=0:(_back+1)%_capacity);//OR: (_back==_capacity-1?0:_back+1);
		//if only 1 value is present, then initialize both, otherwise, increase back in circular order.
		new(data+sizeof(T)*_back) T(std::forward<type>(attrbs)...); ++_size;
	}
	template<typename type>
	void insert(type&& value, size_t n=0){//O((N-n)/2) complexity [works as: push_front (when n=0), push_back (when n=N)]
		if(n>_size) return;//exception safety check
		if(!n){ push_front(std::forward<type>(value)); return; }
		if(n==_size){ push_back(std::forward<type>(value)); return; }
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		if(n<=_size/2){//choosing partition for minimum swaps/shifts
			new(data+sizeof(T)*(_front?_front-1:_capacity-1)) T(std::move(front()));//move 1st value to new first position
			size_t nth_idx=(_front+--n)%_capacity;//storing nth position index (since we can't track afterwards)
			for(size_t i=_front;n;++i,--n)//shifting values forwards (starting from old first position)
				swap(*(T*)(data+sizeof(T)*(i%_capacity)), *(T*)(data+sizeof(T)*((i+1)%_capacity)));
			*(T*)(data+sizeof(T)*nth_idx)=std::forward<type>(value);//insert new value at nth index (copy/move assignment)
			_front=(_front?_front-1:_capacity-1); ++_size;//update front for new insertion
		}
		else{
			new(data+sizeof(T)*((_back+1)%_capacity)) T(std::move(back()));//move last value to new last position
			size_t nth_idx=(_front+n)%_capacity;//storing nth position index (since we can't track afterwards)
			for(size_t i=_back+1;n!=_size-1;++n){//shifting values backwards (starting from old last position)
				i=(i?i-1:_capacity-1);//validating back tracking index
				swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i-1==-1?_capacity-1:i-1)));
			}
			*(T*)(data+sizeof(T)*nth_idx)=std::forward<type>(value);//insert new value at nth index (copy/move assignment)
			_back=(_back+1)%_capacity; ++_size;//update back for new insertion
		}
	}
#else
	void push_front(const T& value){
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		_front=(_front==-1?_back=0:(_front==0?_capacity-1:_front-1));
		new(data+sizeof(T)*_front) T(value); ++_size;
	}
	void push_back(const T& value){
    	if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
    	_back=(_back==-1?_front=0:(_back+1)%_capacity);
		new(data+sizeof(T)*_back) T(value); ++_size;
	}
	void insert(const T& value, size_t n=0){
		if(n>_size) return;//exception safety check
		if(!n){ push_front(value); return; }
		if(n==_size){ push_back(value); return; }
		if(_size==_capacity)
			if(reallocate(_capacity?_capacity*2:1)) return;
		if(n<=_size/2){
			new(data+sizeof(T)*(_front?_front-1:_capacity-1)) T(front());
			size_t nth_idx=(_front+--n)%_capacity;
			for(size_t i=_front;n;++i,--n)
				swap(*(T*)(data+sizeof(T)*(i%_capacity)), *(T*)(data+sizeof(T)*((i+1)%_capacity)));
			*(T*)(data+sizeof(T)*nth_idx)=value;
			_front=(_front?_front-1:_capacity-1); ++_size;
		}
		else{
			new(data+sizeof(T)*((_back+1)%_capacity)) T(back());
			size_t nth_idx=(_front+n)%_capacity;
			for(size_t i=_back+1;n!=_size-1;++n){
				i=(i?i-1:_capacity-1);
				swap(*(T*)(data+sizeof(T)*i), *(T*)(data+sizeof(T)*(i-1==-1?_capacity-1:i-1)));
			}
			*(T*)(data+sizeof(T)*nth_idx)=value;
			_back=(_back+1)%_capacity; ++_size;
		}
	}
#endif
	void pop_front(){//removes element from first position [complexity: O(1)]
		if(!_size) return; --_size;
		((T*)(data+sizeof(T)*_front))->~T();//explicit dtor call
		_front=(_front==_back?_back=-1:(_front+1)%_capacity);//OR: (_front==_capacity-1?0:_front+1));
		//if only 1 value is left, then reset both, otherwise, increase front in circular order.
	}
	void pop_back(){//removes element from last position [complexity: O(1)]
		if(!_size) return; --_size;
		((T*)(data+sizeof(T)*_back))->~T();
		_back=(_front==_back?_front=-1:(_back==0?_capacity-1:_back-1));
		//if only 1 value is left, then reset both, otherwise, decrease back in circular order.
	}
	void erase(size_t n=0){//O((N-n)/2) complexity [works as: pop_front (when n=0), pop_back (when n=N)]
		if(n>=_size) return;//if not empty, then perform shifting from nth index
		if(n<_size--/2){//choosing partition for minimum swaps/shifts
			for(size_t i=_front+n;n!=0;--i,--n)//shifting values backwards (upto new first position)
				swap(*(T*)(data+sizeof(T)*(i%_capacity)), *(T*)(data+sizeof(T)*((i-1)%_capacity)));
			((T*)(data+sizeof(T)*_front))->~T();//remove/destruct first value
			_front=(_front==_back?_back=-1:(_front+1)%_capacity);//reset it or increase in circular order	
		}
		else{
			for(size_t i=_front+n;n!=_size;++i,++n)//shifting values forwards (upto new last position)
				swap(*(T*)(data+sizeof(T)*(i%_capacity)), *(T*)(data+sizeof(T)*((i+1)%_capacity)));
			((T*)(data+sizeof(T)*_back))->~T();//remove/destruct last value
			_back=(_front==_back?_front=-1:(_back==0?_capacity-1:_back-1));//reset it or decrease in circular order
		}
	}
	void clear(){
		while(_size--){
			((T*)(data+sizeof(T)*(_front++%_capacity)))->~T();
		}
		_front=_back=-1; _size=0;
	}
	void reserve(size_t n){
		if(n>_capacity) reallocate(n);
	}
	void resize(size_t n, const T& value=T()){
		if(n>_capacity)
			if(reallocate(n)) return;
		for(;_size<n;++_size){//construct till it reaches 'n' [i.e. constant push_backs]
			_back=(_back+1)%_capacity;
    		new(data+sizeof(T)*_back) T(value);
     	}
		for(;_size>n;--_size){//destruct till it reaches 'n' [i.e. constant pop_backs]
			((T*)(data+sizeof(T)*_back))->~T();
			_back=(_back==0?_capacity-1:_back-1);
		}
		if(!_size) _front=-1;
	}
	void shrink_to_fit(){//opppsite to reserve modifier
		if(_size<_capacity) reallocate(_size);
	}
	
	/*** Comparators ***/
	bool operator==(const __D& other)const{
		if(_size!=other._size) return false;
		size_t i=_front, j=other._front, n=_size;
		while(n--)
			if (*(T*)(data+sizeof(T)*(i++%_capacity))!=*(T*)(other.data+sizeof(T)*(j++%_capacity)))
	  			return false;
		return true;
	}
	bool operator!=(const __D& other)const{ return !(*this==other); }
	
	bool operator<(const __D& other)const{//follows lexicographical-order (Dictionary order)
		size_t n=0;
		for (size_t i=_front, j=other._front;n!=_size;i=(i+1)%_capacity, j=(j+1)%_capacity, ++n){
			if(n==other._size||*(T*)(other.data+sizeof(T)*j)<*(T*)(data+sizeof(T)*i))
				return false;
			else if(*(T*)(data+sizeof(T)*i)<*(T*)(other.data+sizeof(T)*j))
				return true;
		}
		return n!=other._size;
	}
	bool operator>(const __D& other)const{ return other<*this; }
	bool operator<=(const __D& other)const{ return !(other<*this); }
	bool operator>=(const __D& other)const{ return !(*this<other); }
	
 	/*** Iterators ***/
private:
	template<typename _T>
	class D_Base_Iterator{
 		typedef D_Base_Iterator __self;
	 	
	protected:
		_T* ptr;//points base address of respective data buffer
		size_t cap;//keeps track of circular range
		__int64 elem_idx,//points current element index
				iter_idx;//keeps track of loop count
		
		D_Base_Iterator(_T* main_ptr, size_t capacity, //default parameterized ctor
						__int64 element_index, __int64 iterator_index)noexcept:
			ptr(main_ptr), cap(capacity), elem_idx(element_index), iter_idx(iterator_index){}
		
	public:
		/* accessors */
		_T& operator*()const{ return ptr[elem_idx%cap]; }
		_T* operator&()const{ return ptr+(elem_idx%cap); }
		
		/* comparators */
		bool operator==(const __self& other)const{ return iter_idx==other.iter_idx; }
		bool operator!=(const __self& other)const{ return iter_idx!=other.iter_idx; }
	};
	
	template<typename _T>
	class D_Iterator://traverses in forward direction
		public D_Base_Iterator<_T>{
		
		typedef D_Iterator __self;
		typedef D_Base_Iterator<_T> base;
		
	public:
		D_Iterator(_T* main_ptr=nullptr, size_t capacity=0, //default & parameterized ctor
				   __int64 element_index=0, __int64 iterator_index=0)noexcept:
			base(main_ptr, capacity, element_index, iterator_index){}
		
		/* (additional) accessor */
		_T& operator[](size_t i)const{ return base::ptr[(base::elem_idx+i)%base::cap]; }
		
		/* modifiers (arithmetic operators) */
		//prefix operators:
		__self& operator++(){ ++base::iter_idx; ++base::elem_idx; return *this; }
		__self& operator--(){ --base::iter_idx; --base::elem_idx; return *this; }
		
		//postfix operators:
		__self operator++(int){ __self temp(*this); ++base::iter_idx; ++base::elem_idx; return temp; }
		__self operator--(int){ __self temp(*this); --base::iter_idx; --base::elem_idx; return temp; }
		
		__self& operator+=(size_t i){ base::iter_idx+=i; base::elem_idx+=i; return *this; }
		__self& operator-=(size_t i){ base::iter_idx-=i; base::elem_idx-=i; return *this; }
		
		__self operator+(size_t i)const{ return __self(base::ptr, base::elem_idx+i, base::iter_idx+i); }
		__self operator-(size_t i)const{ return __self(base::ptr, base::elem_idx-i, base::iter_idx-i); }
		
		friend __self operator+(size_t i, const __self& other){
			return __self(base::ptr, other.elem_idx+i, other.iter_idx+i);
		}
		
		__int64 operator-(const __self& other)const{ return base::iter_idx-other.base::iter_idx; }
		//note: returns difference_type (required for some STL::algorithms)
		
		/* (additional) comparators */
		bool operator>(const __self& other)const{ return base::iter_idx>other.base::iter_idx; }
		bool operator<(const __self& other)const{ return base::iter_idx<other.base::iter_idx; }
		bool operator>=(const __self& other)const{ return base::iter_idx>=other.base::iter_idx; }
		bool operator<=(const __self& other)const{ return base::iter_idx<=other.base::iter_idx; }
	};
	
	template<typename _T>
	class D_Reverse_Iterator://traverses in backward direction
		public D_Base_Iterator<_T>{
	
		typedef D_Reverse_Iterator __self;
		typedef D_Base_Iterator<_T> base;
		
	public:
		D_Reverse_Iterator(_T* main_ptr=nullptr, size_t capacity=0, //default & parameterized ctor
						   __int64 element_index=0, __int64 iterator_index=0)noexcept:
			base(main_ptr, capacity, element_index, iterator_index){}
		
		/* (additional) accessor */
		_T& operator[](size_t i)const{ return base::ptr[(base::elem_idx-i)%base::cap]; }
		
		/* modifiers (arithmetic operators) */
		__self& operator++(){ --base::iter_idx; --base::elem_idx; return *this; }
		__self& operator--(){ ++base::iter_idx; ++base::elem_idx; return *this; }
		
		__self operator++(int){ __self temp(*this); --base::iter_idx; --base::elem_idx; return temp; }
		__self operator--(int){ __self temp(*this); ++base::iter_idx; ++base::elem_idx; return temp; }
		
		__self& operator+=(size_t i){ base::iter_idx-=i; base::elem_idx-=i; return *this; }
		__self& operator-=(size_t i){ base::iter_idx+=i; base::elem_idx+=i; return *this; }
		
		__self operator+(size_t i)const{ return __self(base::ptr, base::elem_idx-i, base::iter_idx-i); }
		__self operator-(size_t i)const{ return __self(base::ptr, base::elem_idx+i, base::iter_idx+i); }
		
		friend __self operator+(size_t i, const __self& other){
			return __self(base::ptr, other.elem_idx-i, other.iter_idx-i);
		}
		
		__int64 operator-(const __self& other)const{ return other.base::iter_idx-base::iter_idx; }
		
		/* (additional) comparators */
		bool operator>(const __self& other)const{ return base::iter_idx<other.base::iter_idx; }
		bool operator<(const __self& other)const{ return base::iter_idx>other.base::iter_idx; }
		bool operator>=(const __self& other)const{ return base::iter_idx<=other.base::iter_idx; }
		bool operator<=(const __self& other)const{ return base::iter_idx>=other.base::iter_idx; }
	};
	
public:
	//available deque iterator objects (const/non_const):
	typedef D_Iterator<T> iterator;
	typedef D_Iterator<const T> const_iterator;
	
 	typedef D_Reverse_Iterator<T> r_iterator;
 	typedef D_Reverse_Iterator<const T> const_r_iterator;
	
	//available deque iterator methods (const/non_const):
	iterator begin(){ return iterator((T*)data, _capacity, _front, 0); }
	iterator end(){ return iterator((T*)data, _capacity, _front, _size); }
	
	const_iterator begin()const{ return const_iterator((T*)data, _capacity, _front, 0); }
	const_iterator end()const{ return const_iterator((T*)data, _capacity, _front, _size); }
	
	r_iterator rbegin(){ return r_iterator((T*)data, _capacity, _back, _size-1); }
	r_iterator rend(){ return r_iterator((T*)data, _capacity, _back, -1); }
	
	const_r_iterator rbegin()const{ return const_r_iterator((T*)data, _capacity, _back, _size-1); }
	const_r_iterator rend()const{ return const_r_iterator((T*)data, _capacity, _back, -1); }
	
#if __cplusplus >= 201103L
	//reversely traverse deque using these methods (inside range-based loop):
	reverse_iterator_adapter<__D, r_iterator> r_iterator_adapter(){ 
		return reverse_iterator_adapter<__D, r_iterator>(*this);
	}
	reverse_iterator_adapter<const __D, const_r_iterator> r_iterator_adapter()const{
		return reverse_iterator_adapter<const __D, const_r_iterator>(*this);
	}
#endif
	
	/*** Overloaded 'cout & cin' Methods ***/
	friend std::ostream& operator<<(std::ostream& out, const __D& self){
		size_t i=self._front, n=self._size;
		while(n--)
			out<<*(T*)(self.data+sizeof(T)*(i++%self._capacity))<<' ';
			//out<<'\n'<<self._front<<' '<<self._back<<'\n';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __D& self){//updates existing values
		in.sync();//clears remaining content from buffer
		size_t i=self._front, n=self._size;
		while(n--)
			in>>*(T*)(self.data+sizeof(T)*(i++%self._capacity));
		return in;
	}
	
	/*** Destructor ***/
	~Deque(){ clear(); delete[] data; }
	
#if TYPE_CONVERTORS_GUARD
	friend class convert;
#endif
};

#endif
