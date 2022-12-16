#include "BST.hpp"
using std::cout;

template<typename T>
int maxValue(T* node){
    return node? std::max(node->key, std::max(maxValue(node->left), maxValue(node->right))): INT16_MIN;
}
template<typename T>
int minValue(T* node){
    return node? std::min(node->key, std::min(minValue(node->left), minValue(node->right))): INT16_MAX;
}
template<typename T>
bool isBST(T* node){
    return !( node &&
    	   	 ( node->left&&maxValue(node->left)>node->key || node->right&&minValue(node->right)<node->key ||
	   	   	  !( isBST(node->left)&&isBST(node->right) ) ) );
}

typedef BST<int>::node N;

void test_case_1(N** root){
	*root=new N(4);
	(*root)->left=new N(2);
	(*root)->right=new N(5);
//	(*root)->right->left=new N(7);//makes it non-bst tree
	(*root)->left->left=new N(1);
	(*root)->left->right=new N(3);
}

void test_case_2(N** root){
	*root=new N(5);
	(*root)->left=new N(2);
	(*root)->right=new N(3);
	(*root)->left->left=new N(1);
	(*root)->right->right=new N(7);
}

int main(){
	N* root=nullptr;
	
	test_case_1(&root);//bst tree
//	test_case_2(&root);//non-bst tree
	
	cout<<(isBST(root)?"is BST (10 points)":"isn't BST (0 points)");//acts as auto grader
	
	return 0;
}
