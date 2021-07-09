#include<iostream>
using namespace std;

//Note: include "Array.hpp" after including iostream & using namespace std
#include"Array.hpp"

template<typename T,unsigned int __size>
void Array<T,__size>::sort(bool direction_flag){//i.e. improved bubble-sort
	bool swapped=true;
	for (__uint32 i=0;swapped&&(i<_size-1);++i){
		swapped=false;
	    for (__uint32 j=0;j<_size-i-1;++j){
  	    	if(direction_flag){
				if(data[j]>data[j+1]){//i.e. ascending (by default)
        		    swap(data[j],data[j+1]);
        		    swapped=true;
				}
			}
        	else if (data[j]<data[j+1]){//i.e. descending
    	    	swap(data[j],data[j+1]);
    	    	swapped=true;
    	    }
		}
	}
}

int main(){
#if __cplusplus >= 201103L
	Array<int,5> arr{3,-1,7,5,4};
#else
	Array<int,5> arr;
	cin>>arr;
#endif
	cout<<arr;
	arr.sort();//i.e. using improved bubble-sort in ascending order
	cout<<arr;
	return 0;
}

