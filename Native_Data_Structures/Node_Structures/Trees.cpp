#include"BST.hpp"
#include"BST_to_Heap_Convertor.hpp"
#include"AVL.hpp"

using std::cout;

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
	
	cout<<"\nsize: "<<tree.size()<<'\n';
	
	cout<<"found: "<<std::boolalpha<<tree.search(10);
}

#if __cplusplus >= 201103L
void test_case_2(){
	BST_to_Heap_Convertor<int> tree={8,3,1,6,7,10,14};
	
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
#endif

test_case_3(){
	#if __cplusplus >= 201103L
	AVL<int> tree{1,2,34,5,6,7,87,8,89,9,90,0,0,222,-2,-1,-1,5555,5555};
	#else
	AVL<int> tree;
	tree.insert(1);
	tree.insert(2);
	tree.insert(34);
	tree.insert(5);
	tree.insert(6);
	tree.insert(7);
	tree.insert(87);
	tree.insert(8);
	tree.insert(89);
	tree.insert(9);
	tree.insert(90);
	tree.insert(0);
	tree.insert(0);
	tree.insert(222);
	tree.insert(-2);
	tree.insert(-1);
	tree.insert(-1);
	tree.insert(5555);
	tree.insert(5555);
	#endif
	cout<<"\nInorder traversal: ";
	tree.in_order_traversal();
	
	cout<<"\nAfter removing -2:";
	tree.remove(-2);
	cout<<"\nInorder traversal: ";
	tree.in_order_traversal();
	
	cout<<"\nSize: "<<tree.size()<<'\n';

	cout<<"90 present: "<<std::boolalpha<<tree.search(90);
}

int main(){
//	test_case_1();//i.e. basic BST operations
//	test_case_2();//i.e. convert max-heap to min-heap or vice-versa (using BST,C++11)
	test_case_3();//i.e. basic AVL operations
	return 0;
}
