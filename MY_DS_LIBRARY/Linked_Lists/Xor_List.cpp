#include "Xor_List.hpp"

/* XOR Doubly Linked List Operations: */
int main(){
#if __cplusplus >= 201103L
	xor_list<int> xlist({1,2,3,4});
#else
	xor_list<int> xlist;
	for(int i=1;i<5;++i)
		xlist.push_back(i);
#endif
	xlist.push_front(0);//0 1 2 3 4
	
	xlist.push_back(xlist.pop_front(true));//0 1 2 3 4-> 1 2 3 4 0 (node transfer)
	
	xlist.pop_back();//1 2 3 4 0-> 1 2 3 4
	
	xlist.reverse();//1 2 3 4-> 4 3 2 1
	
	xlist.traverse_forward();
	xlist.traverse_backward();
	return 0;
}
/* References:
https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/
https://www.youtube.com/watch?v=hMcHVfu3E8U
*/
