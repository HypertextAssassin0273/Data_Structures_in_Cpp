#include<iostream>
#include<algorithm>
using namespace std;

int partition(int lb, int ub, int arr[]){
	int start = lb;
	int end = ub;
	int pivot = arr[lb];
	
	while(start<end){
		while(arr[start]<=pivot)
			start++;
		while(arr[end]>pivot)
			end--;
		if(start<end)
			swap(arr[start], arr[end]);			
	}
	swap(arr[lb], arr[end]);
	return end;	
}

void Quicksort(int arr[], int lb, int ub){
	if(lb<ub){
		int loc = partition(lb, ub, arr);
		Quicksort(arr, lb, loc-1);
		Quicksort(arr, loc+1, ub);
	}
}

int main(){
	int arr[5] = {10, 12, 3, 14, 5};

	Quicksort(arr, 0, 4);
	for(int cnt = 0; cnt<5; cnt++)
		cout<< arr[cnt]<< " ";
		
	return 0;
}
