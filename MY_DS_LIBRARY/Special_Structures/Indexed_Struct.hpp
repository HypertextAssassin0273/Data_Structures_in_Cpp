/* Indexed Structure or Array of Distinct Data-types (Special Contiguous Container) */
/* Optimal-Usage:
	*) you can use this structure in-place of normal struct to store highly un-alligned
	   attributes with much lesser space.
	   [e.g. struct{int;string;char;} =>24 bytes, indexed_struct<int,string,char> =>14 bytes]
   Highlights:
	1) Theoretically, object array is mapped as struct (with the help of placement-new operator), 
	   in order to access its attributes at runtime with O(1) time-complexity.
	2) Automatic compile-time deduction of pagination-gaps/offsets for keeping
	   elements perfectly alligned in mapped-array (data-buffer).
   Additional-Notes:
	1) Available only in C++11 & higher versions.
	2) Explicit typecast required for accessing elements efficiently in some cases.
*/
#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef INDEXED_STRUCT_GUARD
#define INDEXED_STRUCT 1

#include <iostream>
#include <fstream>
#include "../Utilities/Template_Meta_Programming.hpp"

template<typename... types>
struct indexed_struct{
	typedef indexed_struct __IS;
	
	/* default constructor: */
	indexed_struct()noexcept{
		offset_type index=0;
		bool expander[]{ ( new(data+offsets[index++]) types(), false )... };//constructs default objects/values
	}
	
	/* copy semantics (performs deep copy for mapped objects): */
	indexed_struct(const __IS& other)noexcept{//copy ctor
		offset_type index=0;
		bool expander[]{
			( new(data+offsets[index]) types(*(types*)(other.data+offsets[index])),
			  index++, false )...
		};
	}
	__IS& operator=(const __IS& other)noexcept{//copy assignment operator
		if(this==&other) return *this;//self-assignment protection
		offset_type index=0;
		bool expander[]{
			( *(types*)(data+offsets[index])=*(types*)(other.data+offsets[index]),
			  index++, false )...
		};
		return *this;
 	}
 	
 	/* move semantics (performs shallow copy for mapped objects): */
 	indexed_struct(__IS&& other)noexcept{//move ctor
		offset_type index=0;
		bool expander[]{
			( new(data+offsets[index]) types(std::move(*(types*)(other.data+offsets[index]))),
			  index++, false )...
		};
	}
	__IS& operator=(__IS&& other)noexcept{//move assignment operator
		if(this==&other) return *this;
		offset_type index=0;
		bool expander[]{
			( *(types*)(data+offsets[index])=std::move(*(types*)(other.data+offsets[index])),
			  index++, false )...
		};
		return *this;
 	}
 	
 	/* optimized initializer-list constructor: */
	template<typename... Ts>//variadic place-holder for instantiating universal references of respective 'types'
	indexed_struct(Ts&&... attributes)noexcept{
		offset_type index=0;
			bool expander[]{ ( new(data+offsets[index++]) types(std::forward<Ts>(attributes)), false )... };
	}/*Notes:
		1) here, 'Types&&...' are universal references & are used for 'perfect forwarding'.
	   	2) This technique is useful in place of std::initializer_list, since:
		  - it allows us to store multiple elements of different data-types.
		  - it's efficient for storing both copy & move constructibles simultaneously.
	 */
	
	/* accessors (getters/setters): */	
	template<size_t index, typename T=TMP::nth_type<index, types...>>
	T& get(){ return *(T*)(data+offsets[index]); }//compile time specific single attribute accessor
	
	template<size_t N, typename... Ts>//updates specific attributes efficiently (in any order)
	void set(const int (&indexes)[N], Ts&&... attributes){//performs deep/shallow copy respectively for all
		if(N!=sizeof...(attributes)||N>sizeof...(types)) return;
		offset_type i=0;
		bool expander[]{
			( *(std::remove_reference_t<Ts>*)(data+offsets[indexes[i++]])=std::forward<Ts>(attributes),
			  false )...
		};
	}//Warning: no exception safety is provided for wrong attribute index identification
	
	void* operator+(__int64 index)const{ return (void*)(data+offsets[index]); }//returns address
	/*Acccess-Format: *(respective_type*)(indexed_struct_object_name + index)
	  Notes:
		1) in order to access elements, you have to typecast them explicitly.
		2) this is the only efficient generic attribute accessor we can have since, we can't
		   directly typecast return types using template parameter-pack without recursion.
	*/
	
	/* overloaded 'cout & cin' methods: */
	friend std::ostream& operator<<(std::ostream& out, const __IS& self){//cout operator
		offset_type index=0;
		bool expander[]{ ( out<<*(types*)(self.data+offsets[index++])<<' ', false )... };
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __IS& self){//cin operator
		offset_type index=0;
		bool expander[]{ ( in.sync(), in>>*(types*)(self.data+offsets[index++]), false )... };
		return in;
	}
	
	/* overloaded 'fout & fin' methods (for .csv files): */
	friend std::ofstream& operator<<(std::ofstream& out, const __IS& self){//fout operator
		offset_type index=0;
		bool expander[]{ ( out<<*(types*)(self.data+offsets[index++])<<',', false )... };
		out.seekp(out.tellp()-static_cast<std::streampos>(1));
		out.put('\n');
		return out;
	}
	friend std::ifstream& operator>>(std::ifstream& in, __IS& self){//fin operator
		offset_type index=0;
		bool expander[]{ ( in>>*(types*)(self.data+offsets[index++]), in.get(), false )... };
		return in;
	}
	
	/* destructor: */
	~indexed_struct(){
		offset_type index=0;
		bool expander[]{ ( ((types*)(data+offsets[index++]))->~types(), false )... };
		//Note: we have to perform explicit dtor call for every constructed/mapped object on data-buffer
	}
	
private:
	/* non-member attributes: */
	static constexpr size_t capacity=TMP::total_of<sizeof(types)...>();//total size of all types
	
	typedef TMP::nth_type<(capacity<=255?0:capacity<=65535?1:capacity<=4294967295?2:3),
						   unsigned char, unsigned short, unsigned int, size_t> offset_type;
	//Note: this technique allows us to have exact type for offsets, so we can store them with less memory cost.
	
	static const offset_type offsets[];//static array of size same as 'total no. of attributes'
	static offset_type offset_adder;//need run-time variable to add offsets
	
	/* member attribute: */
	unsigned char data[capacity];//data-buffer on stack
};

/* static variable initialization: */
template<typename... types>
typename indexed_struct<types...>::offset_type
indexed_struct<types...>::offset_adder=0;
//Note: it has to be declared it inside the class as static. otherwise, it won't reset for different types.

/* static array initialization: */
template<typename... types>
const typename indexed_struct<types...>::offset_type
indexed_struct<types...>::offsets[]{ offset_type((offset_adder+=sizeof(types))-sizeof(types))... };

#endif

#endif
