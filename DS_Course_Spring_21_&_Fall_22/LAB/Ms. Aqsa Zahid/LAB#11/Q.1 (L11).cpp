#include<iostream>
using namespace std;

class MaxHeap{
	int *arr; // pointer to array of elements in heap
	int capacity; // maximum possible size of min heap
	int size;
public:
	MaxHeap(int capacity):
		size(0),capacity(capacity),arr(new int[capacity]){}
	
	int getSize(){ return size; }// returns size of heap
	int getparent(int child){ return (child%2==0)?(child/2)-1:(child/2); }//returns index of parent node
	int getleft(int parent){ return (2*parent+1); }//returns index of left parent node
	int getright(int parent){ return (2*parent+2); }//returns index of right parent node
	int getMax(){ return arr[0]; }//returns the highest value/max value
	bool isleaf(int i){return (i>=size)?true:false; }//to find if the index is leaf or not
	
	void siftup(int i){//sorts the values in heap order after a value is inserted
		if(i == 0)
			return; //only one element in the array
		int parent_index = getparent(i); // get the index of the parent
		if(arr[parent_index] < arr[i]){
			int temp = arr[parent_index]; //if value at parent index is less than inserted value
			arr[parent_index] = arr[i]; // swap the values
			arr[i] = temp;
			siftup(parent_index); // loop untill it satisfies parent child max heap relationship
		}
	}
	void siftdown(int i){//sorts the values in heap order after a value is popped out
		int l = getleft(i);
		int r = getright(i);
		if(isleaf(l))
			return;
		int maxIndex = i;
		if(arr[l] > arr[i])
			maxIndex = l;
		if(!isleaf(r) && (arr[r] > arr[maxIndex]))
			maxIndex = r;
		if(maxIndex != i){
			int temp = arr[i];
			arr[i] = arr[maxIndex];
			arr[maxIndex] = temp;
			siftdown(maxIndex);
		}
	}
	void insert(int k){//inserts value in heap
		arr[size] = k; // insert the value into array
		siftup(size);
		size++; //increment the size of the array
	}
	int extractMax(){//extracts/pops the highest value from heap
		int max = arr[0];
		arr[0] = arr[size - 1];
		size--;
		siftdown(0);
		return max;
	}
	int removeAt(int K){//extracts/pops the value of given index from heap
		int r = arr[K];
		arr[K] = arr[size -1]; // replace with rightmost leaf
		size-- ;
		int p = getparent(K);
		if(K == 0 || arr[K] < arr[p])
			siftdown(K);
		else
			siftup(K);
		return r;
	}
	void heapify(int *array, int len){//converts the given array into max heap
		size = len;
		arr = array;
		for(int i=size-1; i>=0; --i)
			siftdown(i);
	}
	
	~MaxHeap(){ delete []arr; }
};

int main(){
//	MaxHeap heap(20);//2 3 5 6 4 15 45 77 150 120 88
//	heap.insert(2);
//	heap.insert(3);
//	heap.insert(5);
//	heap.insert(6);
//	heap.insert(4);
//	heap.insert(15);
//	heap.insert(45);
//	heap.insert(77);
//	heap.insert(150);
//	heap.insert(120);
//	heap.insert(88);
	return 0;
}
