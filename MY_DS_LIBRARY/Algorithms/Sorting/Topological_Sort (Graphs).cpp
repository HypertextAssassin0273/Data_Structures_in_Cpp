#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//garbage values print hou rhin hain.
class Node{
public:
	int data;
	Node *next;
	
	Node(int key){
		data = key;
		next = NULL;
	}	
	
	Node(){ next = NULL; }
};

//Note: Each linkedlist is representing a vertex
class LinkedList{
	Node *root;
	int outdegree;
	int indegree;
	int size;
	
	public:
		LinkedList(){
			indegree = outdegree = size = 0;
			root = NULL;	
		}
		
		int getsize(){
			size = 0;
			for(Node *tmp = root; tmp!=NULL; tmp = tmp->next)
				size++;			
			return size;
		}
		
		int get_adjacent(const int tg_ind){
			int ind = 0;
			for(Node *tmp = root; tmp!=NULL; tmp = tmp->next){
				if(ind == tg_ind)
					return tmp->data;
				ind++;	
			}
			return -1;
		}
		
		int get_indegree()	const{
			return indegree;	
		}
		
		void set_indegree(const int num){
			indegree = num;	
		}
		
		int get_outdegree()	const{
			return outdegree;	
		}
		
		void set_outdegree(const int num){
			outdegree = num;	
		}
		
		void createnode(int key){
			if(root == NULL){
				root = new Node(key);
			}else{
				Node *tmp;
				for(tmp = root; tmp->next!=NULL; tmp = tmp->next);
				tmp->next = new Node(key);			
			}	
		}
		
		void disp(){
			for(Node *tmp = root; tmp!=NULL; tmp = tmp->next)
				cout<< tmp->data<< " ";
			cout<< endl;
		}
}; 

class Adjacencylist{
	LinkedList *lst;
	int vertices;
	
	public:
		Adjacencylist(int num){
			vertices = num;
			lst = NULL;
			lst = new LinkedList[num];
		}
		
		void addedge(int out, int in){
			if(in <= (vertices-1) && out <= (vertices-1) ){
				lst[out].createnode(in);
				lst[out].set_outdegree(lst[out].get_outdegree() + 1);
				lst[in].set_indegree(lst[in].get_indegree() + 1);		
			}	
		}
		
		void topologicalsort(){
			vector<int>indeg = this->get_allindegrees();
			vector<int>result;
			queue<int>tmp;
			
			for(int cnt = 0; cnt<vertices; cnt++){
				if(indeg[cnt] == 0)
					tmp.push(cnt);
			}
			
			while(!tmp.empty()){
				int val = tmp.front();
				tmp.pop();
				result.push_back(val);
				
				for(int cnt = 0; cnt<lst[val].getsize(); cnt++){
					int adj = lst[val].get_adjacent(cnt);
					indeg[adj]--;
					if(indeg[adj] == 0)
						tmp.push(adj);
				}
			}
			cout<< endl;
			for(int cnt = 0; cnt<result.size(); cnt++)
				cout<< result[cnt]<< " ";
		}
		
		void display(){
			cout<< endl<< "The adjacency list of the graph is: "<< endl;
			for(int cnt = 0; cnt<vertices; ){
				cout<< "Vertex-"<< cnt<< " -> ";
				lst[cnt++].disp();
			}
		}
		
		vector<int> get_allindegrees(){
			vector<int>tmp;
			for(int cnt = 0; cnt<vertices; cnt++)
				tmp.push_back( lst[cnt].get_indegree() );
			return tmp;
		}
};

//ENTRY POINT:
int main(){
	Adjacencylist Graphrep(5);
	
	Graphrep.addedge(2, 1);
	Graphrep.addedge(2, 0);
	Graphrep.addedge(0, 1);
	Graphrep.addedge(3, 1);
	Graphrep.addedge(3, 2);
	Graphrep.addedge(4, 3);
	Graphrep.addedge(4, 2);
	Graphrep.display();

	Graphrep.topologicalsort();
	
	return 0;	
}
