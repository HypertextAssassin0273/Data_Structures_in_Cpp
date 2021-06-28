#include<iostream>
using namespace std;

struct _pair{
	int val1,val2;
	_pair(int val1,int val2):val1(val1),val2(val2){}//i.e. defalut ctor
};
_pair find_largest_and_smallest(int arr[],int N){
	int largest=0,smallest=(~((unsigned int)0)/2);//i.e. max int size
	for(int i=0;i<N;++i){
	  	if(arr[i]>largest)
	  	largest=arr[i];
	  	else if(arr[i]<smallest)
	  	smallest=arr[i];
	}
	return _pair(largest,smallest);
}
int main(){  
    int arr[]={20,10,-22,50,120,40,80,10,60,70};
    #define N sizeof(arr)/sizeof(arr[0])
	_pair obj=find_largest_and_smallest(arr,N);
	cout<<"Largest: "<<obj.val1<<"\nSmallest: "<<obj.val2;
 }
