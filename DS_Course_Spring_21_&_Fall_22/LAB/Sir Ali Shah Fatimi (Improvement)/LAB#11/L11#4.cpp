#include "Pair.hpp"
#include "Forward_List.hpp"
using namespace std;

#define MAX_SIZE 10

template<typename T, char hash_type='D'>
class Hash_Map{
	typedef Forward_List<Pair<int, T>> FL;
	
	FL table[MAX_SIZE];//array of singly-list objects
	int count;
	
public:
	Hash_Map():count(0){}
	
	int hash(int key)const{ return key%MAX_SIZE; }
	
	int get_count()const{ return count; }
	bool isEmpty()const{ return !count; }
	
	void insert(int key, const T& value){
		int pos=hash(key);
		count++;
		if(table[pos].empty()){
			table[pos].push_front(Pair<int, T>(key, value));
			return;
		}
		for(int i=0;i<MAX_SIZE;++i, ++pos)
			if(table[pos%MAX_SIZE].empty()){
				table[pos%MAX_SIZE].push_front(Pair<int, T>(key, value));
				return;
			}
	}

	int search(int key){
		int pos=hash(key);
		for(int i=0;i<MAX_SIZE;++i,++pos)
			if(!table[pos%MAX_SIZE].empty()&&table[pos%MAX_SIZE].front().first==key)
				return pos%MAX_SIZE;
		return -1;
	}

	void remove(int key){	
		int pos=search(key);
		if(pos==-1){
			std::cout<<"Key doesnt exist\n";
			return;
		}
		--count;
		table[pos].pop_front();
	}
	
	void traverse()const{
		std::cout<<"Key   Value\n";
		for(int i=0;i<MAX_SIZE;++i)
			if(!table[i].empty())
				std::cout<<table[i].front()<<'\n';
	}
};

int main(){
    Hash_Map<string> ob;
    int s;
    string value;
    for(int i=0;i<5;++i){
        cout<<"Enter ID: ";
        cin>>s;
        cout<<"Enter number: ";
        cin>>value;
        ob.insert(s, value);
    }
    
	cout<<(ob.isEmpty()?"empty\n":"Not Empty\n")
    	<<"Size of contact bookey: "<<ob.get_count()
    	<<"\nEnter the student ID for search : ";
    cin>>s;
    
    cout<<"Pair found at index : "<<ob.search(s)
    	<<"\nEnter the pair to be deleted : ";
    cin>>s;
    
    ob.remove(s);
    
	cout<<"Size of contact book: "<<ob.get_count()<<'\n';
    ob.traverse();
    
    return 0;
}
