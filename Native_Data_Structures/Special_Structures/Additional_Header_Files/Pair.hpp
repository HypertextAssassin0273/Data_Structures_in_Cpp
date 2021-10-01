#ifndef PAIR_GUARD
#define PAIR_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T1,typename T2>
struct Pair{//i.e. custom minimal implementation of std::pair
	T1 first;
	T2 second;
	
	Pair()noexcept://i.e. default ctor
		first(),second(){}
#if __cplusplus >= 201103L
	template<typename _T1,typename _T2>//i.e. _T1&& , _T2&& both are universal references
	Pair(_T1&& first,_T2&& second)noexcept://i.e. fill ctor
		first(std::forward<_T1>(first)),second(std::forward<_T2>(second)){}
#endif
		
	friend std::ostream& operator<<(std::ostream& out,const Pair& self){//i.e. overloaded cout method
		out<<self.first<<' '<<self.second;
		return out;
	}
	friend std::istream& operator>>(std::istream& in,Pair& self){//i.e. overloaded cin method
		in>>self.first>>self.second;
		return in;
	}
};

#if __cplusplus >= 201103L
template<typename T1,typename T2>
auto Make_Pair(T1&& first,T2&& second)->Pair<T1,T2>{//i.e. construct Pair without providing their types
	return Pair<T1,T2>(std::forward<T1>(first),std::forward<T2>(second));
}//Note: doesn't deduce complex dependant (template) types
#endif

#endif
