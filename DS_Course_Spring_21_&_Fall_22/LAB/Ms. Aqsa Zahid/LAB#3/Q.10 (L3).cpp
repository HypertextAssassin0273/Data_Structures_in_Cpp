#include<iostream>
using namespace std;

void reverse_arr(int arr[],int start,int end){
	if (start>=end)
		return;
	int temp=arr[start];//i.e. swap start & end indexes
	arr[start]=arr[end];
	arr[end]=temp;
	reverse_arr(arr,start+1,end-1);
}

int main(){
	int arr[]={1,2,3,4,5,6};
	#define N sizeof(arr)/sizeof(arr[0])
	
	for (int i=0;i<N;++i)
		cout<<arr[i]<<" ";
		
	reverse_arr(arr,0,N-1);	
	cout<<"\nAfter Reversed:"<<endl;
	for (int i=0;i<N;++i)
		cout<<arr[i]<<" ";
	return 0;
}
