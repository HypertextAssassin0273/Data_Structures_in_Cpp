#include <iostream>
using namespace std;

#define MAX_SIZE 10

void heapify(int *arr, int size, int Data){
    int key=Data, left=2*Data+1, right=2*Data+2;
    if(left<size&&arr[left]> arr[key])
		key=left;
	if(right<size&&arr[right]> arr[key])
		key=right;
	if(key!=Data){
        std::swap(arr[Data], arr[key]);
        heapify(arr, size, key);
    }
}

void insert(int *arr, int& size, int Data){
	if(size>=MAX_SIZE)
		cout<<"\n<-----OVERFLOW OR MEMORY FULL----->\n";
	else{
		arr[size]=Data;
		if(size++)
			for(int x=(size/2)-1;x>=0;x--)
				heapify(arr, size, x);
	}
}

void delete_node(int *arr, int& size, int Data){
	int index;
	for(int i=0;i<size;++i)
		if(arr[i]==Data){
			index=i;
			break;
		}
	size--;
	arr[index]=arr[size];
	for(int x=(size/2)-1;x>=0;x--)
		heapify(arr, size, x);
}

void print_heap(int *arr, int size){
	for(int i=0;i<size;i++)
		cout<<" -> "<<arr[i];
	cout<<'\n';
}

int main(){
	int size=0, arr[MAX_SIZE]{};
	
	insert(arr, size, 55);
	insert(arr, size, 77);
	insert(arr, size, 11);
	insert(arr, size, 66);
	insert(arr, size, 44);
	insert(arr, size, 88);
	insert(arr, size, 22);
	
	cout<<"\n<=====BEFORE DELETION======>\n";
	print_heap(arr, size);
	
	delete_node(arr, size, 88);
	cout<<"\n<=====AFTER DELETION======>\n";
	print_heap(arr, size);
	
	return 0;
}
