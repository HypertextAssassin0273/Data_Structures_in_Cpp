#include "BST.hpp"
using std::cout;

template<typename T>
__int64 height(T *current){
	return current?std::max(height(current->left), height(current->right))+1:0;
}
template<typename T>
__int64 balance_factor(T *current){
	return current?height(current->left)-height(current->right):0;
}

template<typename T>
void BST<T>::display_in_ordered_bf(node *current)const{
	if(current){
		display_in_ordered_bf(current->left);
		std::cout<<current->key<<":\t"<<balance_factor(current)<<'\n';
		display_in_ordered_bf(current->right);
	}
}
template<typename T>
void BST<T>::display_in_ordered_bf()const{
	std::cout<<"key: balance_factor\n";
	display_in_ordered_bf(root);
}

int main(){
#if __cplusplus >= 201103L
	BST<int> tree({5,10,2,4,9,11,12,13});
#else
	BST<int> tree;
	
	int arr[]={5,10,2,4,9,11,12,13},
		N=sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0;i<N;++i)
		tree.insert(arr[i]);
#endif
	
	cout<<"balance factors of each node (In-order traversal):-\n";
	tree.display_in_ordered_bf();
	
	return 0;
}
