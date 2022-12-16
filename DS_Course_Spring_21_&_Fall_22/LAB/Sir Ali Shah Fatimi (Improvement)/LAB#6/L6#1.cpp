#include "List.hpp"
//#include <list>

/* Doubly Linked List Operations: */
int main(){
	List<int> DLL;
	
	DLL.push_back(11);	//i.   Insert a new node at the end of the list
	//11
	
	DLL.push_front(22);	//ii.  Insert a new node at the beginning of list.
	//22,11
	
	DLL.insert(2-1, 33);//iii. Insert a new node at given position.
	//22,33,11			//	   [here, inserting node at 2nd position OR 1st index]
	
	DLL.erase(0ull);	//iv.  Delete any node. (note: 0ull insead of 0 to resolve overload ambiguity error)
	//33,11				//	   [here, deleting 1st position node]
	
	DLL.traverse();		//v.   Print the complete doubly link list.
	//33->11->N			//	   [here, traversing in ascending order]
	
	return 0;
}
