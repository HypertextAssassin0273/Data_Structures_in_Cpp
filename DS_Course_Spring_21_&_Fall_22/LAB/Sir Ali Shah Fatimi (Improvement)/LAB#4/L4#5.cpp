#include <iostream>

struct indexes{
	int intial, final;
	
	indexes(int i=0, int f=0)://default & parameterized ctor
		intial(i),final(f){}
	
	friend std::ostream& operator<<(std::ostream& out,const indexes& self){
			if(self.intial)
				out<<self.intial<<" and "<<self.final;
			else
				out<<"The complete array is sorted";
		return out;
	}
};

indexes get_unsorted_subarray_indexes(int arr[], int n){
	int s=0, e=n-1, i, max, min;
	//step 1(a)
	for (s=0;s<n-1;++s)
		if(arr[s]>arr[s+1])
			break;
	if (s==n-1)
		return indexes();
	
	//step 1(b)
	for(e=n-1;e>0;--e)
		if(arr[e]<arr[e-1])
			break;
	
	//step 2(a)
	min=max=arr[s];
	for(i=s+1;i<=e;i++){
		if(arr[i]>max)
			max=arr[i];
		if(arr[i]<min)
			min=arr[i];
	}
	
	//step 2(b)
	for(i=0;i<s;i++)
		if(arr[i]>min){
			s=i;
			break;
		}
	
	//step 2(c)
	for(i=n-1;i>=e+1;i--)
		if(arr[i]<max){
			e=i;
			break;
		}
	
	//step 3
	return indexes(s, e);
}

int main(){
	int arr[]={
		/* test_case 1: */
		10, 12, 20, 30, 25, 40, 32, 31, 35, 50, 60
		/* test_case 2: */
//		0, 1, 15, 25, 6, 7, 30, 40, 50
	},
	N=sizeof(arr)/4;
	
	std::cout<<"The unsorted subarray lies b/w the indexes: "
			 <<get_unsorted_subarray_indexes(arr, N);
	
	return 0;
}
