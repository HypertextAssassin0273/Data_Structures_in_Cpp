#include<iostream>
#include<limits.h>
using namespace std;

class Hashtable{
	int buckets;
	int *table;
	
	public:
		Hashtable(int num){
			buckets = num;
			table = NULL;
			table = new int [buckets];
			for(int cnt = 0; cnt<buckets; cnt++)
				table[cnt] = INT_MIN;
		}	
		
		//insert an element:
		void insert(int val){
			int num = 0, index = (val + 1) % buckets;
			while(table[index] != INT_MIN){
				index = (index + 1) % buckets;
				num++;
				if(num == buckets)
					break;
			}
			if(num == buckets)
				cout<< endl<< "No place found to insert this element"<< endl;
			else
				table[index] = val;
		}
		
		int search(int val){
			int cnt = 0, ind = (val + 1) % buckets;
			while(cnt++ != buckets){
				if(table[ind] == val){
					cout<< endl<< endl<< "Element found at position-"<< ind+1;
					return ind;
				}else if(table[ind] == INT_MIN){	//shows discontinuity
					cout<< endl<< "No such element found!"<< endl;
					return -1;
				}
				ind = (ind + 1) % buckets;
			}
			if(cnt-1 == buckets)
				cout<< endl<< "No such element found!"<< endl;
			return -1;	
		}
		
		void _delete(int val){
			int ind = search(val);
			if(ind== -1)
				return;	
			cout<< " and deleted!"<< endl;
			table[ind] = INT_MAX;
			cout<< endl<< "Displaying the modified list:"<<endl;
			disp();
		}
		
		void disp()	const{
			for(int cnt = 0; cnt<buckets; cnt++){
				if(table[cnt] != INT_MIN && table[cnt] != INT_MAX)
				cout<< table[cnt]<< endl;
				else
					cout<< "EMPTY"<< endl;
			}
		}
};

//ENTRY POINT:
int main(){
	Hashtable Hashing(10);
	
	Hashing.insert(2);
	Hashing.insert(3);
	Hashing.insert(5);
	Hashing.insert(7);
	Hashing.disp();
	
	Hashing._delete(3);
	
	system("PAUSE");
	return 0;
}
