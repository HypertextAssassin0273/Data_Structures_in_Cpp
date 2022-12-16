#ifndef SORTS_GUARD
#define SORTS_GUARD 1

#include<iostream>

/* generalized & optimized (for heap objects) swap: */
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

/* comparators: */
template<typename T>
bool greater(const T& a, const T& b){ return a>b; }
template<typename T>
bool lesser(const T& a, const T& b){ return a<b; }

/* generalized sorts (for both ascending & descending orders): */
/* important-note:
	there is no need for passing additional comparator in standard iterator based versions
	when sorting in descending order, since we already have reverse_iterator class
	hence, we can replace 'begin' with 'rbegin' & 'end' with 'rend' methods.
*/
namespace sort{
	template<typename T>
	void bubble(T arr[], size_t size,//raw array based version
				bool (*comparator)(const T&, const T&)=greater){//default comparator: greater
		size_t j;//iterator
		bool of;//optimization_flag (for checking whether swaps were performed inside inner-loop)
		for(--size;size;--size){//loops 'acutal_size-1' times
			for(j=0,of=true;j!=size;++j)//loops one lesser time than previous iteration
				if(comparator(arr[j], arr[j+1])){//default order: ascending
					swap(arr[j], arr[j+1]);
					of=false;
				}
			if(of) return;
		}
	}
	template<typename T>
	void bubble(T* begin, T* end,//raw ptr based iterator based version
				bool (*comparator)(const T&, const T&)=greater){
		T *j;	//iterator
		bool of;//optimization_flag
	    for (--end;begin!=end;--end){
	        for (j=begin,of=true;j!=end;++j)
	            if (comparator(*j,j[1])){//note: j[1] is same as *(j+1), default order: ascending
	                swap(*j, j[1]);
	                of=false;
				}
			if(of) return;
		}
	}
	template<typename iter>
	void bubble(iter begin, iter end){//standard iterator based version
		iter j;	//iterator class object
		bool of;//optimization_flag
	    for (--end;begin!=end;--end){
	        for (j=begin,of=true;j!=end;++j)
	            if (*j>j[1]){//default order: ascending
	                swap(*j, j[1]);
	                of=false;
				}
			if(of) return;
		}
	}

	template<typename T>
	void selection(T arr[], size_t size, bool (*comparator)(const T&, const T&)=greater){
		size_t j,	   //iterator
			   sel_idx;//selected_index (i.e. minimum/maximum element index)
		for(--size;size;--size){//loops 'acutal_size-1' times
			sel_idx=size;
			for(j=0;j!=size;++j)//loops one lesser time than previous iteration
				if(comparator(arr[j], arr[sel_idx]))//default order: ascending
					sel_idx=j;
			if(sel_idx!=size)//ensures same indexes aren't swapped
				swap(arr[sel_idx], arr[size]);//swaps the selected element with last-most element
		}
	}
	template<typename T>
	void selection(T *begin, T *end, bool (*comparator)(const T&, const T&)=greater){
		T *j,	   //iterator
		  *sel_ptr;//selected_ptr (points minimum/maximum element)
		for(--end;begin!=end;--end){
			sel_ptr=end;
			for(j=begin;j!=end;++j)
				if(comparator(*j, *sel_ptr))//default order: ascending
					sel_ptr=j;
			if(sel_ptr!=end)
				swap(*sel_ptr, *end);
		}
	}
	template<typename iter>
	void selection(iter begin, iter end){
		iter j,	   	 //iterator class object
		  	 sel_iter;//selected_iterator (points minimum/maximum element)
		for(--end;begin!=end;--end){
			sel_iter=end;
			for(j=begin;j!=end;++j)
				if(*j>*sel_iter)//default order: ascending
					sel_iter=j;
			if(sel_iter!=end)
				swap(*sel_iter, *end);
		}
	}
	
	template<typename T>
	void insertion(T arr[], size_t size, bool (*comparator)(const T&, const T&)=greater){
		size_t i, j;//iterators
		T key;   	//temporarily holds minimum/maximum element
		for(i=size-1;i;--i){//loops 'acutal_size-1' times
			key=arr[i-1];
			//loops one greater time than previous iteration (w.r.t previously compared elements):
			for(j=i;j<size && comparator(key, arr[j]);++j)//default order: ascending
					arr[j-1]=arr[j];
			arr[j-1]=key;
		}
	}
	template<typename T>
	void insertion(T *begin, T *end, bool (*comparator)(const T&, const T&)=greater){
		T *i, *j,//iterators
		  key;   //temporarily holds minimum/maximum element
		for(i=end-1;begin!=i;--i){
			key=i[-1];//note: i[-1] is same as *(i-1)
			for(j=i;j!=end && comparator(key, *j);++j)//default order: ascending
					j[-1]=*j;
			j[-1]=key;
		}
	}
	template<typename T, typename iter>
	void insertion(iter begin, iter end){
		iter i, j;//iterator class objects
		T key; //temporarily holds minimum/maximum element
		for(i=end-1;begin!=i;--i){
			key=i[-1];
			for(j=i;j!=end && key>*j;++j)//default order: ascending
					j[-1]=*j;
			j[-1]=key;
		}
	/* note: in this version, 'T' needs to be mentioned explicitly (because of key)
	   format: sort::insertion<int>(parameters...); */
	}
	
	template<typename iter>
	void quick(iter begin, iter end){
		if (end<=begin) return;
	    iter middle=begin+1;
	    for (iter i=begin+1;i<end;++i)
	        if (*i<*begin)//here, 'begin' acts as 'pivot'
    	        swap(*i, *middle++);
		swap(*begin, middle[-1]);
    	quick(begin, middle-1);
	    quick(middle, end);
	}
	
	//note: quick, comb, shell... (remaining)
}

#endif
