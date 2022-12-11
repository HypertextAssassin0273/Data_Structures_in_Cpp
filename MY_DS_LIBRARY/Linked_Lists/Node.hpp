#ifndef NODE_GUARD
#define NODE_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
struct SLL_Node{//Singly Linked List Node
	T data;
    SLL_Node *next;
    
#if __cplusplus < 201103L
    SLL_Node(const T& data=T())noexcept://default & parameterized ctor
		data(data), next(nullptr){}
#else
    template<typename... _T>//variadic template
	SLL_Node(_T&&... data)noexcept://emplaced ctor
		data{std::forward<_T>(data)...},//perfect forwarding
		next(nullptr){}
#endif
};

template<typename T>
struct DLL_Node{//Doubly Linked List Node
	T data;
    DLL_Node *next, *prev;
	
#if __cplusplus < 201103L
    DLL_Node(const T& data=T())noexcept:
		data(data), next(nullptr), prev(nullptr){}
#else
    template<typename... _T>
	DLL_Node(_T&&... data)noexcept:
		data{std::forward<_T>(data)...},
		next(nullptr), prev(nullptr){}
#endif
};

#endif
