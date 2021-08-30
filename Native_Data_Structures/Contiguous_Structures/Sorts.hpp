#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
#endif

#if __cplusplus >= 201103L
template<typename T>//i.e. T->type
void Swap(T &xp,T &yp){
    T temp=std::move(xp);
    xp=std::move(yp);
    yp=std::move(temp);
	//i.e. here, move ctor gets invoked for pointed obj
}
#else
template<typename T>
void Swap(T &xp,T &yp){
    T temp=xp;
    xp=yp;
    yp=temp;
}
#endif

template<class Iterator>
Iterator Min_element(Iterator first,const Iterator& last){
	if (first==last)
		return last;
  	Iterator smallest=first;
  	while (++first!=last)
    	if (*first<*smallest)
      		smallest=first;
  	return smallest;
}

namespace Sort{
	template<class Iterator>
	void Bubble(const Iterator& begin,const Iterator& end){
	    for (Iterator i=begin;i!=end;++i)
	        for (Iterator j=begin;j<i;++j)
	            if (*i<*j)
	                Swap(*i,*j);
	}
	
	template<class Iterator>
	void Insertion(Iterator begin,const Iterator& end){
	    Swap(*begin,*Min_element(begin,end));//i.e. here, 'begin' acts as 'min' value
	    for (Iterator b=begin;++b<end;begin=b)
	        for (Iterator c=b;*c<*begin;--c,--begin)
	            Swap(*begin,*c);
	}
	
	template<class Iterator>
	void Selection(const Iterator& begin,const Iterator& end){
	    for (Iterator i=begin;i!=end;++i)
	        Swap(*i,*Min_element(i,end));//i.e. here, 'i' acts as 'min' value
	}
	
	template<class Iterator>
	void Quick(const Iterator& begin,const Iterator& end){
		if (end<=begin)
			return;
	    Iterator middle=begin+1;
	    for (Iterator i=begin+1;i<end;++i)
	        if (*i<*begin){//i.e. here, 'begin' acts as 'pivot'
    	        Swap(*i,*middle);
    	        ++middle;
    	    }
    	Swap(*begin,*(middle-1));
    	Quick(begin,middle-1);
	    Quick(middle,end);
	}
}
