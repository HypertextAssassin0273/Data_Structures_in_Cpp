#include <iostream>

using std::cout;

//part#1: generalized approach for sorting given array in both order

template<typename T>
void _swap(T& a, T& b){
	T temp=std::move(a);
    a=std::move(b);
    b=std::move(temp);
}

// ascending & descending functions => act as comparators
template<typename T>
void ascending(T* arr, int j, bool& swap_flag){
	if(arr[j+1]<arr[j]){
		_swap(arr[j+1],arr[j]);
		swap_flag=false;
	}
}
template<typename T>
void descending(T* arr, int j, bool& swap_flag){
	if(arr[j+1]>arr[j]){
		_swap(arr[j+1],arr[j]);
		swap_flag=false;
	}
}

// generalized sort function (for both ascending & descending orders)
template<typename T>
void sort(T *arr,int size, void (*compare_func)(T*, int, bool&)){
	int i,j; //iterators
	bool swap_flag;
	for(i=0;i<size-1;++i){
		swap_flag=true;
		for(j=0;j<(size-1)-i;++j)
			compare_func(arr, j, swap_flag);
		//optimization flag
		if(swap_flag) return;
	}
}

template<typename T>
void display(T* arr,int size){
	for (int i=0;i<size;++i)
		cout<<arr[i]<<' ';
	cout<<'\n';
}

int main(){
	constexpr int N=10; //array size
	
	//stack/local 1d array
	int arr1[N]{2,7,8,4,1,5,6,10,9,3};
//	for (i=0;i<N;++i)
//		cin>>arr1[i]; //keyboard input
	
	//heap/dynamic 1d array
	int *arr2=new int[N]{2,7,8,4,1,5,6,10,9,3};
//	for (i=0;i<N;++i)
//		cin>>arr2[i];
	
	sort(arr1, N, ascending);
	display(arr1, N);
	
	sort(arr2, N, descending);
	display(arr2, N);
	
	delete []arr2;// deallocating heap memory
	
	//extra
//	char arr3[]{'S','g','a','b','v','C','c'};
//	N=sizeof(arr3)/sizeof(arr3[0]);
	
//	sort(arr3, N, ascending);
//	display(arr3, N);
	
	return 0;
}
