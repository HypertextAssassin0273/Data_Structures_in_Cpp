#include<iostream>
using namespace std;

//Note: include "Vector.hpp" after including iostream & using namespace std
#include"Vector.hpp"

template<typename T>
void Vector<T>::sort(bool direction_flag){//i.e. improved bubble_sort
	bool swapped=true;
	for (__uint64 i=0;swapped&&(i<_size-1);++i){
		swapped=false;
	    for (__uint64 j=0;j<_size-i-1;++j){
  	    	if(direction_flag){
				if(*(T*)(data+sizeof(T)*j)>*(T*)(data+sizeof(T)*(j+1))){//i.e. ascending (by default)
        		    swap(*(T*)(data+sizeof(T)*j),*(T*)(data+sizeof(T)*(j+1)));
					swapped=true;
				}
			}
        	else if(*(T*)(data+sizeof(T)*j)<*(T*)(data+sizeof(T)*(j+1))){//i.e. descending 
    	   		swap(*(T*)(data+sizeof(T)*j),*(T*)(data+sizeof(T)*(j+1)));
    	   		swapped=true;
    	   	}
		}
	}
}

int main(){
#if __cplusplus >= 201103L
	Vector<int> vec{3,-1,7,5,4};
#else
	Vector<int> vec;
	vec.push_back(3);
	vec.push_back(-1);
	vec.push_back(7);
	vec.push_back(5);
	vec.push_back(4);
#endif
	cout<<vec;
	vec.sort();//i.e. using improved bubble-sort in ascending order
	cout<<vec;
	return 0;
}
