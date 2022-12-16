#include "Sorts.hpp"

int main(){
	std::string arr[]={"good","lol","taebak","fun","great", "k4"};//stack/local 1d array
	const int N=sizeof(arr)/sizeof(arr[0]);//array size
	
	sort::bubble(arr, N);//ascending order
//	sort::bubble(arr, arr+N);//iterator version
	
//	sort::bubble(arr, N, lesser);//descending order
//	sort::bubble(arr, arr+N, lesser);
	
	for(size_t i=0;i<N;++i)
		std::cout<<arr[i]<<", ";
	
	return 0;
}
