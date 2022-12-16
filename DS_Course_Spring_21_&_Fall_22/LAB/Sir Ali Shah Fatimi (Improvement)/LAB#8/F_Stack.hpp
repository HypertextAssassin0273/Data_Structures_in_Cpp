/* Important Notes:
	1) uses 'object mapping technique' for saving extra inital value construction cost
 	   & allows us to destruct objects in stack when not in use.
 	   [ref: 'mapping objects' with 'placement new operator' in c++]
	2) '(T*)(data+sizeof(T)*n)' returns address of mapped object 'T' at 'n' index.
*/
#ifndef F_STACK_GUARD
#define F_STACK_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define noexcept
#endif

template<typename T, size_t _capacity=1>
class F_Stack{//Fixed {Size} Stack (LIFO order)
	typedef F_Stack __FS;
	
	/* private member attributes */
	size_t current;//current index {ptr}
	unsigned char data[_capacity*sizeof(T)];//allocates memory for 'N' elements in bytes on local data buffer
public:
	/* default constructors */
#if __cplusplus >= 201103L
	template<typename... _T>
	F_Stack(size_t n=0, _T&&... attributes)noexcept://default & emplaced fill ctor
		current(n>_capacity?throw:0){
		while(current<n)
			new(data+sizeof(T)*current++) T(std::forward<_T>(attributes)...);//perfect forwarding
	}
#else
	F_Stack(size_t n=0, const T& value=T())://default & fill ctor
		current(n>_capacity?throw:0){
		while(current<n)
			new(data+sizeof(T)*current++) T(value);
	}
#endif
	
	/* copy semantics */
	F_Stack(const __FS& other)noexcept://copy ctor
		current(0){
			while(current<other.current)
				new(data+sizeof(T)*current++) T(other[current]);
	}
	__FS& operator=(const __FS& other)noexcept{//copy assignment operator
		if(this!=&other){//self-assignment protection
			clear();
			for(current=0;current<other.current;++current)
				new(data+sizeof(T)*current) T(other[current]);
		}
		return *this;
 	}
 	
#if __cplusplus >= 201103L
 	/* move semantics (performs shallow copy for stored values) */
	F_Stack(__FS&& other)noexcept://move ctor
		current(0){
			while(current<other.current)
				new(data+sizeof(T)*current++) T(std::move(other[current]));
			other.current=0;
	}
	__FS& operator=(__FS&& other)noexcept{//move assignment operator
		if(this!=&other){//self-assignment protection
			clear();
			for(current=0;current<other.current;++current)
				new(data+sizeof(T)*current) T(std::move(other[current]));
			other.current=0;
		}
		return *this;
 	}

	/* move initializer_list constructor */
 	template<typename _T, size_t N>
	F_Stack(_T (&&list)[N])noexcept://works best for r-values
		current(N>_capacity?throw:0){
		for(;current<N;++current)
			new(data+sizeof(T)*current) T(std::move(list[current]));//elements of list are move constructed
	}
#endif
	
	/* accessors (getters & setters) */
	size_t size()const{ return current; }
	size_t capacity()const{ return _capacity; }
	
	T& peek(){ return *(T*)(data+sizeof(T)*(current-1)); }//gives read & write both access
	const T& peek()const{ return *(T*)(data+sizeof(T)*(current-1)); }//gives read access only
	
	T& operator[](size_t n){ return *(T*)(data+sizeof(T)*n); }
	const T& operator[](size_t n)const{ return *(T*)(data+sizeof(T)*n); }
	
	T* operator+(size_t n){ return (T*)(data+sizeof(T)*n); }//returns address of nth first pointed element
	const T* operator+(size_t n)const{ return (T*)(data+sizeof(T)*n); }
	
	T* operator-(size_t n){ return (T*)(data+sizeof(T)*(current-1-n)); }//returns address of nth last pointed element
	const T* operator-(size_t n)const{ return (T*)(data+sizeof(T)*(current-1-n)); }
	
	T& at(size_t n, bool df=false){//ensures exception safety, [df: direction flag]
		if (n>=current){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(current-1-n):n));
	}
	const T& at(size_t n, bool df=false)const{
		if (n>=current){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return *(T*)(data+sizeof(T)*(df?(current-1-n):n));
	}
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'size()==true' for 'peek' accessor.
		2) use condition 'n<size()' for '[]', '+' & '-' operator accessors.
	  Side Note:
		- passing -ve index means getting illegal memory access, hence
		  all random accessors have unsigned index parameter.
	*/
	
	/* desicion checking methods */
	bool full()const{ return current==_capacity; }
	bool empty()const{ return !current; }
	
	/* stack general operations (modifiers) */
#if __cplusplus >= 201103L
	template<typename... types>
	void push(types&&... values){//O(1) complexity, Note: types&&... == universal_references
		if(current!=_capacity)
			new(data+sizeof(T)*current++) T(std::forward<types>(values)...);
			//constructing mapped_object format: new(memory_address) type_ctor();
	}
#else
	void push(const T& value){
    	if(current!=_capacity)
    		new(data+sizeof(T)*current++) T(value);
	}
#endif
	void pop(){//O(1) complexity
		if(current)
			((T*)(data+sizeof(T)*--current))->~T();//explicit dtor call
	}
	void clear(){
		while(current)
			((T*)(data+sizeof(T)*--current))->~T();
	}
		
	/* overloaded 'cout & cin' methods */
	friend std::ostream& operator<<(std::ostream& out, const __FS& self){
		for(size_t i=0;i<self.current;++i)
			out<<*(T*)(self.data+sizeof(T)*i)<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __FS& self){//updates existing values
		in.sync();//clears remaining content from buffer
		for(size_t i=0;i<self.current;++i)
			in>>*(T*)(self.data+sizeof(T)*i);
		return in;
	}
	
	/* destructor */
	~F_Stack(){ clear(); }
};

#endif
