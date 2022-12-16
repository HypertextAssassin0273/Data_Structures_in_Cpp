#include <iostream>
#include <algorithm>

//Merges back the partitions of actual array
void merge(int arr[], int beg, int mid, int end, int max){
	int i=beg, j=mid+1, k=beg;
	while(i<=mid&&j<=end)
		arr[k++]+=(arr[(arr[i]%max<=arr[j]%max)?i++:j++]%max)*max;
	while(i<=mid)
		arr[k++]+=(arr[i++]%max)*max;
	while(j<=end)
		arr[k++]+=(arr[j++]%max)*max;
	i=beg;
	while(i<=end)//obtains actual values
		arr[i++]/=max;
}

//Recursive Merge Sort (with extra parameter for storing max. element)
void RMS(int arr[], int beg, int end, int max){
	if(beg<end){
		int mid=(beg+end)/2;
		RMS(arr, beg, mid, max);
		RMS(arr, mid+1, end, max);
		merge(arr, beg, mid, end, max);
	}
}

//Helper function: finds max element & then calls recursive merge sort.
template<int n>
void merge_sort(int (&&arr)[n]){
	RMS(arr, 0, n-1, *std::max_element(arr, arr+n)+1);
	
	std::cout<<"Sorted array \n";
	for (auto& it: arr)
		std::cout<<it<<' ';
}

int main(){
	/* test case 1: */
//	merge_sort({5, 4, 3, 2, 1});
	
	/* test case 2: */
	merge_sort({999, 612, 589, 856, 56, 945, 243});
	
	return 0;
}

