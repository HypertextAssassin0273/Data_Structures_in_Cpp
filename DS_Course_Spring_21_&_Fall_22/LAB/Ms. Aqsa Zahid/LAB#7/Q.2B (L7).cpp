#include<iostream>
using namespace std;

//Note: include "Singly_Linked_List.hpp" after including iostream & using namespace std
#include"Singly_Linked_List.hpp"

template<typename T>
void SLL<T>::sort(bool direction_flag){//i.e. selection sort
	for (node* i_ptr=head;i_ptr;i_ptr=i_ptr->next){
        node* min_ptr=i_ptr;
       	for (node* j_ptr=i_ptr->next;j_ptr;j_ptr=j_ptr->next){
           	if(direction_flag){//i.e. ascending (by default)
				if(j_ptr->data<min_ptr->data)
        	       	min_ptr=j_ptr;
			}
			else{//i.e. descending
				if(j_ptr->data>min_ptr->data)
        	        min_ptr=j_ptr;
			}
       	}
        node::swap_data(*i_ptr,*min_ptr);
    }
}

int main(){
#if __cplusplus >= 201103L
	SLL<int> list{3,-1,7,5,4};
#else
	SLL<int> list;
	list.push_back(3);
	list.push_back(-1);
	list.push_back(7);
	list.push_back(5);
	list.push_back(4);
#endif
	cout<<"Before Sort:"<<endl;
	list.traverse();
	list.sort();//i.e. using selection-sort in ascending order
	cout<<"After Sort:"<<endl;
	list.traverse();
	return 0;
}
