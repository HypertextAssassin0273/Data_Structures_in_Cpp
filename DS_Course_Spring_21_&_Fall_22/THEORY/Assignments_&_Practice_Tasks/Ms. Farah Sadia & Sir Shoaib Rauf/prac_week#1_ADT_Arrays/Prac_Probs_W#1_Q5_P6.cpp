#include<iostream>

void shift_array_circularly(int* arr, int size, int K, bool flag=false){
	if(flag)
		while(K--)
		for(int i=0;i<size-1;++i)//shift to left K times
			std::swap(arr[i],arr[i+1]);
	else
		while(K--)
		for(int i=size-1;i;--i)//shift to right K times
			std::swap(arr[i],arr[i-1]);
}

int main(){
	int arr[]={1, 2, 3, 4, 5, 6}, K=1,
		N=sizeof(arr)/4;
	
	shift_array_circularly(arr,  N , K);//O(N^K) complexity
	
	for(int i=0;i<N;++i)
		std::cout<<arr[i]<<' ';
	
	return 0;
}
