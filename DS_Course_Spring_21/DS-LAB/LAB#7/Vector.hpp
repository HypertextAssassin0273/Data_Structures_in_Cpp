#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#endif

template<typename T>
class Vector{//i.e. same as Dynamic Safe Array
	typedef unsigned char __uchar;
	typedef unsigned int __uint32;
	typedef unsigned long long __uint64;
	
	static const __uint32 max_capacity=~((__uint32)0);
	//Tip: negate the min. value with extension (by typecasting) to get max. of any predefined datatype.
	__uint32 _size,_capacity;
	__uchar *data;//i.e. data-buffer on heap

public:
	Vector(__uint64 n=0)noexcept://i.e. default ctor
		_size((n>max_capacity)?throw:n),_capacity(_size),
		data((_size>0)?new __uchar[sizeof(T)*_size]:nullptr){//i.e. allocating new buffer 'data'
		for(__uint64 i=0;i<_size;++i)
			new(data+sizeof(T)*i) T();
		/*Note: empty-brackets initializes primitives with '0','\0',"\0" & for non-primitives,
				it invokes default ctors */
	}
#if __cplusplus >= 201103L
	Vector(std::initializer_list<T> list)noexcept://i.e. ctor for initializer-list (C++11 Construct)
		_size(0),_capacity(list.size()),data(new __uchar[sizeof(T)*_capacity]){
		for(const auto& it:list)//i.e. initializer_list can only be traversed with iterators
			new(data+sizeof(T)*_size++) T(it);//i.e. performs copy of list iterator's elements
	}
#endif
	
	T& operator[](__uint32 n)const{
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		std::terminate();
		}
		return *(T*)(data+sizeof(T)*n);
	}
	__uint32 size()const{ return _size; }
 	__uint32 capacity()const{ return _capacity; }
	
private:
	void reallocate(__uint64 n){
		__uchar* new_data=new __uchar[sizeof(T)*n];
		for(__uint64 i=0;i<(sizeof(T)*_size);++i)
			new_data[i]=data[i];//i.e. copying buffer (byte by byte)
		/*Note: 
			->this saves us from extra constructions & destructions
			->also copies ptr addresses, so no loss for non-P.O.D mapped objs */
		delete[] data;
		data=new_data;
	}
public:
    void push_back(const T& val){
    	if(_size>=_capacity)
			reallocate(_capacity?_capacity*=2:++_capacity);
			//i.e. if capacity is '0' then set it to '1' else twice it
    	new(data+sizeof(T)*_size++) T(val);
	}
	void clear(){
		while(_size)
			((T*)(data+sizeof(T)*--_size))->~T();//i.e. explicit dtor call
		/*Note: we can destruct objects of 'T' type that are mapped on buffer 'data'
				by simply type-casting the buffer to object's ptr type */
	}
#if __cplusplus >= 201103L
	static void swap(T &xp,T &yp){
    	T temp=move(xp);//i.e. move ctor for temp gets invoked
    	xp=move(yp);//i.e. move ctor gets invoked for xp's pointed obj
    	yp=move(temp);//i.e. move ctor gets invoked for yp's pointed obj
	}
#else
	static void swap(T &xp,T &yp){
    	T temp=xp;
    	xp=yp;
    	yp=temp;
	}
#endif
	void sort(bool=true);
	
	friend ostream& operator<<(ostream& out,const Vector& vec){
		for(__uint32 i=0;i<vec._size;++i)
			out<<*(T*)(vec.data+sizeof(T)*i)<<" ";//i.e. vec[i] == *(T*)(vec.data+sizeof(T)*i)
		out<<endl;
		return out;
	}
	friend istream& operator>>(istream& in,Vector& vec){
		for(__uint32 i=0;i<vec._size;++i)
			in>>*(T*)(vec.data+sizeof(T)*i);
		return in;
	}
	
	~Vector(){//i.e. dtor
		clear();
		delete[] data;
	}
};
