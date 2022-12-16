#include <iostream>

using std::cout;

// problem analysis:
// assuming sorted in ascending order
// indexes: 0,2,4,... -> max values
// indexes: 1,3,5,... -> min values
// 10, 11 -> two case: equal sizes, non-equal sizes

//original: 1,2,3,4,5,6,7,8,9,10 (n=10)
//temp1: 1,2,3,4,5 	(n/2)
//temp2: 6,7,8,9,10 (n/2)
//rearranged: 10,1,9,2,8,3,7,4,6,5

//original: 1,2,3,4,5,6,7,8,9,10,11 (n=11)
//temp1: 1,2,3,4,5 	(n/2)
//temp2: 6,7,8,9,10,11 (n/2+1)
//rearranged: 11,1,10,2,9,3,8,4,7,5,6

void rearrange(int *arr,int size){
	int n1,n2; //temporary-array sizes
	if(size%2){ //odd
		n1=size/2;
		n2=size/2+1;
	}
	else //even
		n1=n2=size/2;
	
	int arr1[n1],arr2[n2]; //temporary/sub arrays
	int i,j; //iterators
	
	// copying 1st half i.e. sorted min values (from start)
	for(i=0;i<n1;++i)
		arr1[i]=arr[i];
	// copying 2nd half i.e. sorted max values (from last)
	for(;i<size;++i)
		arr2[i-n1]=arr[i];
	
	// copying back sorted 'min' values on 'odd' indexes
	for(i=0,j=1;i<n1;++i,j+=2)
		arr[j]=arr1[i];
	// copying back sorted 'max' values on 'even' indexes
	for(i=n2-1,j=0;i>-1;--i,j+=2)
		arr[j]=arr2[i];
}

void display(int* arr,int size){
	for (int i=0;i<size;++i)
		cout<<arr[i]<<' ';
	cout<<'\n';
}

int main(){
	{//local-scope (defined to manually destruct even-size array to save memory)
	cout<<"even size case:\n";
	int arr[]{1,2,3,4,5,6,7,8,9,10}, // sorted array
		N=sizeof(arr)/sizeof(arr[0]); //array size
	
	cout<<"original: ";
	display(arr, N);
	rearrange(arr, N);
	cout<<"rearranged: ";
	display(arr, N);
	}
	
	cout<<"\nodd size case:\n";
	int arr[]{1,2,3,4,5,6,7,8,9,10,11}, // sorted array
		N=sizeof(arr)/sizeof(arr[0]); //array size
	
	cout<<"original: ";
	display(arr, N);
	rearrange(arr, N);
	cout<<"rearranged: ";
	display(arr, N);
		
	return 0;
}
