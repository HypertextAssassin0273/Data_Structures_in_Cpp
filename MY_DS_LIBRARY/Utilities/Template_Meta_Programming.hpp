/* Simple Work-arounds for Compile-Time Operations */
/* Side-Notes:
	1) constexpr is used to make function usable at compile-time.
	2) tenary operator can be used to make decision at compile-time.
*/
#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef TEMPLATE_META_PROGRAMMING_GUARD
#define TEMPLATE_META_PROGRAMMING_GUARD 1

#ifndef size_t
typedef unsigned long long size_t;//range: 0 to 18,446,744,073,709,551,615 (upto 20 digits)
#endif

namespace TMP{//Template Meta-Programming

//Deduce Nth type from Template Parameter-Pack:
template<size_t, typename...>
struct nth_type;//forward declaration of primary template struct

template<typename T0, typename... Ts>//T0: 1st type, Ts: (remaining all) types
struct nth_type<0, T0, Ts...>{//partially specialized template struct (base-case for terminating condition)
    typedef T0 type;
};
template<size_t N, typename T0, typename... Ts>//N: (remaining) number count
struct nth_type<N, T0, Ts...>{//main template struct
    typedef typename nth_type<N-1, Ts...>::type type;//template recursion in struct
};


//Get Total Size of All Template Parameter-Pack Values:
template<size_t V=0>//V: (last) value
constexpr size_t total_of(){ return V; }//overloaded template function (base-case for terminating condition)

template<size_t V1, size_t V2, size_t... Vs>//V1: 1st value, V2: 2nd value, Vs: (remaining all) values
constexpr size_t total_of(){//main template function
	return V1+total_of<V2, Vs...>();//template recursion in function
}


//Get Max. Value from Template Parameter-Pack:
constexpr size_t max(size_t a, size_t b){ return a>b?a:b; }

template<size_t V=0>
constexpr size_t max_of(){ return V; }

template<size_t V1, size_t V2, size_t... Vs>
constexpr size_t max_of(){ return max(V1, max_of<V2, Vs...>()); }


//Get Min. Value from Template Parameter-Pack:
constexpr size_t min(size_t a, size_t b){ return a<b?a:b; }

template<size_t V=0>
constexpr size_t min_of(){ return V; }

template<size_t V1, size_t V2, size_t... Vs>
constexpr size_t min_of(){ return min(V1, min_of<V2, Vs...>()); }

}

#endif

#endif
