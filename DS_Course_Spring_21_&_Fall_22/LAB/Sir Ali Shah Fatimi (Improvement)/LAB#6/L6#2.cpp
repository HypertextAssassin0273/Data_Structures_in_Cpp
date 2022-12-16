#include "Circular_Forward_List.hpp"

/* Circular Singly Linked List Operations: */
int main(){
	Circular_Forward_List<int> CSLL;
	
	CSLL.push_back(11);	//i.   Insert a new node at the end of the list
	//11
	
	CSLL.push_front(22);//ii.  Insert a new node at the beginning of list.
	//22,11
	
	CSLL.insert(2, 33);	//iii. Insert a new node at given position.
	//22,33,11			//	   [here, inserting node at 2nd position]
	
	CSLL.erase(0);		//iv.  Delete any node.
	//33,11				//	   [here, deleting 1st position node]
	
	CSLL.traverse();	//v.   Print the complete circular link list.
	//33->11->N			//	   [here, traversing in ascending order]
	
    return 0;
}
