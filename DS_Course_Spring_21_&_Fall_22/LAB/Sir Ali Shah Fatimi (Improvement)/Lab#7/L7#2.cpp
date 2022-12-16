#include <iostream>

void quick_sort(int arr[], int low, int high){
    if(low>=high) return;
    int i=low-1, j=high+1, pivot=arr[(low+high)/2];
    while(true){
        while(arr[++i]<pivot);
        while(arr[--j]>pivot);
        if(i>=j) break;
        std::swap(arr[i], arr[j]);
    }
    quick_sort(arr, low, j);
    quick_sort(arr, j+1, high);
}

int main(){
	/* test case 1: */
//	int arr[]={5, 4, 3, 2, 1};
	
	/* test case 2: */
	int arr[]={999, 612, 589, 856, 56, 945, 243};
	
	quick_sort(arr, 0, sizeof(arr)/sizeof(arr[0])-1);
	
	std::cout<<"Sorted array \n";
	for (auto& it: arr)
		std::cout<<it<<' ';
	
	return 0;
}
