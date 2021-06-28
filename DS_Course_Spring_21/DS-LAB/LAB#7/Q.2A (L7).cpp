#include<iostream>
using namespace std;

//Note: include "Array.hpp" after including iostream & using namespace std
#include"Array.hpp"

template<typename T,unsigned int __size>
void Array<T,__size>::sort(bool direction_flag){//i.e. selection sort
	for (__uint32 i=0;i<_size-1;++i){
        __uint32 min_index=i;
        for (__uint32 j=i+1;j<_size;++j){
            if(direction_flag){//i.e. ascending (by default)
				if(data[j]<data[min_index])
        	       	min_index=j;
			}
			else{//i.e. descending
				if(data[j]>data[min_index])
        	        min_index=j;
			}
        }
        swap(data[i],data[min_index]);
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
	arr.sort(0);//i.e. using selection-sort in descending order
	cout<<arr;
	return 0;
}

