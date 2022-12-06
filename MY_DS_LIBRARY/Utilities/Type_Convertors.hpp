//NOTE: this header must be included before required type-container headers in order to use thier respective convertor methods

#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef TYPE_CONVERTORS_GUARD
#define TYPE_CONVERTORS_GUARD 1

#include <iostream>

//forward declarations:
template<typename, size_t> class HF_Stack;
template<typename> class Vector;

class convert{//non instantiating class (i.e. acts as interface)
	
	convert();//disabled default ctor
public:
	
	template<typename T, size_t C>
	static Vector<T> to_Vector(HF_Stack<T, C>&& s){
		Vector<T> v(s.data, s.current, C);
		s.data=nullptr; s.current=0;
		return v;
	}
	
	template<size_t C, typename T>
	static HF_Stack<T, C> to_HF_Stack(Vector<T>&& v){
		if(v.capacity()!=C) throw false;//exception safety
		HF_Stack<T, C> s(v.data, v._size);
		v.data=nullptr; v._size=v._capacity=0;
		return s;
	}

};

#endif

#endif
