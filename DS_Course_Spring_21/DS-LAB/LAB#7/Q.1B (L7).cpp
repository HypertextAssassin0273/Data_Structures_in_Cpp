#include<iostream>
using namespace std;

//Note: include "Singly_Linked_List.hpp" after including iostream & using namespace std
#include"Singly_Linked_List.hpp"

template<typename T>
void SLL<T>::sort(bool direction_flag){//i.e. improved bubble sort, using data-swap
	if (!head||!head->next)//i.e. do nothing if size is 0 or 1
    	return;
    bool swapped=true;
	for(node *i=nullptr,*j=nullptr;swapped;j=i){
		swapped=false;
	    for (i=head;i->next!=j;i=i->next){
	        if(direction_flag){
            	if (i->data>i->next->data){//i.e. ascending order
 	    	    	node::swap_data(*i,*i->next);
    	            swapped=true;
            	}
			}
            else{
            	if (i->data<i->next->data){//i.e. descending order
 	    	        node::swap_data(*i,*i->next);
    	           	swapped=true;
            	}
			}
        }
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
	list.sort();//i.e. using improved bubble-sort in ascending order
	cout<<"After Sort:"<<endl;
	list.traverse();
    return 0;
}
