#if __cplusplus < 201103L
#include "warning.hpp"
#else
#include <iostream>

using std::cout;

/* problem description: */
//=> sort array with {both tail & non-tail} recursion methods
//given input: {12, 11, 13, 5, 6, 7}
//expected output: {5, 6, 7, 11, 12, 13} => 'ascending' order

/* part 'a': tail recursion */
//M#1 (as loop):
void tr_sort(int* arr,const int N, int i=0, int j=0){
	if(i==N-1) return;//outer_loop {terminating condition}
	if(j==(N-1)-i) return;//inner_loop {terminating condition}
		if(arr[j]>arr[j+1]){//swap (in ascending order)
			int temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
	tr_sort(arr, N, i, j+1);//inner_loop
	tr_sort(arr, N, i+1, 0);//outer_loop
}
//M#2 (with return, extra):
bool tr_sort_2(int* arr,const int N, int i=0, int j=0){
	if(i==N-1) return true;
	if(j==(N-1)-i) return true;
		if(arr[j]>arr[j+1]){//swap (in ascending order)
			int temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
	return tr_sort_2(arr, N, i+1, 0)&&tr_sort_2(arr, N, i, j+1);
	//1st completes inner_loop recursion, then starts outer_loop & performs swap
}

/* part 'b': non-tail (head) recursion {i.e. similar to loop} */
void hr_sort(int* arr,const int N, int i=0, int j=0){
	if(i<N-1) hr_sort(arr, N, i+1, 0);//outer_loop
	if(j<(N-1)-i) hr_sort(arr, N, i, j+1);//inner_loop
		if(arr[j]>arr[j+1]){//swap (in ascending order)
			int temp=arr[j];
			arr[j]=arr[j+1];
			arr[j+1]=temp;
		}
}

template<int N, typename T=void>//N => array size, T => sort_function return type
void display_after_sort(int (&&arr)[N],//array of r_value_references [C++11 construct] => temporary array
						T (*sort_func)(int*,const int, int, int)){//function_pointer
	sort_func(arr, N, 0, 0);
	/*Note: need to explicitly pass inital_values for i & j iterators
			since default parameters don't work for function_pointers
	*/
	for(const auto& it:arr)//traverse by built-in raw_array_iterator [C++11 construct]
		cout<<it<<' ';
}//Benefit: passed array gets immediately deallocated when control exits function scope

int main(){
	cout<<"tail recursive sort (part a):-\n"
		<<"method#1 (as loop):\n";
	display_after_sort<6>(
		{12, 11, 13, 5, 6, 7},
		tr_sort
	);
	
	cout<<"\nmethod#2 (with return):\n";
	display_after_sort<6, bool>(
		{12, 11, 13, 5, 6, 7},
		tr_sort_2
	);
	
	cout<<"\n\nhead recursive sort (part b):-\n";
	display_after_sort<6>(
		{12, 11, 13, 5, 6, 7},
		hr_sort
	);
	
	return 0;
}
#endif
