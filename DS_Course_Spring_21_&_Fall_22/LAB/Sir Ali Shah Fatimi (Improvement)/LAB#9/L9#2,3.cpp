#include "BST.hpp"
#include <stack>
using std::cout;

template<typename T>
void BST<T>::iterative_pre_order_traversal()const{//task 3 (part B)
	std::stack<node*> s;
	if(!root) return;
	s.push(root);
	while(!s.empty()){
		node *curr=s.top();
		s.pop();
		cout<<curr->key<<' ';
		if(curr->right)
			s.push(curr->right);
		if(curr->left)
			s.push(curr->left);
	}
}

int main(){
#if __cplusplus >= 201103L
	BST<int> tree({15,10,20,8,12,16,25});//task 2: using move_initializer_list format
#else
	BST<int> tree;
	
	int arr[]={15,10,20,8,12,16,25}, N=sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0;i<N;++i)//task 2
		tree.insert(arr[i]);
#endif
	
	cout<<"Recursive:-"
		<<"\nPre-order traversal: ";
	tree.pre_order_traversal();//task 3 (part A)
	
	cout<<"\nIn-order traversal: ";
	tree.in_order_traversal();//task 3 (part A)
	
	cout<<"\nPost-order traversal: ";
	tree.post_order_traversal();//task 3 (part A)
	
	cout<<"\n\nIterative:-"
		<<"\nPre-order traversal: ";
	tree.iterative_pre_order_traversal();//task 3 (part B)
	
	return 0;
}
