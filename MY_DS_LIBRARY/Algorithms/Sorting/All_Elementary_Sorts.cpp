#include<iostream>
using namespace std;

void bubblesort(int arr[], int size){
	int arrt[size];
	for(int cnt = 0; cnt<size; cnt++)
		arrt[cnt] = arr[cnt];
		
	for(int cnt = 0; cnt<size; cnt++){
		for(int cnt2 = 0; cnt2<size-cnt-1; cnt2++)
			if(arrt[cnt2]>arrt[cnt2+1])
				swap(arrt[cnt2], arrt[cnt2+1]);
	}
	
	for(int cnt = 0; cnt<size; cnt++)
		cout<< arrt[cnt] << " ";
	cout<< endl;
}

void insertionsort(int arr[], int size){
	int arrt[size];
	for(int cnt = 0; cnt<size; cnt++)
		arrt[cnt] = arr[cnt];
		
	for(int cnt = 1; cnt<size; cnt++){
		int tmp = arr[cnt];
		int cnt2 = cnt-1;
		
		while(cnt2>=0 && arrt[cnt2]>tmp){
			arrt[cnt2+1] = arrt[cnt2];
			cnt2--;
		}
		arrt[cnt2+1] = tmp; 
	}
	
	for(int cnt = 0; cnt<size; cnt++)
		cout<< arrt[cnt] << " ";
	cout<< endl;
}

void selectionsort(int arr[], int size){
	int arrt[size];
	for(int cnt = 0; cnt<size; cnt++)
		arrt[cnt] = arr[cnt];
	
	for(int cnt = 0; cnt<size-1; cnt++){
		int min = cnt;
		int tmp = arrt[cnt];
		for(int cnt2 = cnt+1; cnt2<size; cnt2++){
			if(arrt[cnt2]< arrt[min])
				min = cnt2;
		}
		arrt[cnt] = arrt[min];
		arrt[min] = tmp;
	}
	
	for(int cnt = 0; cnt<size; cnt++)
		cout<< arrt[cnt] << " ";
	cout<< endl;
}

//ENTRY POINT:
int main(){
	int arr[] = {10, 4, 40, 11, 12, 16, 15};
	int size = 7;
	
	bubblesort(arr, size);
	insertionsort(arr, size);
	selectionsort(arr, size);
	
	return 0;
}
