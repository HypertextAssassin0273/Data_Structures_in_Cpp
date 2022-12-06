#ifndef REVERSE_ITERATOR_ADAPTER_GUARD
#define REVERSE_ITERATOR_ADAPTER_GUARD 1

/* Adapter for using const/non_const reverse_iterators inside 'range-based' loop: */

template<typename CT,//container_type
		 typename RIT>//reverse_iterator_type
struct reverse_iterator_adapter{
	reverse_iterator_adapter(CT& reference):
		ref(reference){}
	
	RIT begin(){ return ref.rbegin(); }
	RIT end(){ return ref.rend(); }
	
private:
	CT& ref;
};

#endif
