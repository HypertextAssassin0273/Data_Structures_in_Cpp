#include <iostream>

using std::cout;

int counter=0;//global variable for tracking iterations

int interpolation_search(int arr[], int low, int high, int key){
	++counter;
	if(low>high||key<arr[low]||key>arr[high]) return -1;//bound exception safety
	int pos=low+(((double)(high-low)/(arr[high]-arr[low]))*(key-arr[low]));//Probing position w.r.t uniform distribution.
	return (arr[pos]==key?pos://Condition of target found
		   (arr[pos]<key?interpolation_search(arr, pos+1, high, key)://target is in right sub array
			interpolation_search(arr, low, pos-1, key)));//target is in left sub array
}

int binary_search(int arr[], int left, int right, int key){
	++counter;
    if(right<left) return -1;//bound exception safety
    int mid=left+(right-left)/2;//Setting pivot w.r.t middle index
	return (arr[mid]==key?mid://element is present at middle
		   (arr[mid]<key?binary_search(arr, mid+1, right, key)://element is in right sub array
			binary_search(arr, left, mid-1, key)));//element is in left sub array
}

int main(){
	int arr[]={10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47},
		n=sizeof(arr)/sizeof(arr[0]),//array size
		key=18;//Element to be searched
	
	int index=interpolation_search(arr, 0, n-1, key);
//	int index=binary_search(arr, 0, n-1, key);
	
	if(index!=-1)
		cout<<"Element found at index "<<index;
	else
		cout<<"Element not found.";
	
	cout<<"\nNo. of iterations: "<<counter;
	//conclusion: interpolation takes less ierations than binary search
	
	return 0;
}
