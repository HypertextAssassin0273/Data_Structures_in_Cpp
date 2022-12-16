#include "Circular_List.hpp"

/* Circular Doubly Linked List Operations: */
int main(){
	Circular_List<int> CDLL;
	
	CDLL.push_back(11);		//i.   Insert a new node at the end of the list
	//11
	
	CDLL.push_front(22);	//ii.  Insert a new node at the beginning of list.
	//22,11
	
	CDLL.insert(2, 33);		//iii. Insert a new node at given position.
	//22,33,11				//	   [here, inserting node at 2nd position]
	
	CDLL.erase(0);			//iv.  Delete any node.
	//33,11					//	   [here, deleting 1st position node]
	
	CDLL.traverse_forward();//v.   Print the complete circular doubly link list.
	//33->11->N				//	   [here, traversing in ascending order]
	
	return 0;
}
