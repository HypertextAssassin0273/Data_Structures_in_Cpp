#include"DLL.hpp"

int main(){
	//Note: using Queue FIFO/ascending order (i.e. push_front & pop_back only)
#if __cplusplus >= 201103L
	DLL<int> queue_Q,queue_D={1,2,3,4,5,6,7,8};
#else
	DLL<int> queue_Q,queue_D;
	for(int i=1;i<=8;++i)
		queue_D.push_back(i);
#endif
	cout<<"Before:\nD: ";
	queue_D.traverse_forward();
	cout<<"Q: ";
	queue_Q.traverse_forward();
	
	for(int i=0;i<3;++i)
		queue_Q.push_back(queue_D.pop_front(1));
	
	queue_D.push_back(queue_D.pop_front(1));
	
	queue_Q.push_back(queue_D.pop_front(1));

	for(int i=0;i<3;++i)
		queue_D.push_back(queue_D.pop_front(1));
	
	while(!queue_Q.empty())
		queue_D.push_back(queue_Q.pop_front(1));
	
	for(int i=0;i<4;++i)
		queue_D.push_back(queue_D.pop_front(1));
	
	cout<<"\nAfter:\nD: ";
	queue_D.traverse_forward();
	cout<<"Q: ";
	queue_Q.traverse_forward();
	
	return 0;
}
