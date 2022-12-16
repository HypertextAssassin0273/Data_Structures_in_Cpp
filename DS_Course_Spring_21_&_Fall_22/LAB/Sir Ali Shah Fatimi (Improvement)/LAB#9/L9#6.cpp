#include "AVL.hpp"
using std::cout;

template<typename T>
void AVL<T>::display_in_ordered_bf(node *current)const{
	if(current){
		display_in_ordered_bf(current->left);
		std::cout<<current->data<<":\t"<<balance_factor(current)<<'\n';
		display_in_ordered_bf(current->right);
	}
}
template<typename T>
void AVL<T>::display_in_ordered_bf()const{
	std::cout<<"key: balance_factor\n";
	display_in_ordered_bf(root);
}

int main(){
#if __cplusplus >= 201103L
	AVL<int> tree({5,10,2,4,9,11,12,13});
#else
	AVL<int> tree;
	
	int arr[]={5,10,2,4,9,11,12,13},
		N=sizeof(arr)/sizeof(arr[0]);
	
	for(int i=0;i<N;++i)
		tree.insert(arr[i]);
#endif
	
	cout<<"balance factors of each node (In-order traversal):-\n";
	tree.display_in_ordered_bf();
	
	return 0;
}
