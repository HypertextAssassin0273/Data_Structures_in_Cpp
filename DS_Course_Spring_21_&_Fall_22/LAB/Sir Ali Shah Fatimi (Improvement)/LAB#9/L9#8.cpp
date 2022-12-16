#include "BST.hpp"
using std::cout;

template<typename T>
typename BST<T>::node* BST<T>::convert_sorted_array(const T* arr, __int64 s, __int64 e){
	if(s>e) return nullptr;
	__int64 mid=(s+e)/2;
	node* current=new node(arr[mid]);
	current->left=convert_sorted_array(arr, s, mid-1);
	current->right=convert_sorted_array(arr, mid+1, e);
	return current;
}

template<typename T>
template<size_t N>
void BST<T>::convert_sorted_array(const T (&arr)[N]){
	clear();
	root=convert_sorted_array(arr, 0, N-1);
}

int main(){
	BST<int> tree;
	tree.convert_sorted_array({1,2,3,4,5,6,7,8,9,10});
	tree.post_order_traversal();
	
	return 0;
}
