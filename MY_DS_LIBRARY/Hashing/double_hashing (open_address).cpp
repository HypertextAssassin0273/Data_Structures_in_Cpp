#include<iostream>
using namespace std;

class Hashing{
	int buckets;
	int *table;
		
	public:
		Hashing(int cap){
			buckets = cap;
			table = new int[buckets];
			for(int cnt = 0; cnt<buckets; cnt++)
				table[cnt] = -404;
		}
		
		int hash_func(int val){
			return ((3*val+1) % buckets);
		}
		
		int hash_func2(int val){
			return ((2*val+3) % buckets);
		}
		
		void insert(int key){
			int loop = 0, cnt = 0, hash_ind = hash_func(key), hash_ind2 = hash_func2(key);
			while(table[hash_ind]!= (-404)){
				if(loop == buckets)
					break;
				loop++;
				hash_ind = (hash_ind + hash_ind2*cnt)%buckets;
				cnt++;
			}
			if(loop == buckets){
				cout<< "can't add!"<< endl;
				return;
			}
			table[hash_ind] = key;			
		}
		
		void disp()	const{
			for(int cnt = 0; cnt<buckets; cnt++){
				if(table[cnt] != -404)
				cout<< table[cnt]<< endl;
				else
					cout<< "EMPTY"<< endl;
			}
		}
};

int main(){
	Hashing Hashings(5);
	
	Hashings.insert(155);
	Hashings.insert(570);
	Hashings.insert(850);
	Hashings.insert(590);
	Hashings.disp();
	
	return 0;
}
