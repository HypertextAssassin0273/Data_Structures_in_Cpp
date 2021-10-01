#if __cplusplus >= 201103L

#ifndef MAKE_VECTOR_GUARD
#define MAKE_VECTOR_GUARD 1

#include"Vector.hpp"

namespace __TMP{//i.e. Template Meta-Programming
	template<typename T,typename...>
	struct type_helper{
		using type=T;
	};
	
	template<typename... Types>
	struct type_helper<void,Types...>{
		using type=typename std::common_type<Types...>::type;
	};//i.e. specialized template struct for automatic type deduction
	
	template<typename T,typename... Types>
	using type_helper_t=typename type_helper<T,Types...>::type;
}

template<typename T=void,typename... Types,
         typename V=__TMP::type_helper_t<T,Types...>>
Vector<V> make_vector(Types&&... args){
	Vector<V> vec;
	vec.reserve(sizeof...(Types));
	bool expander[]{ (vec.emplace_back(std::forward<Types>(args)),false)... };
    return vec;
}
#endif

#endif
