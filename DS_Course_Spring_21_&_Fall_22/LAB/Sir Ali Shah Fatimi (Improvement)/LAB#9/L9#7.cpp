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

N* get_tree(){
	N* root=new N(4);
	root->left=new N(2);
	root->right=new N(5);
//	root->right->left=new N(7);//1
	root->left->left=new N(1);
	root->left->right=new N(3);
//	root->left->left->left=new N(-1);//2
	return root;
}

/*Notes:-
1) if 1 & 2 both are commented, then its:
	both AVL & BST
2) if only 1 is commented, then its:
	NOT AVL but BST
3) if only 2 is commented or non of them, then its:
	Neither BST nor AVL
*/

int main(){	
	N* root=get_tree(); __int64 bf;
	
	cout<<(isBST(root)?
			((bf=balance_factor(root))==-1||bf==0||bf==1)?
				"both AVL and BST":"NOT AVL but BST":"Neither BST nor AVL");
	
	return 0;
}
