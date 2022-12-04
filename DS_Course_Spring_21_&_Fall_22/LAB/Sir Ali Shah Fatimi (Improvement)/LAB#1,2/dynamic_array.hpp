#ifndef DYNAMIC_ARRAY_GUARD
#define DYNAMIC_ARRAY_GUARD 1

#include<iostream>

//note: this container only utilizes move semantics for optimize operations (for specific cases)
//tip: provides better functionalties for storing & using heap/dynamic resource based objects in optimized way

template<typename T>
class dynamic_array{//minimal approach for quickly using dynamic arrays in generalize format as sequence-container
	size_t _size;
	T *data;
public:
	template<typename... t>
	dynamic_array(t&&... attrbs)://default/variadic ctor (for taking values as std::initializer_list)
		_size(sizeof...(attrbs)),
		data(new T[_size]{std::forward<t>(attrbs)...}){}
	/*important-notes:
		1) this approach deprecates casting for (some number based) primitives
		   [e.g. DA<float>{1.3, 4.22, 2} => wont treat arguments as: {float,float,float},
		   		instead, it treats (in default checking manner) as: {double, double, int},
				making compiler to do additional casting to convert in: {float,float,float}]
		2) always perform 'perfect forwarding' with universal references,
		   in order to implement 'reference collapsing rules' efficiently.
	/*side-notes:
		1) std::forward => used for 'perfect forwarding'
		2) && => known as register/right/r value reference
		3) t&& => acts as 'universal reference'
		4) t&&... => acts as 'universal references'
	*/
	
	//copy semantics (i.e. rule of three)
	dynamic_array(const dynamic_array&)=delete;//disables (deep) copy ctor
	dynamic_array& operator=(const dynamic_array&)=delete;//disables (deep) copy assignment operator
	
	//move semantics (i.e. rule of five)
	dynamic_array(dynamic_array&& other)://move (shallow-copy) ctor
		_size(other._size),data(other.data){ //1) steal other's resources
		other._size=0; other.data=nullptr;	 //2) set other's resources to null state
	}
	dynamic_array& operator=(dynamic_array&& other){//move (shallow-copy) assignment operator
		if(this!=&other){//ensures self-assignment exception safety
			delete[] data; 						//1) clear existing resources
			_size=other._size; data=other.data; //2) steal other's resources
  			other._size=0; other.data=nullptr;	//3) set other's resources to null state
		}
		return *this;
	}
	
	T& operator[](size_t n){//accessor (getter + setter): gives read & write both access
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n < 0' can be excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return data[n];
	}
	const T& operator[](size_t n)const{//getter: gives read access only
		if (n>=_size){
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		return data[n];
	}
	const size_t& size()const{ return _size; }//getter
	
	friend std::ostream& operator<<(std::ostream& out,const dynamic_array& self){//overloaded cout (console output) method
		for(size_t i=0;i<self._size;++i)
			out<<self.data[i]<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,dynamic_array& self){//overloaded cin (console input) method
		in.sync();//i.e. clears remaining content from buffer
		for(size_t i=0;i<self._size;++i)
			in>>self.data[i];
		return in;
	}
	
	~dynamic_array(){ delete[] data; }//dtor
};

template<typename T>
using DA=dynamic_array<T>;//redefining as short-form of actual name

#endif
