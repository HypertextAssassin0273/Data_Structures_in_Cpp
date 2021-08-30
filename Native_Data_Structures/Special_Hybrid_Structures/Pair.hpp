#ifndef PAIR_GUARD
#define PAIR_GUARD 1

#if __cplusplus >= 201103L

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
#endif

template<typename T1,typename T2>
struct Pair{//i.e. custom minimal implementation of std::pair
	T1 first;
	T2 second;
	
	Pair()noexcept://i.e. default ctor
		first(),second(){}
	template<typename _T1,typename _T2>
	Pair(_T1&& first,_T2&& second)noexcept://i.e. fill ctor
		first(std::forward<_T1>(first)),second(std::forward<_T2>(second)){}
		
	friend std::ostream& operator<<(std::ostream& out,const Pair& self){//i.e. overloaded cout method
		out<<self.first<<' '<<self.second;
		return out;
	}
	friend std::istream& operator>>(std::istream& in,Pair& self){//i.e. overloaded cin method
		in>>self.first>>self.second;
		return in;
	}
};

template<typename T1,typename T2>
constexpr auto Make_Pair(T1&& first,T2&& second)->Pair<T1,T2>{//i.e. construct Pair without providing their types
	return Pair<T1,T2>(std::forward<T1>(first),std::forward<T2>(second));
}//Note: doesn't deduce complex dependant (template) types
#endif

#endif
