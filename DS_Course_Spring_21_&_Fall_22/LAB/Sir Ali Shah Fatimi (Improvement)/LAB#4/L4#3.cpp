#include "Sorts.hpp"

int main(){	 //0  1  2  3  4   5   6   7
	int arr[]={33,44,66,2,404,999,525,31};//local 1d array
	const int N=sizeof(arr)/sizeof(arr[0]);//array size
	
//	sort::insertion(arr, N);//ascending order
	sort::insertion(arr, arr+N);//iterator version
	
//	sort::insertion(arr, N, lesser);//descending order
//	sort::insertion(arr, arr+N, lesser);
	
	for(size_t i=0;i<N;++i)
		std::cout<<arr[i]<<' ';
	
	return 0;
}
