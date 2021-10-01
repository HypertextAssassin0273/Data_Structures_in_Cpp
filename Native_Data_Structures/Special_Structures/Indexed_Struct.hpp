/* Indexed Structure or Array of Distinct Data-types (Special Contiguous Container) */
/* Highlights:
	1) Theoretically, struct is mapped as array (with the help of placement-new operator), 
	   in order to access its attributes at runtime with O(1) time-complexity	
	2) Automatic compile-time deduction of pagination-gap or offsets for keeping
	   elements perfectly alligned in mapped-array (data-buffer)
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

#include<iostream>
#include<fstream>

/*************** Simple Work-arounds for Compile-Time Operations (Template Meta-Programming) ****************/

/* Deduce Nth-type from Template Parameter-Pack */
template<size_t N,typename... T>
struct Nth_type;//i.e. forward declaration of primary template struct

template<typename T0,typename... T>
struct Nth_type<0,T0,T...>{//i.e. partially specialized struct template (base-case for terminating condition)
    typedef T0 type;
};
template<size_t N,typename T0,typename... T>
struct Nth_type<N,T0,T...>{//i.e. partially specialized struct template
    typedef typename Nth_type<N-1,T...>::type type;//i.e. template recursion
};

template<size_t N,typename... T>
using nth_type=typename Nth_type<N,T...>::type;//i.e. simplifying previous formatted name

/* Get Max. Value from Template Parameter-Pack */
constexpr size_t _max(size_t a,size_t b){ return a>b?a:b; }
/*Notes:
	- constexpr is used to make function usable at compile-time
	- tenary operator can be used to make decision at compile-time 
*/
template<bool>
constexpr size_t max_of(){ return 0; }//i.e. overloaded base-case func for terminating condition

template<bool b,size_t value,size_t... values>
constexpr size_t max_of(){ return _max(value,max_of<b,values...>()); }//i.e. template function recursion

/* Get Total of All Template Parameter-Pack Values */
template<bool>
constexpr size_t total_of(){ return 0; }

template<bool b,size_t value,size_t... values>
constexpr size_t total_of(){ return value+total_of<b,values...>(); }

/************************************************************************************************************/


template<bool,typename... types>
struct indexed_struct;//i.e. forward declaration (for template-specialization)


/************* NOTE: This Version gives Lesser Performance but provides Optimized Memory Results ************/
/*Optimal-Usage: when one or few data-types have very large type-size while rest have smaller
  Additional Perk: you can use this structure in-place of normal struct to store highly un-alligned
				   attributes with much lesser space
  Example: struct{ int; string; char; } => 24 bytes, indexed_struct<1,int,string,char> => 14 bytes 			*/
template<typename... types>
struct indexed_struct<true,types...>{
	indexed_struct()noexcept{//i.e. default ctor
		size_t index=0;
		bool expander[]{ ( new(data+offsets[index++]) types(),false )... };//i.e. default constructing objs
	}
	indexed_struct(types... attributes)noexcept{//i.e. optimized initializer-list ctor
		size_t index=0;
		bool expander[]{ ( new(data+offsets[index++]) types(std::move(attributes)),false )... };
	}/*Note:
		 Attributes are constructed on data-buffer using Lamba (array) expander with template parameter-pack 
		 because there is no more efficient way (that I know) to access types one-by-one from parameter-pack.
	   Side-Note:
	   	 This technique can be used in-place of std::initializer_list since, it has some pros, like:
		  - it can store multiple elements of different data-types
		  - it doesn't cost us extra copy of elements (if we need to further move them)
		  - it can be efficiently used for moving both copy & move constructibles simultaneously
	 */
	indexed_struct(const indexed_struct& other)noexcept{//i.e. copy ctor
		size_t index=0;
		bool expander[]{
			( new(data+offsets[index]) types(*(types*)(other.data+offsets[index])),
			  index++,false )...
		};
	}
	indexed_struct(indexed_struct&& other)noexcept{//i.e. move ctor
		size_t index=0;
		bool expander[]{
			( new(data+offsets[index]) types(std::move(*(types*)(other.data+offsets[index]))),
			  index++,false )...
		};
	}
	indexed_struct& operator=(const indexed_struct& other)noexcept{//i.e. copy assignment operator
		if(this!=&other){//i.e. self-assignment protection
			size_t index=0;
			bool expander[]{
				( *(types*)(data+offsets[index])=*(types*)(other.data+offsets[index]),
				  index++,false )...
			};
		}
		return *this;
 	}
	indexed_struct& operator=(indexed_struct&& other)noexcept{//i.e. move assignment operator
		if(this!=&other){
			size_t index=0;
			bool expander[]{
				( *(types*)(data+offsets[index])=std::move(*(types*)(other.data+offsets[index])),
				  index++,false )...
			};
		}
		return *this;
 	}
	
	void* operator+(__int64 index)const{ return (void*)(data+offsets[index]); }//i.e. accessor, returns address
	/*Acccess-Format: *(respective_type*)(indexed_struct_object_name + index)
	  Note: 
	  	In order to access elements, u have to typecast explicitly. Also, this is the only accessor we can
		have since, we can't efficiently & directly typecast return types using template parameter-pack
	*/
	
