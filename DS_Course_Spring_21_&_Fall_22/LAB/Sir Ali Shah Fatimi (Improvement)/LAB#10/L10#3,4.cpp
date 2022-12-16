#include <iostream>
using std::cout;

//comparators:
bool greater(int a, int b){ return a>b; }
bool lesser(int a, int b){ return a<b; }

void heapify(int *arr, int size, int Data, bool (*comparator)(int, int)){
    int key=Data, left=2*Data+1, right=2*Data+2;
    if(left<size&&comparator(arr[left], arr[key]))
		key=left;
	if(right<size&&comparator(arr[right], arr[key]))
		key=right;
	if(key!=Data){
        std::swap(arr[Data], arr[key]);
        heapify(arr, size, key, comparator);
    }
}

void build_heap(int *arr, int size, bool (*comparator)(int, int)=greater){//defaults for max heap
	for(int i=size/2-1;i>=0;--i)
		heapify(arr, size, i, comparator);
}

void sort_heap(int *arr, int size, bool (*comparator)(int, int)=greater){//Note: use it after building heap
	for(int i=size-1;i>0;i--){
		std::swap(arr[0], arr[i]);
		heapify(arr, i, 0, comparator);	
	}
}

void print_heap(int *arr, int size){
	for(int i=0;i<size;i++)
		cout<<" -> "<<arr[i];
	cout<<'\n';
}

void delete_element(int *arr, int size, int Data, bool (*comparator)(int, int)=greater){//defaults for max heap
	int key;
	for(int i=0;i<size;i++)
		if(Data==arr[i]){
			key=i;
			break;
		}
	--size;
	arr[key]=arr[size];
	build_heap(arr, size, comparator);
}


void test_case_1(int *arr, int size){//Task 3, Part A: Max Heap
	build_heap(arr, size);
    cout<<"<--------MAX HEAP BEFORE DELETION-------->\n";
    print_heap(arr, size);
	
	delete_element(arr, size, 42);
    cout<<"\n\n<--------MAX HEAP AFTER DELETION-------->\n";
    print_heap(arr, size-1);
}

void test_case_2(int *arr, int size){//Task 3, Part B: Min Heap
	build_heap(arr, size, lesser);
    cout<<"<--------MIN HEAP BEFORE DELETION-------->\n";
    print_heap(arr, size);
	
	delete_element(arr, size, 35, lesser);
	cout<<"\n\n<--------MIN HEAP AFTER DELETION-------->\n";
	print_heap(arr, size-1);
}

void test_case_3(int *arr, int size){//Task 3, Part C: Sorted Max Heap
	build_heap(arr, size, lesser);
	sort_heap(arr, size, lesser);
	cout<<"\n\n<--------SORTED MAX HEAP-------->\n";
	print_heap(arr, size);
}

void test_case_4(){//Task 4: Sort Array by Heapify in  ascending order
	int arr[]={4,1,3,9,7},
    	size=sizeof(arr)/sizeof(arr[0]);
    
	build_heap(arr, size);
	sort_heap(arr, size);
	cout<<"\n\n<--------SORTED MIN HEAP-------->\n";
	print_heap(arr, size);
}

int main(){
    int arr[]={35,33,42,10,14,19,27,44,26,31},
    	size=sizeof(arr)/sizeof(arr[0]);
	
	test_case_1(arr, size);//Task 3, Part A: Max Heap
//	test_case_2(arr, size);//Task 3, Part B: Min Heap
//	test_case_3(arr, size);//Task 3, Part C: Sorted Max Heap
    
//	test_case_4();//Task 4: Sort Array by Heapify in  ascending order
    
    return 0;
}
