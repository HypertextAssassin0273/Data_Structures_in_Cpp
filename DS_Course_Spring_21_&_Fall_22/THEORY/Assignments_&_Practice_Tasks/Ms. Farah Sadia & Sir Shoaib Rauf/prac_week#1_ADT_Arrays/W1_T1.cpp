#include<iostream>
using namespace std;

// assuming un-sorted array

void MinMax(int* arr,int N, int* min,int* max){
	*min=*max=arr[0];
	for(int i=1,j; i<N; ++i){
		if(arr[i]<*min)
			*min=arr[i];
		if(arr[i]>*max)
			*max=arr[i];
	}
}

int main(){
	int arr[]={11,15,156,44,9,17,8,76,17},
		N=sizeof(arr)/sizeof(arr[0]),
		min=-1, max=-1;
	
	MinMax(arr, N, &min, &max);
	
	cout<<"min: "<<min
		<<", max: "<<max;
	
	return 0;
}
