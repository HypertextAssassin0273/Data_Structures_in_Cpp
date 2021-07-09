#include<iostream>
using namespace std;

int find_duplicates_R(int arr[],int low,int high){//i.e. for sorted array (Recursive method)
	if (low>high) 
		return -1; 
	int mid=(low+high)/2;
	//i.e. checks if the mid element is repeating one  
	if (arr[mid]!=mid+1){
		if (mid>0&&arr[mid]==arr[mid-1])
			return mid;
		//i.e. checks duplicates present in left side
		return find_duplicates_R(arr,low,mid-1);
	}
	//i.e. checks duplicates present in right side
	return find_duplicates_R(arr,mid+1,high);
}

int main(){
	int arr[]={1,2,3,4,4,5};
	#define N sizeof(arr)/sizeof(arr[0])
	int index=find_duplicates_R(arr,0,N-1);
	if (index!=-1)
		cout<<arr[index];
	return 0;
}
