#if __cplusplus >= 201103L

#ifndef COMPARATOR_ADAPTER_GUARD
#define COMPARATOR_ADAPTER_GUARD 1

#include "Comparator.hpp"

template<typename T>
using comparator_t=bool(*)(const T&, const T&);//storing function pointer type
template<typename T>
using comparator_t2=bool(*)(const T&, const T&, const T&);

template<typename, template<typename> class>
struct comparator_adapter;//forward declaration (for template specialization)

template<typename T>
struct comparator_adapter<T, comparator_t>{//partially specialized struct
	
	comparator_adapter(const T& key, comparator_t<T> comp)noexcept://parameterized ctor
		comparator(comp), source_key(key){}
	
	bool operator()(const T& target_key)const{//function call operator
		return comparator(target_key, source_key);
	}
	
private:
	comparator_t<T> comparator;
	const T& source_key;
};

template<typename T>
struct comparator_adapter<T, comparator_t2>{
	
	comparator_adapter(const T& key, const T& key2, comparator_t2<T> comp)noexcept:
		comparator(comp), source_key(key), source_key2(key2){}
	
	bool operator()(const T& target_key)const{
		return comparator(target_key, source_key, source_key2);
	}
	
private:
	const T& source_key, source_key2;
	comparator_t2<T> comparator;
};

template<typename T>
auto Make_CA(const T& key, comparator_t<T> comp=equal)//makes comparator_adapter object
	->comparator_adapter<T, comparator_t>{
	return comparator_adapter<T, comparator_t>(key, comp);
}
template<typename T>
auto Make_CA(const T& key, const T& key2, comparator_t2<T> comp=equal)//overload for range based comparators
	->comparator_adapter<T, comparator_t2>{
	return comparator_adapter<T, comparator_t2>(key, key2, comp);
}

#endif

#endif
