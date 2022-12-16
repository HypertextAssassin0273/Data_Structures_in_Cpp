#ifndef SWAP_GUARD
#define SWAP_GUARD 1

#include <iostream>

/* Generalized & optimized swap (for move constructible heap objects): */

#if __cplusplus >= 201103L
template<typename T>
void swap(T& a, T& b){
	T temp=std::move(a);
    a=std::move(b);
    b=std::move(temp);
}
#else
template<typename T>
void swap(T& a, T& b){
	T temp=a;
    a=b;
    b=temp;
}
#endif

#endif
