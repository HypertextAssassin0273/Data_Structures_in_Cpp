#include "BST.hpp"
using std::cout;

typedef BST<int>::node N;

int maxValue(N* node){
    if(!node) return INT16_MIN;
    return std::max(node->key, std::max(maxValue(node->left), maxValue(node->right)));
}
 
int minValue(N* node){
    if (!node) return INT16_MAX;
    return std::min(node->key, std::min(minValue(node->left), minValue(node->right)));
}

bool isBST(N* node){
    if(!node)
		return true;
    if(node->left&&maxValue(node->left)>node->key)
        return false;
    if(node->right&&minValue(node->right)<node->key)
        return false;
    if(!(isBST(node->left)&&isBST(node->right)))
        return false;
    return true;
}

int main(){
	N* t1=new N(11);
	t1->right=new N(22);
		
	BST<int> t{4, 5, 6, 8, 10, 11, 17, 19, 31, 43, 49};
	
	cout<<(isBST(t1)?"is BST":"isn't BST'")<<'\n';
	
	return 0;
}
