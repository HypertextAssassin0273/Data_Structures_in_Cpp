#include<iostream>
using namespace std;

class Node{
	public:
	Node *nxt;
	int data;
	
	Node(const int data){
		this->data = data;
		this->nxt  = NULL;
	} 
	
	Node(){}
};

Node* createnode(int val){
	Node *tmp = new Node(val);
	return tmp;	
}

class LinkedList{  
	Node *root; 
	
	public:
		LinkedList(){
			root  = NULL;
		}	
		
		void addnode(Node *tmp, int val){
			if(tmp->nxt == NULL)
				tmp->nxt = createnode(val);
			else
				addnode(tmp->nxt, val);
		}
		
		void drive_addnode(int val){
			if(root == NULL)
				root = createnode(val);
			else
				addnode(root, val);
		}
		
		void print(){
			for(Node *tmp = root; tmp != NULL; tmp = tmp->nxt) 
				cout<< tmp->data<< " ";
			cout<< endl;
		}
};

class Graph{
	int num_vtx;
	LinkedList *list;
	
	public:
		Graph(int num_vtx){
			this->num_vtx = num_vtx;
			list = new LinkedList[num_vtx];	
		}
		
		//adjacency list:
		void addedge(int vertex1, int vertex2){			//an edge between vertex1 & vertex2
			list[vertex1].drive_addnode(vertex2);
		}
		
		void display_graph(){
			for(int cnt = 0; cnt<num_vtx; cnt++){
				cout<< endl<< "Vertex-"<< cnt<< endl;
				list[cnt].print();
				cout<< endl;
			}
		}
};

//ENTRY POINT:
int main(){
	int num_vertices = 5;
	
	Graph G1(num_vertices);
	G1.addedge(0, 1);
	G1.addedge(0, 2);
	G1.addedge(0, 3);
	G1.addedge(0, 4);
	G1.addedge(2, 3);
	G1.addedge(1, 2);
	G1.addedge(3, 2);
	G1.addedge(4, 5);
	G1.addedge(3, 0);
	
	G1.display_graph();
	system("PAUSE");
	return 0;
}
