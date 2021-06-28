#include<iostream>
using namespace std;

//Note: include "Array.hpp" after including iostream & using namespace std
#include"Array.hpp"

template<typename T,unsigned int __size>
void Array<T,__size>::sort(bool direction_flag){//i.e. insertion-sort
    for (__int64 j,i=1;i<_size;++i){
      	T key=data[i];
       	if(direction_flag)
			for (j=i-1;j>=0&&data[j]>key;--j)
            	data[j+1]=data[j];
        else
            for (j=i-1;j>=0&&data[j]<key;--j)
            	data[j+1]=data[j];
       	data[j+1]=key;
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
	arr.sort();//i.e. using insertion-sort in ascending order
	cout<<arr;
	return 0;
}

