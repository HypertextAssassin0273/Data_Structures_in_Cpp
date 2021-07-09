#include<iostream>
#include<cmath>
using namespace std;

//Note: Treats array elements as indexes
void find_duplicates(int arr[], int N){//i.e. for unsorted array
	cout<<"The repeating elements are:"<<endl;
	for (int i=0;i<N;++i){
		if (arr[abs(arr[i])]>=0)
			arr[abs(arr[i])]=-arr[abs(arr[i])];
		else
			cout<<abs(arr[i])<<" ";
	}
}

int main(){
	int arr[]={1,2,3,1,3,6,6,7,11};
	#define N sizeof(arr)/sizeof(arr[0])
	find_duplicates(arr,N);
	return 0;
}
