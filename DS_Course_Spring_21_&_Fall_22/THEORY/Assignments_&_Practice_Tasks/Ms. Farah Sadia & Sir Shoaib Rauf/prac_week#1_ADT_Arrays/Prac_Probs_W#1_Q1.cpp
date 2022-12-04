#include<iostream>

int find_local_minimum(int* arr, int size){
	if (size<2) return -1;//expects atleast 2 elements
	if(arr[0]<=arr[1]) return 0;//left boundary/corner element should be less than or equals to right-most neighbor
	for(int i=0;i<size-1;++i)//middle elements
		if(arr[i]<=arr[i-1]&&arr[i]<=arr[i+1])//should be less than or equals to both neighbor elements
			return i;
	if(arr[size-1]<=arr[size-2]) return size-1;//right boundary/corner element should be less than or equals to left-most neighbor
	return -1;//no such element found
}

int main(){
	/* test_case_1: */
//	int arr[]={1, 2, 3};
	
	/* test_case_2: */
//	int arr[]={3, 2, 1};
		
	/* test_case_3: */
	int arr[]={23, 8, 15, 2, 3};
	
	std::cout<<"Index of local minima is: "
			 <<find_local_minimum(arr, sizeof(arr)/4);
	
	return 0;
}
