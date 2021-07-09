#if __cplusplus < 201103L
#define noexcept
#endif

template<typename T,unsigned int __size=1>
class Array{
	typedef unsigned int __uint32;
	
	static const __uint32 max_capacity=~((__uint32)0);
	//Tip:  negate the min. value with extension (by typecasting) to get max. of any predefined datatype.
	__uint32 _size;
	T data[__size];
public:
	Array()noexcept://i.e. variadic template ctor as initializer-list ctor
		_size((__size>max_capacity)?throw:__size),data(){}
#if __cplusplus >= 201103L
    template<typename... _T>
	Array(_T&&... data)noexcept://i.e. default ctor	
		_size((__size>max_capacity)?throw:__size),data{std::forward<_T>(data)...}{}
#endif

	T& operator[](__uint32 n)const{
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		std::terminate();
		}
		return data[n];
	}
 	__uint32 size()const{ return _size; }
	
	void sort(bool=true);
	
	static void swap(T &xp,T &yp){
    	T temp=xp;
    	xp=yp;
    	yp=temp;
	}
	
	friend ostream& operator<<(ostream& out,const Array& arr){
		for(__uint32 i=0;i<arr._size;++i)
			out<<arr.data[i]<<" ";
		out<<endl;
		return out;
	}
	friend istream& operator>>(istream& in,Array& arr){
		for(__uint32 i=0;i<arr._size;++i)
			in>>arr.data[i];
		return in;
	}
};
