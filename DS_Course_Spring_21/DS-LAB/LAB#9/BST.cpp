#include<iostream>
using namespace std;

#ifndef BST_GUARD
#define BST_GUARD 1

#if !LIST_GUARD
#include "List.hpp"
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class BST{
	typedef unsigned int __uint32;
	
	struct node{
		T key;
		node *left,*right;
		
    	node(const T& key=T())noexcept:
			key(key),left(nullptr),right(nullptr){}
	};
	
	node *root;
	__uint32 _size;
	
public:
	BST()noexcept:
		root(nullptr),_size(0){}
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	BST(initializer_list<T> list)noexcept:root(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	insert(it);
	}
#endif
#if __cplusplus >= 201103L
 	BST(BST&& other)noexcept://i.e. move ctor (C++11 Construct)
  		root(other.root),_size(other._size){
		other.root=nullptr; other._size=0;
	}
	BST& operator=(BST&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)//i.e. self-assignment protection
			return *this;
		clear();
  		root=other.root; _size=other._size;
  		other.root=nullptr; other._size=0;
  		return *this;
	}
#endif	
	
	__uint32 size()const{ return _size; }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void post_order_traversal()const{ post_order_traversal(root); }
	
	void insert(const T& key){ root=insert(key,root); }
	void remove(const T& key){ remove(key,root); }
	bool search(const T& key){ return search(root,key); }
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	void convert_BST_to_max_heap()const{
    	List<T> queue;
    	in_order_transfer_to_queue(root,queue);
    	post_order_transfer_to_BST(root,queue);
	}
	void convert_BST_to_min_heap()const{
    	List<T> queue;
    	in_order_transfer_to_queue(root,queue);
    	pre_order_transfer_to_BST(root,queue);
	}
	void convert_min_heap_to_max_heap()const{
    	List<T> queue;
    	pre_order_transfer_to_queue(root,queue);
    	post_order_transfer_to_BST(root,queue);
	}
	void convert_max_heap_to_min_heap()const{
    	List<T> queue;
    	post_order_transfer_to_queue(root,queue);
    	pre_order_transfer_to_BST(root,queue);
	}
	
	~BST(){ clear(root); root=nullptr; }
	
private:
	BST(const BST &other)noexcept;//i.e. deleted copy ctor
    BST& operator=(const BST &other)noexcept;//i.e. deleted copy assignment func.
	
	void pre_order_traversal(node *current)const{
		if(current){
			cout<<current->key<<" ";
			pre_order_traversal(current->left);
			pre_order_traversal(current->right);
		}
	}
	void in_order_traversal(node *current)const{
		if (current){
			in_order_traversal(current->left);
			cout<<current->key<<" ";
			in_order_traversal(current->right);
		}
	}
	void post_order_traversal(node *current)const{
		if(current){
			post_order_traversal(current->left);
			post_order_traversal(current->right);
			cout<<current->key<<" ";
		}
	}
	node* insert(const T& key,node* current){
		if (!current){
			++_size;
			return new node(key);
		}
		if (key<current->key)
			current->left=insert(key,current->left);
		else
			current->right=insert(key,current->right);
		return current;
	}
	node* min_value_node(node *current){//i.e. returns the inorder successor
		while(current&&current->left)//i.e. finds the left-most leaf
			current=current->left;
		return current;
	}
	node* remove(const T& key,node* current){
		if (!current)
			return current;
		if (key<current->key)
			current->left=remove(key,current->left);
		else if(key>current->key)
			current->right=remove(key,current->right);
		else{//i.e. if the node is with only one child or no child
			if (!current->left){
				node *temp=current->right;
				delete current;
				--_size;
				return temp;
			}
			else if(!current->right){
				node *temp=current->left;
				delete current;
				--_size;
				return temp;
			}
			/*Note: If the node has two children, place the in-order successor in position
					of the node to be deleted & delete the in-order successor */
			node *temp=min_value_node(current->right);
			current->key=temp->key;
			current->right=remove(temp->key,current->right);
		}
		return current;
	}
	bool search(node* current,const T& key){
        if(!current)
            return false;
        if(key<current->key)
        	return search(current->left,key);
        if(key>current->key)
            return search(current->right,key);
        return true;
    }
    void clear(node* current){
        if(!current)
            return;
        clear(current->left);
        clear(current->right);
        delete current;
	}
	
	void pre_order_transfer_to_queue(node *current,List<T>& queue)const{
		if (current){
		#if __cplusplus >= 201103L
			queue.push_back(move(current->key));
		#else
			queue.push_back(current->key);
		#endif
			pre_order_transfer_to_queue(current->left,queue);
			pre_order_transfer_to_queue(current->right,queue);
		}
	}
	void in_order_transfer_to_queue(node *current,List<T>& queue)const{
		if (current){
			in_order_transfer_to_queue(current->left,queue);
		#if __cplusplus >= 201103L
			queue.push_back(move(current->key));
		#else
			queue.push_back(current->key);
		#endif
			in_order_transfer_to_queue(current->right,queue);
		}
	}
	void post_order_transfer_to_queue(node *current,List<T>& queue)const{
		if (current){
			post_order_transfer_to_queue(current->left,queue);
			post_order_transfer_to_queue(current->right,queue);
		#if __cplusplus >= 201103L
			queue.push_back(move(current->key));
		#else
			queue.push_back(current->key);
		#endif
		}
	}
	
	void pre_order_transfer_to_BST(node *current,List<T>& queue)const{
    	if (current){
		#if __cplusplus >= 201103L
  	  	current->key=move(queue.front());
		#else
 			current->key=queue.front();
		#endif
	 		queue.pop_front();
    		pre_order_transfer_to_BST(current->left,queue);
    		pre_order_transfer_to_BST(current->right,queue);
    	}
	}
	void post_order_transfer_to_BST(node *current,List<T>& queue)const{
    	if (current){
			post_order_transfer_to_BST(current->left,queue);
			post_order_transfer_to_BST(current->right,queue);
		#if __cplusplus >= 201103L
			current->key=move(queue.front());
		#else
 			current->key=queue.front();
		#endif
		 	queue.pop_front();
		}
	}
};
#endif


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
