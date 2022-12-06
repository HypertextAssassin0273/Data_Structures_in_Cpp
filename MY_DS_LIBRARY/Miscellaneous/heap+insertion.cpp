#include<iostream>
using namespace std;

class Heap{
	int h_size;
	int *arr;
	int max_size;
	
	public:
		Heap(int max){
			max_size = max;
			arr = new int(max_size);
			h_size = 0;
		}	
		
		int get_parent(int cnt){
			return 	((cnt-1)/2);
		}
		
		//function for insert:
		bool insert(const int key){
			if(h_size == max_size){
				cout<< endl<< "Heap Overflow!"<< endl;
				return false;
			}
			h_size+= 1;	
			int cnt = h_size-1;
			arr[cnt] = key;
			
			//min-heap
			while( (cnt != 0) && (arr[get_parent(cnt)] > arr[cnt]) ){
				swap(arr[get_parent(cnt)], arr[cnt]);
				cnt = get_parent(cnt);
			}
				
			return true;	
		}
		
		int get_lft(const int prt)	const{
			return ((prt*2)+1);
		}
		
		int get_rt(const int prt)	const{
			return ((prt*2)+2);
		}
		
		void display()	const{
			for(int cnt = 0; cnt< h_size; cnt++)
				cout<< arr[cnt]<< " ";
			cout<< endl;
		}
};

//scope of main:
int main(){
	Heap HDS(10);
	
	HDS.insert(11);
	HDS.insert(3);
	HDS.insert(2);
	HDS.insert(1);	
	
	HDS.display();
	return 0;
}
