#include <iostream>
using namespace std;

//part#2: generalized approach for sorting 'array of pointers' in both order (address book-keeping method)
/*advantages:
	1) saves memory as data is stored once [i.e. memory complexity O(3N) => O(N)] 
	2) operations are performed without changing original array
*/

template<typename T>
void _swap(T& a, T& b){
	T temp=std::move(a);
    a=std::move(b);
    b=std::move(temp);
	// here 'move' optimizes swap for heap objects
	// refer to move-semantics (i.e. rule of five) [C++11 construct]
}

// ascending & descending functions => act as comparators
template<typename T>
void ascending(T** arr, int j, bool& swap_flag){//accessing array as 2d pointer to array of pointers
	if(*arr[j+1]<*arr[j]){
		_swap(arr[j+1],arr[j]);
		swap_flag=false;
	}
}
template<typename T>
void descending(T** arr, int j, bool& swap_flag){
	if(*arr[j+1]>*arr[j]){
		_swap(arr[j+1],arr[j]);
		swap_flag=false;
	}
}

// generalized sort function (for both ascending & descending orders)
template<typename T>
void sort(T **arr,int size, void (*compare_func)(T**, int, bool&)){
	int i,j;  //iterators
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
void display(T *arr, int N){ //for normal 1d array
	for (int i=0;i<N;++i)
		cout<<arr[i]<<' ';
	cout<<'\n';
}
template<typename T>
void display(T **arr, int N){ //for array of ptrs (overloaded version)
	for (int i=0;i<N;++i)
		cout<<*arr[i]<<' ';
	cout<<'\n';
}

int main(){
	constexpr int N=5; //array size
	
	int arr[N]{2,7,8,4,1}; //stack/local 1d array
//	char arr[N]{'d','z','a','l','r'}; //N=5
//	string arr[N]{"good","awesome","lol","raw","light"}; //N=5
	
//	for (i=0;i<N;++i)
//		cin>>arr1[i]; //keyboard input
	
	int *asc[N]/*ascending*/, //array of pointers
		*dsc[N]/*descending*/; 
	
	for (int i=0;i<N;++i) //assigning respective addresses of N blocks of 'arr'
		asc[i]=dsc[i]=&arr[i];	
	
	cout<<"BEFORE SORTING:-\n"
		<<"'arr' original array:\n";
	display(arr, N);
	cout<<"'ascending' array of ptrs:\n";
	display(asc, N);
	cout<<"'descending' array of ptrs:\n";
	display(dsc, N);
	
	sort(asc, N, ascending);
	sort(dsc, N, descending);
	
	cout<<"\nAFTER SORTING:-\n"
		<<"'arr' original array:\n";
	display(arr, N);
	cout<<"'ascending' array of ptrs:\n";
	display(asc, N);
	cout<<"'descending' array of ptrs:\n";
	display(dsc, N);
	
	return 0;
}
