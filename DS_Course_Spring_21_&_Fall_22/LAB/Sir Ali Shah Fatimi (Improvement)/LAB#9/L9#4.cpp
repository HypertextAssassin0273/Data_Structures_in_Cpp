#include "BST.hpp"
using std::cout;

template<>//specialized for int datatype only
BST<int>::node* BST<int>::remove(node *current, const int (&range)[2]){
	if(!current) return nullptr;
	current->left=remove(current->left, range);
	current->right=remove(current->right, range);
	if(current->key<range[0]){//min case
		node *rChild=current->right;
		delete current;
		return rChild;
	}
	if(current->key>range[1]){//max case
		node *lChild=current->left;
		delete current;
		return lChild;
	}
	return current;
}
template<>//specialized for int datatype only
void BST<int>::remove(const int (&range)[2]){//task 4
	root=remove(root, range);
}

int main(){
#if __cplusplus >= 201103L
	BST<int> tree({15,10,20,8,12,18,25});
#else
	BST<int> tree;
	
	int arr[]={15,10,20,8,12,18,25},
		N=sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0;i<N;++i)
		tree.insert(arr[i]);
#endif
	
	cout<<"In-order traversal:-\n"
		<<"Before: ";
	tree.in_order_traversal();
	
#if __cplusplus >= 201103L
	tree.remove({9, 12});
#else
	int range[]={9, 12};
	tree.remove(range);//no concept of direct use of r-values in C++03
#endif
	
	cout<<"\nAfter: ";
	tree.in_order_traversal();
	
	return 0;
}
