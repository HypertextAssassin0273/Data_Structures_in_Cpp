#include "BST.hpp"

void test_case_1(){
	BST<int> tree;
	
	tree.insert(8);
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);
	tree.insert(7);
	tree.insert(10);
	tree.insert(14);
	
	cout<<"\nInorder traversal: ";
	tree.in_order_traversal();
	
	cout<<"\nAfter deleting 10:";
	tree.remove(10);
	
	cout<<"\nInorder traversal: ";
	tree.in_order_traversal();
	
	cout<<"\nsize: "<<tree.size()<<endl;
	
	cout<<"found: "<<boolalpha<<tree.search(10);
}

void test_case_2(){
#if __cplusplus >= 201103L
	BST<int> tree={8,3,1,6,7,10,14};
#else
	BST<int> tree;
	tree.insert(8);
	tree.insert(3);
	tree.insert(1);
	tree.insert(6);
	tree.insert(7);
	tree.insert(10);
	tree.insert(14);
#endif
	
	/* max to min heap */
	cout<<"\nBST to max heap:-";
	tree.convert_BST_to_max_heap();
	cout<<"\npre-order traversal: ";
	tree.pre_order_traversal();
	cout<<"\nIn-order traversal: ";
	tree.in_order_traversal();
	cout<<"\nPost-order traversal: ";
	tree.post_order_traversal();
	
	cout<<"\n\nMax heap to min heap:-";
	tree.convert_max_heap_to_min_heap();
	cout<<"\npre-order traversal: ";
	tree.pre_order_traversal();
	cout<<"\nIn-order traversal: ";
	tree.in_order_traversal();
	cout<<"\nPost-order traversal: ";
	tree.post_order_traversal();
	
	/* min to max heap */
//	cout<<"\nBST to min heap:-";
//	tree.convert_BST_to_min_heap();
//	cout<<"\npre-order traversal: ";
//	tree.pre_order_traversal();
//	cout<<"\nIn-order traversal: ";
//	tree.in_order_traversal();
//	cout<<"\nPost-order traversal: ";
//	tree.post_order_traversal();
//	
//	cout<<"\n\nMin heap to max heap:-";
//	tree.convert_min_heap_to_max_heap();
//	cout<<"\npre-order traversal: ";
//	tree.pre_order_traversal();
//	cout<<"\nIn-order traversal: ";
//	tree.in_order_traversal();
//	cout<<"\nPost-order traversal: ";
//	tree.post_order_traversal();
}


int main(){
	test_case_1();//i.e. basic tree operations
//	test_case_2();//i.e. convert max-heap to min-heap or vice-versa (using BST) 
	return 0;
}