	friend std::ostream& operator<<(std::ostream& out,const indexed_struct& self){//i.e. overloaded cout method
		size_t index=0;
		bool expander[]{ (out<<*(types*)(self.data+offsets[index++])<<' ',false)... };
		return out;
	}
	friend std::istream& operator>>(std::istream& in,indexed_struct& self){//i.e. overloaded cin method
		size_t index=0;
		bool expander[]{ (in.sync(),in>>*(types*)(self.data+offsets[index++]),false)... };
		return in;
	}
	
	friend std::ofstream& operator<<(std::ofstream& out,const indexed_struct& self){//i.e. overloaded fout method
		size_t index=0;
		bool expander[]{ (out<<*(types*)(self.data+offsets[index++])<<',',false)... };
		out.seekp(out.tellp()-static_cast<std::streampos>(1));
		out.put('\n');
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in,indexed_struct& self){//i.e. overloaded fin method
		size_t index=0;
		bool expander[]{ ( in>>*(types*)(self.data+offsets[index++]),in.get(),false)... };
		return in;
	}
	
	~indexed_struct(){//i.e. dtor
		size_t index=0;
		bool expander[]{ (((types*)(data+offsets[index++]))->~types(),false)... };
		//Note: we have to perform explicit dtor call for every constructed/mapped object on data-buffer
	}
	
private:
	static constexpr size_t capacity=total_of<0,sizeof(types)...>();//Note: capacity == total size of all types
	typedef nth_type<(capacity<=255?0:(capacity<=65535?1:(capacity<=4294967295?2:3))),
					 unsigned char,unsigned short,unsigned int,size_t> offset_type;
	//Note: this technique allows us to have exact type for offsets, so we can store them with less memory cost
	static const offset_type offsets[];
	static offset_type offset_adder;//i.e. need run-time variable to add offsets
	
	unsigned char data[capacity];//i.e. data-buffer on stack
};

//i.e. static member variable initialization
template<typename... types>
typename indexed_struct<true,types...>::offset_type
indexed_struct<true,types...>::offset_adder=0;
//Note: We had to declare it inside the class as static. Otherwise, it won't reset for different types

//i.e. static member array initialization
template<typename... types>
const typename indexed_struct<true,types...>::offset_type
indexed_struct<true,types...>::offsets[]{ offset_type((offset_adder+=sizeof(types))-sizeof(types))... };


/******************* NOTE: This Version gives Optimized Performance but takes More Memory *******************/
/*Why Optimized-Performance?: this techique doesn't involves any 'additional dereferencing' for offsets
							  to access elements, which we have seen in above version
  Optimal-Usage: when all types have average size or have size closer to each other 
  Example: sizes can be like <1,4,2,4,2> but not like <2,4,32,8,2> (i.e. 32 is too high w.r.t others)		*/
template<typename... types>
struct indexed_struct<false,types...>{
	indexed_struct()noexcept{//i.e. default ctor
		size_t index=0;
		bool expander[]{ (new(data+pagination*index++) types(),false)... };
	}
	indexed_struct(types... attributes)noexcept{//i.e. optimized initializer-list ctor
		size_t index=0;
		bool expander[]{ (new(data+pagination*index++) types(std::move(attributes)),false)... };
	}
	indexed_struct(const indexed_struct& other)noexcept{//i.e. copy ctor
		size_t index=0;
		bool expander[]{ 
			( new(data+pagination*index) types(*(types*)(other.data+pagination*index)),
			  index++,false )... 
		};
	}
	indexed_struct(indexed_struct&& other)noexcept{//i.e. move ctor
		size_t index=0;
		bool expander[]{
			( new(data+pagination*index) types(std::move(*(types*)(other.data+pagination*index))),
			  index++,false )...
		};
	}
	indexed_struct& operator=(const indexed_struct& other)noexcept{//i.e. copy assignment operator
		if(this!=&other){
			size_t index=0;
			bool expander[]{ 
				( *(types*)(data+pagination*index)=*(types*)(other.data+pagination*index),
				  index++,false )...
			};
		}
		return *this;
	}
	indexed_struct& operator=(indexed_struct&& other)noexcept{//i.e. move assignment operator
		if(this!=&other){
			size_t index=0;
			bool expander[]{
				( *(types*)(data+pagination*index)=std::move(*(types*)(other.data+pagination*index)),
				  index++,false )...
			};
		}
		return *this;
 	}
	
	void* operator+(__int64 index)const{ return (void*)(data+pagination*index); }//i.e. accessor
	
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
	
	friend std::ofstream& operator<<(std::ofstream& out,const indexed_struct& self){//i.e. overloaded fout method
		size_t index=0;
		bool expander[]{ (out<<*(types*)(self.data+pagination*index++)<<',',false)... };
		out.seekp(out.tellp()-static_cast<std::streampos>(1));
		out.put('\n');
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in,indexed_struct& self){//i.e. overloaded fin method
		size_t index=0;
		bool expander[]{ ( in>>*(types*)(self.data+pagination*index++),in.get(),false)... };
		return in;
	}
	
	~indexed_struct(){//i.e. dtor
		size_t index=0;
		bool expander[]{ (((types*)(data+pagination*index++))->~types(),false)... };
	}
	
private:
	static constexpr size_t pagination=max_of<0,sizeof(types)...>();
	unsigned char data[pagination*sizeof...(types)];//i.e. data-buffer on stack
};

#endif

#endif
