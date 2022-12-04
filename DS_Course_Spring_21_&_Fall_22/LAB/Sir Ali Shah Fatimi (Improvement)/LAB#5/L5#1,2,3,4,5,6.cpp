#include "SLL.hpp"

/* 
	task#1: create singly linked list class alongwith its node class 
			=>SLL.hpp
			
	task#2: Add a node at the end of a singly linked list
			=>push_back()
			
	task#3: Add a node at the front of a singly linked list (Prepend a new node)
			=>push_front()
			
	task#4: Add a node after a given node in a singly linked list
			=>use 'insert()' with '+1' index to insert data 
			  after 'nth' position node
			
	task#5: Delete a node from a singly linked list:
			a) at last =>pop_back()
			b) at random position =>erase()
			
	task#6: update a node in a singly linked list
			=>check whether respective node is present or not using '[] operator'
			  & then update
*/

int main(){
#if __cplusplus >= 201103L
	SLL<int> l1({1,2,3,4,5}),//O(N) operation, ascending order
			 l2({1,2,3,4,5},true);//O(N^2) operation, descending/stack order
#else
	SLL<int> l1,l2;
	for(int i=1;i<=5;++i){
		l1.push_back(i);//insert at last node
		l2.push_front(i);//insert at first node
	}
#endif
		
	std::cout<<"Initial State (after pushes):\n"
			   "l1: "<<l1<<"\n"
			   "l2: "<<l2<<'\n';
    
	l1.pop_back();//last node
	l2.erase(2);//3rd position node (random 'index+1' position)
	
	std::cout<<"\nAfter pops:\n"
			   "l1: "<<l1<<"\n"
			   "l2: "<<l2<<'\n';
	
//handling duplicates => struct(datatype, unique_id) => comparator for unique_id:
//	for(int i=0;i<l1.size();++i)
//		if(l1[i]==key)//incomplete...
	
	l1.insert(1+1, 404);//insert after 1st position/index node
	l2[1]=404;//update node data
	
	std::cout<<"\nAfter insert & update:\n"
			   "l1: "<<l1<<"\n"
			   "l2: "<<l2<<'\n';
	
	return 0;
}

/*Additional Note:
	for handling duplicates, we don't need to store key with same data everytime.
	
  Example:
	if there are 4 strings "ali" that needs to be stored with different ids,
 	then, mentioned method in lab, fails to store it efficiently,
	as node is storing redundant string again & again but with different key.
	
  Proposed Solution:
	 we can store string "ali" seperately with a list of duplicate unique_ids
	 as pair of string & singly-list of unique_ids (if limit is undefined),
     otherwise we can use std::vector or fixed size raw array as per requirement.
*/
