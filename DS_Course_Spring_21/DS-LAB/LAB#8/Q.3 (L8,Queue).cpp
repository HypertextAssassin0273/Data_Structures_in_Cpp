#include"DLL.hpp"

template<typename T>
void DLL<T>::find_first_non_repeating_element(){
    if(head){
       	bool flag=true;
		if(head->next)
			find_first_non_repeating_element(head,flag);
		if(flag)
			head->data='1';
	}
}
template<typename T>
void DLL<T>::find_first_non_repeating_element(node* temp,bool& flag){
	if (temp->next){
       	if (temp->data==temp->next->data){
       		find_first_non_repeating_element(temp->next,flag);
			if(flag){
				temp->next->data='1';
				flag=false;
			}
			return;
		}
   	}
}

int main(){
#if __cplusplus >= 201103L
	DLL<char> queue={'a','a','b','c'};
#else
	DLL<char> queue;
	queue.push_back('a');
	queue.push_back('a');
	queue.push_back('b');
	queue.push_back('c');
#endif
	cout<<"Input:"<<endl;
	queue.traverse_forward();
	queue.find_first_non_repeating_element();
	cout<<"Output:"<<endl;
	queue.traverse_forward();
	return 0;
}
