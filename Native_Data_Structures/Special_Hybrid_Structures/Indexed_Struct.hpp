/* Indexed Structure or Array of Distinct Data-types (Special Contiguous Container) */
/*	Highlights:
	1) Theoretically, struct is mapped as array, in order to access its attributes at 
	   runtime with O(1) time complexity	
	2) Automatic deduction of max. attribute size for providing pagination-gap
	   in order to keep elements perfectly alligned in mapped-array
	Additional-Notes:
	1) Available only in C++11 & higher versions
	2) Explicit typecast required for accessing elements
*/
#ifndef INDEXED_STRUCT_GUARD
#define INDEXED_STRUCT 1

#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
#endif

/*************** work-around for getting max. size of types (at compile-time) ****************/
constexpr size_t _max(size_t a,size_t b){ return a>b?a:b; }

template<bool>
constexpr size_t max_of(){ return 0; }//i.e. overloaded base-case func for terminating condition

template<bool b,size_t size,size_t... sizes>
constexpr size_t max_of(){ return _max(size,max_of<b,sizes...>()); }
/********************************************************************************************/

template<typename... types>
struct indexed_struct{
	indexed_struct()noexcept://i.e. default ctor
		is_constructed(false){}
	indexed_struct(types... attributes)noexcept://i.e. optimized initializer-list ctor
		is_constructed(true){
		size_t index=0;
		bool expander[]{ (new(data+pagination*index++) types(std::move(attributes)),false)... };
	}	/*Note: Parameters are constructed on data-buffer using Lamba (array) expander instead of initializer-list
				since, it has some advantages over the initializor-list, like: 
					1) it can store elements of different data-types
					2) it doesn't cost us extra copy of elements
					3) it can be used for both copying & moving elements (efficiently)
		*/
	indexed_struct(const indexed_struct& other)noexcept://i.e. copy ctor
		is_constructed(true){
		size_t index=0;
		bool expander[]{ (new(data+pagination*index++) types(*(types*)(other+index)),false)... };
		
	}
	indexed_struct(indexed_struct&& other)noexcept://i.e. move ctor
		is_constructed(true){
		size_t index=0;
		bool expander[]{ (new(data+pagination*index++) types(std::move(*(types*)(other+index))),false)... };
	}
	indexed_struct& operator=(const indexed_struct& other)noexcept{//i.e. copy assignment operator
		if(this!=&other){//i.e. self-assignment protection
			size_t index=0;
			if(is_constructed)
 	 			bool expander[]{ (*(types*)(data+pagination*index)=*(types*)(other+index),++index,false)... };
 	 		else{
 	 			bool expander[]{ (new(data+pagination*index++) types(*(types*)(other+index)),false)... };
 	 			is_constructed=true;
			}
		}
		return *this;
 	}
	indexed_struct& operator=(indexed_struct&& other)noexcept{//i.e. move assignment operator
		if(this!=&other){
			size_t index=0;
			if(is_constructed)
 	 			bool expander[]{ (*(types*)(data+pagination*index)=std::move(*(types*)(other+index)),++index,false)... };
 	 		else{
 	 			bool expander[]{ (new(data+pagination*index++) types(std::move(*(types*)(other+index))),false)... };
 	 			is_constructed=true;
 	 		}
		}
		return *this;
 	}
	
	void* operator+(__int64 index)const{ return (void*)(data+pagination*index); }//i.e. accessor, returns address
	/*Acccess-Format: *(respective_type*)(indexed_struct_object_name + index)
	  Note: In order to access elements, u have to typecast explicitly. Also,
			this is the only accessor we can have since, we can't efficiently 
			& directly typecast return types using template parameter-pack
	*/
	
	friend std::ostream& operator<<(std::ostream& out,const indexed_struct& self){//i.e. overloaded cout method
		size_t index=0;
		bool expander[]{ (out<<*(types*)(self.data+pagination*index++)<<' ',false)... };
		return out;
	}
	friend std::istream& operator>>(std::istream& in,indexed_struct& self){//i.e. overloaded cin method
		size_t index=0;
		bool expander[]{ (in.sync(),in>>*(types*)(self.data+pagination*index++),false)... };
		return in;
	}
	
	~indexed_struct(){//i.e. dtor
		size_t index=0;
		if(is_constructed)
			bool expander[]{ (((types*)(data+pagination*index++))->~types(),false)... };
	}//Note: we have to perform explicit dtor call for every constructed/mapped object on data-buffer
private:
	static constexpr size_t pagination=max_of<0,sizeof(types)...>();
	unsigned char data[pagination*sizeof...(types)];//i.e. data-buffer on stack
	bool is_constructed;//i.e. for exception safety in assignment operators
};
#endif

#endif
