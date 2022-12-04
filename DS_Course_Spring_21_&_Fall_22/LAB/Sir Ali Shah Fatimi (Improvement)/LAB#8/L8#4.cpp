#include "F_Deque.hpp"
using std::cout;

int main(){
	const int N=10;//Queue Limit
	F_Deque<int, N> q;//using fixed size circular queue for normal queue operations
	
	for(int i=1;i<=N;++i){
		if(q.full()){//step 1
			cout<<"queue capacity is full!";
			break;
		}
		q.push_back(i);//step 2: same as enqueue in FIFO order
	}
	
	q.pop_front();//step 3: same as dequeue in FIFO order
	
	cout<<q;//traverse values in queue
	
	return 0;
}
