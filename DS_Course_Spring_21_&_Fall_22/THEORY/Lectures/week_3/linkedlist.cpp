#include <iostream>
using namespace std;
class Node{
	   public:
   int data;
   Node *next;
   Node(){
   	next=NULL;
   }
   	Node(int d) {
	   data = d; 
	   next = NULL; 
	}
};
class LinkedList{
	public:
	Node *head; // head of list 
	void push(int new_data){
   		Node *newNode = new Node(new_data);
  		newNode->next = head;
		head = newNode;
	}
	void displayList(){
   		Node *pnode = head;
   		while (pnode != NULL){
		   cout<<pnode->data<<"-->";
   			pnode = pnode->next;
		}
	}
	void append(int new_data) { 
        Node *newNode = new Node(new_data); 
		if (head == NULL) { 
			head = newNode;
			return; 
        } 
		// if not the head node traverse the list and add it to the last
		Node *last = head;
		while (last->next != NULL)
			last = last->next;
		last->next = newNode;
		return;
	}
	void insertAfter(Node *prev_node, int new_data){
		if (prev_node == NULL){
		cout<<"The given node is required and cannot be null"<<endl;
		return;
		}
		Node *newNode = new Node(new_data);
		newNode->next = prev_node->next;
		prev_node->next = newNode;
	}
	Node* deleteFirstNode(){
		if (head == NULL)
			return NULL;
   		Node *temp = head;
   		head = head->next;
   		delete temp;
   		return head;	
	}
	Node* deleteLastNode(){
	//do complete
	}
	
	void deleteAfter(int position){
	//do complete
	}
};
int main(){
   LinkedList *lList = new LinkedList();
   lList->push(20);
   lList->push(10);
   lList->push(30);
   lList->push(40);
   lList->push(50);
   lList->append(11);
   lList->append(12);
   lList->append(13);
   lList->append(14);
   lList->push(15);
   lList->insertAfter(lList->head,100);
   lList->insertAfter(lList->head->next,500);
   lList->insertAfter(lList->head->next->next,56);
   cout<<"Final linked list: ";
   lList->displayList();
   cout<<endl;
   lList->deleteFirstNode();
   lList->deleteFirstNode();
   lList->deleteFirstNode();
   lList->push(99);
   cout<<"Final linked list: ";
   lList->displayList();
   cout<<endl;
//   lList->deleteLastNode();
//   lList->push(88);
//   lList->deleteLastNode();
//   cout<<"Final linked list: ";
//   lList->displayList();
//   cout<<endl;
//   lList->deleteAfter(50);
//   lList->deleteAfter(7);
//   cout<<"Final linked list: ";
//   lList->displayList();
//   cout<<endl;
   return 0;
}

