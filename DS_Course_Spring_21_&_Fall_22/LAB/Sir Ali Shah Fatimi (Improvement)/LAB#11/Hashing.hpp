#ifndef HASHING_GUARD
#define HASHING_GUARD 1

#include<iostream>

#define MAX_SIZE 10

template<typename T>
struct hash_table{
	int key;
	T value;
	
	hash_table(int key=0, const T& value=T()):
		key(key), value(value){}
};

template<typename T, char hash_type='D'>
class Hash_Map{
	typedef hash_table<T> HT;
	
	HT **table;
	int count;
	
public:
	Hash_Map():
		count(0), table(new HT*[MAX_SIZE]{}){}
	
	int hash(int)const;
	
	int get_count()const{ return count; }
	bool isEmpty()const{ return !count; }
	
	
	void insert(int key, const T& value){
		if(count>=10){
			std::cout<<"Hash Table is Already Full.\n";
			return;
		}
		int p=hash(key);
		HT *newEntry=new HT(key, value);
		count++;
		if(!table[p]){
			table[p]=newEntry;
			return;
		}
		for(int i=0;i<MAX_SIZE;i++){
			if(table[p%MAX_SIZE]){
				++p;
				continue;
			}else{
				table[p%MAX_SIZE]=newEntry;
				return;
			}
		}
	}

	int search(int key){
		int pos=hash(key);
		for(int i=0;i<MAX_SIZE;++i){
			if(table[pos%MAX_SIZE]->key==key)
				return pos%MAX_SIZE;
			else ++pos;
		}
		return -1;
	}

	void remove(int key){	
		int pos=search(key);
		if(pos==-1){
			std::cout<<"Key doesnt exist\n";
			return;
		}
		--count;
		delete table[pos];
		table[pos]=nullptr;
	}
	
	void traverse()const{
		std::cout<<"Key   Value\n";
		for(int i=0;i<MAX_SIZE;++i)
			if(table[i])
				std::cout<<table[i]->key<<"   "<<table[i]->value<<'\n';
	}
	
	~Hash_Map(){ delete []table; }
};

template<>
int Hash_Map<int, 'D'>::hash(int key)const{ return key%MAX_SIZE; }
template<>
int Hash_Map<std::string, 'D'>::hash(int key)const{ return key%MAX_SIZE; }

#endif
