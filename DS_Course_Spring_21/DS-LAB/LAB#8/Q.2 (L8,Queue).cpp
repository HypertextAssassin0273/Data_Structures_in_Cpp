#include"DLL.hpp"

template<typename T>
T DLL<T>::get_minimum(){
	if(!head)
		throw false;
	node *temp=head;
	T min=temp->data;
	for(;temp;temp=temp->next)
    	if(temp->data<min)
    		min=temp->data;
	return min;
}

int main(){
#if __cplusplus >= 201103L
	DLL<int> queue={1,2,3,4,5,6,7,8};
#else
	DLL<int> queue;
	for(int i=1;i<=8;++i)
		queue.push_back(i);
#endif
	cout<<"after 8 push_backs: ";
	queue.traverse_forward();
	
	queue.pop_back();
	queue.pop_back();
	cout<<"after 2 pop_backs: ";
	queue.traverse_forward();
	
	queue.pop_front();
	queue.pop_front();
	cout<<"after 2 pop_fronts: ";
	queue.traverse_forward();
	
	queue.push_front(-7);
	queue.push_front(77);
	cout<<"after 2 push_fronts: ";
	queue.traverse_forward();
	
	cout<<"size: "<<queue.size()<<endl;
	cout<<"min: "<<queue.get_minimum();	
	return 0;
}
