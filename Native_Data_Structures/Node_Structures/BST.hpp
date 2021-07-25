#ifndef BST_GUARD
#define BST_GUARD 1

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class BST{
protected:
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
	BST(initializer_list<T> list)noexcept:
		root(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	insert(it);
	}
#endif
	BST(const BST &other)noexcept://i.e. copy ctor
		root(nullptr),_size(0){
		copy(other.root);
	}
	BST& operator=(const BST &other)noexcept{//i.e. copy assignment func.
		if(this==&other)//i.e. self-assignment protection
			return *this;
		clear();
  		copy(other.root);
  		return *this;
	}
#if __cplusplus >= 201103L
 	BST(BST&& other)noexcept://i.e. move ctor (C++11 Construct)
  		root(other.root),_size(other._size){
		other.root=nullptr; other._size=0;
	}
	BST& operator=(BST&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
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
	
	~BST(){ clear(root); root=nullptr; }
	
private:
	void copy(node* current){//i.e. copies data in sorted order
		if (current){
			copy(current->left);
			insert(current->key);
			copy(current->right);
		}
	}
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
};

#endif
