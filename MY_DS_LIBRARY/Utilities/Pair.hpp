#ifndef PAIR_GUARD
#define PAIR_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define noexcept
#endif

template<typename T1, typename T2>
struct Pair{//custom minimal implementation of std::pair
	T1 first;
	T2 second;
	
	Pair()noexcept://default ctor
		first(), second(){}
		//Note: for objs, it invokes default ctor & for primitives, it sets default values
	
#if __cplusplus >= 201103L
	template<typename _T1, typename _T2>//_T1&& , _T2&& both are universal references
	Pair(_T1&& first, _T2&& second)noexcept://parametized ctor
		first(std::forward<_T1>(first)), second(std::forward<_T2>(second)){}
#else
	Pair(const T1& first, const T2& second):
		first(first), second(second){}
#endif
	
	friend std::ostream& operator<<(std::ostream& out, const Pair& self){//overloaded cout method
		out<<self.first<<' '<<self.second;
		return out;
	}
	friend std::istream& operator>>(std::istream& in, Pair& self){//overloaded cin method
		in>>self.first>>self.second;
		return in;
	}
};

#if __cplusplus >= 201103L
template<typename T1, typename T2>
auto Make_Pair(T1&& first, T2&& second)->Pair<T1, T2>{//construct Pair without providing their types
	return Pair<T1, T2>(std::forward<T1>(first), std::forward<T2>(second));
}//Note: doesn't deduce complex dependant (template) types
#endif

#endif
