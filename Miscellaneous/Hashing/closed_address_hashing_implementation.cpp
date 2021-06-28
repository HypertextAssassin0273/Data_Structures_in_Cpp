#include<iostream>
using namespace std;

class Node{
	public:
	int data;
	Node *nxt;
	
	Node(int val){
		data = val;
		nxt = NULL;
	}
};

class LinkedList{
	Node *root;
	
	public:
		LinkedList(){
			root = NULL;
		}	
		
		void makenode(int val, Node *tmp){
			if(tmp->nxt == NULL)
				tmp->nxt = new Node(val);
			else
				makenode(val, tmp->nxt);
		}
		
		void createnode(int val){
			if(root == NULL){
				root = new Node(val);
				return;
			}
			makenode(val, root);
		}
		
		void disp(Node *tmp){
			if(tmp == NULL){
				cout<< "                 ";
				return;
			}else if(tmp->data != 0)
				cout<< tmp->data<< " | ";
			
			disp(tmp->nxt);	
		}
	
		Node* search(int val, Node *tmp){
			if( (tmp->data == val) || (tmp == NULL) )
				return tmp;
			search(val, tmp->nxt);	
		}
		
		Node* call_search(int val){
			Node* tmp = search(val, root);
			return tmp;	
		}	
		
		void display(){
			cout<< endl;
			disp(root);
		}
};

//open chaining
class Hashing{
	int buckets;
	LinkedList *HashTable;
	
	public:
		Hashing(int val){
			buckets = val;
			HashTable = NULL;
			HashTable = new LinkedList[buckets];
		}
		
		int Hash_function(int key){
			return (key%buckets);
		}
		
		void addkey_table(int val){
			int ind = Hash_function(val);
			HashTable[ind].createnode(val);			
		}
	
		Node* search(int target_ind){
			int ind = Hash_function(target_ind);
			Node *found = HashTable[ind].call_search(target_ind);
			return found;
		}
			
		bool deletekey(int val){
			Node* found = search(val);
			if(!found)
				return false;
			found->data = 0;	
			cout<< endl<< "The key with Value-"<< val<< " has been deleted successfully!"<< endl;
			display();
			return true;
		}
		
		void display(){
			for(int cnt = 0; cnt<buckets ; cnt++){
				HashTable[cnt].display();
				cout<< endl<< "|---------------|"<< endl;
			}
		}
};

int main(){
	Hashing Hashtable(5);
	
	Hashtable.addkey_table(5);
	Hashtable.addkey_table(3);
	Hashtable.addkey_table(4);
	Hashtable.addkey_table(10);
	Hashtable.addkey_table(8);
	Hashtable.addkey_table(9);
	
	Hashtable.display();
	Hashtable.deletekey(5);
	
	return 0;
}
