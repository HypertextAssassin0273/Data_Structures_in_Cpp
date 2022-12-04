#include"SLL.hpp"

template<typename T>
bool SLL<T>::operator==(const SLL& other)const{
	if(_size!=other._size)
		return false;
	for(node *l1=head,*l2=other.head;l1;l1=l1->next,l2=l2->next)
    	if (l1->data!=l2->data)
      		return false;
  	return true;
}

template<typename T>//i.e. extra
bool SLL<T>::operator!=(const SLL& other)const{ return !(*this==other); }

int main(){
	SLL<int> stack1,stack2;
	stack1.push_front(404);
	stack1.push_front(1);
	stack1.push_front(2);
	stack1.push_front(3);
	
	stack2.push_front(404);
	stack2.push_front(1);
	stack2.push_front(2);
	stack2.push_front(3);
	
	cout<<(stack1==stack2?"true":"false");
	return 0;
}
