#include<iostream>
#include<vector>
using namespace std;

void swap(int &xp,int &yp){
    int temp=xp;
    xp=yp;
    yp=temp;
}
void bubble_sort(int arr[], int N){
    for (int i=0;i<N-1;++i){
    	bool swapped=false;
    	for (int j=0;j<N-i-1;++j)
        	if (arr[j]>arr[j+1]){
        	    swap(arr[j],arr[j+1]);
        	    swapped=true;
        	}
		if(!swapped)
 	 		break;
 	}
}
int find_longest_consecitive_sequence(int arr[],int N){
	bubble_sort(arr,N);
	vector<int> v;
	v.push_back(arr[0]);
	//insert repeated elements only once in the vector
	for (int i=1;i<N;++i){
		if (arr[i]!=arr[i-1])
			v.push_back(arr[i]);
	}
	int ans=0,count=0;
	for (int i=0;i<v.size();++i){
		if (i>0&&v[i]==v[i-1]+1)
			count++;
		else// reset the count
			count=1;
		ans=(ans>count)?ans:count;// update the maximum
	}
	return ans;
}

int main(){
	int arr[]={1,2,2,9,3,5,4,7};
	#define N sizeof(arr)/sizeof(arr[0])
	cout<<"Length of the Longest contiguous subsequence is: "
		<<find_longest_consecitive_sequence(arr,N)<<endl;
	return 0;
}

