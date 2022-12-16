#include<iostream>
#include<queue>
using namespace std;

int calc_no_of_operations(int *arr, int size){
	priority_queue<int, vector<int>, greater<int>> pq;
	int n=0, d=0;
	for(int x=0;x<size;x++){
        if(!pq.empty() && pq.top() < arr[x]){
            d=arr[x]-pq.top();
            n+=d;
  			pq.pop();
            pq.push(arr[x]);
        }
		pq.push(arr[x]);
	}
	return n;
}

int main(){
	int arr[]={3,1,2,1},
   		size= sizeof(arr)/sizeof(arr[0]);
   	
    cout<<"Operation Required:"<<calc_no_of_operations(arr, size);
	
	return 0;
}

