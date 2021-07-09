#include"SLL.hpp"

template<typename T>//i.e. extra
void SLL<T>::fill_other_reversely(SLL &other){//i.e. transfers nodes to 'other' in reverse order
	other.clear();
	while(head)
		other.push_front(pop_front(1));
}

template<typename T>
void SLL<T>::fill_other_reversely(SLL &other,bool)const{//i.e. copies nodes to 'other'....
	other.clear();
#if __cplusplus >= 201103L
	for(const auto& it:*this)
		other.push_front(it.data);
#else
	for(iterator it=head;it!=nullptr;++it)
		other.push_front(it->data);
#endif
}

int main(){
	SLL<int> stack1,stack2;
	
	cout<<"Transfering Nodes Reversely (stack1-> stack2):-"<<endl;
	stack1.push_front(99);
	stack1.push_front(88);
	stack1.push_front(77);
	stack1.push_front(66);
	
	stack2.push_front(404);
	stack2.push_front(1);
	stack2.push_front(2);
	stack2.push_front(3);

	cout<<"Before:"<<endl;
	stack1.traverse();
	stack2.traverse();
	
	stack1.fill_other_reversely(stack2);
	
	cout<<"After:"<<endl;
	stack1.traverse();
	stack2.traverse();
	
	cout<<"\nCopying Nodes Reversely (stack1-> stack2):-"<<endl;
	stack1.push_front(123);
	stack1.push_front(456);
	stack1.push_front(789);
	
	cout<<"Before:"<<endl;
	stack1.traverse();
	stack2.traverse();
	
	stack1.fill_other_reversely(stack2,1);
	
	cout<<"After:"<<endl;
	stack1.traverse();
	stack2.traverse();
	return 0;
}
