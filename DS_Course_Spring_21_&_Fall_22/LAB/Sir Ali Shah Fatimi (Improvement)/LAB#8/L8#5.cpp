#include "D_Deque.hpp"
using std::cout;

int main(){
	//note: step 4 cannot be done since queue is a linked list, hence having capacity function makes no sense
	
	//note: using doubly linked list double eneded queue for normal queue operations
	D_Deque<int> q({1,2,3,4,5,6,7,8,9,10});//step 5: same as enqueue 10 times in FIFO order
	
	q.pop_front();//step 6: same as dequeue in FIFO order
	
	cout<<q;//traverse queue values in ascending order
	
	return 0;
}
