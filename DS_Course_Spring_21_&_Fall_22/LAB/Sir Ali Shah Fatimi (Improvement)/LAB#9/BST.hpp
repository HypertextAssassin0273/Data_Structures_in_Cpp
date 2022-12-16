#ifndef BST_GUARD
#define BST_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class BST{
public:
	struct node{
		T key;
		node *left, *right;
		
	#if __cplusplus >= 201103L
		template<typename _T>
    	node(_T&& key)noexcept:
			key(std::forward<_T>(key)), left(nullptr), right(nullptr){}
	#else
		node(const T& key)noexcept:
			key(key), left(nullptr), right(nullptr){}
	#endif
	};
	
protected:
	node *root;
	size_t _size;
	
public:	
	BST()noexcept://default ctor
		root(nullptr), _size(0){}
	
	BST(const BST &other)noexcept://copy ctor
		root(nullptr), _size(0){
		copy(other.root);
	}
	BST& operator=(const BST &other)noexcept{//copy assignment operator
		if(this==&other) return *this;//self-assignment protection
		clear();
  		copy(other.root);
  		return *this;
	}
	
#if __cplusplus >= 201103L
 	BST(BST&& other)noexcept://move ctor (C++11 Construct)
  		root(other.root), _size(other._size){
		other.root=nullptr; other._size=0;
	}
	BST& operator=(BST&& other)noexcept{//move assignment operator (C++11 Construct)
  		if(this==&other) return *this;
		clear();
  		root=other.root; _size=other._size;
  		other.root=nullptr; other._size=0;
		return *this;
	}
	
	template<typename _T, size_t N>
	BST(_T (&&list)[N])noexcept://move initializer_list based ctor
		root(nullptr), _size(0){
		for(auto& it:list)
        	insert(std::move(it));
	}
#endif
	
	size_t size()const{ return _size; }
	const node* get_root()const{ return root; }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void display_in_ordered_bf()const;//non-modifier declaration
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void iterative_pre_order_traversal()const;//non-modifier declaration
	void post_order_traversal()const{ post_order_traversal(root); }
	
	void insert(const T& key){ root=insert(key, root); }
	void remove(const T& key){ root=remove(key, root); }
	void remove(const int (&)[2]);//modifier declaration as overload
	bool search(const T& key){ return search(root, key); }
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	template<size_t N>
	void convert_sorted_array(const T (&)[N]);//modifier declaration
	
	~BST(){ clear(root); root=nullptr; }
	
private:
	void copy(node* current){//copies data in sorted order
		if (current){
			copy(current->left);
			insert(current->key);
			copy(current->right);
		}
	}
	
	void pre_order_traversal(node *current)const{
		if(current){
			std::cout<<current->key<<' ';
			pre_order_traversal(current->left);
			pre_order_traversal(current->right);
		}
	}
	void in_order_traversal(node *current)const{
		if(current){
			in_order_traversal(current->left);
			std::cout<<current->key<<' ';
			in_order_traversal(current->right);
		}
	}
	void display_in_ordered_bf(node*)const;//hidden non-modifier declaration
	void post_order_traversal(node *current)const{
		if(current){
			post_order_traversal(current->left);
			post_order_traversal(current->right);
			std::cout<<current->key<<' ';
		}
	}
	
	node* insert(const T& key, node* current){
		if (!current){ ++_size; return new node(key); }
		if (key<current->key)
			current->left=insert(key, current->left);
		else
			current->right=insert(key, current->right);
		return current;
	}
	
	node* min_value_node(node *current){//returns the inorder successor
		while(current&&current->left)//finds the left-most leaf
			current=current->left;
		return current;
	}
	node* remove(const T& key, node* current){
		if(!current) return nullptr;
		if(key<current->key)
			current->left=remove(key, current->left);
		else if(key>current->key)
			current->right=remove(key, current->right);
		else{//current node is same as key
			if(current->left&&current->right){//if node has both children, then replace itself with in-order successor
				node *temp=min_value_node(current->right);
				current->key=temp->key;//Note: here, data can only be copied (since move assignment isn't possible)
				current->right=remove(temp->key, current->right);
			}else{//else node is with only one child or no child
				node *temp=current->left?:current->right;
				--_size;
				if(temp){//one child case
				#if __cplusplus >= 201103L
					*current=std::move(*temp);//move-assignment of node
				#else
					*current=*temp;//copy-assignment of node
				#endif
					delete temp;
				}else{//no child case
					delete current;
					return nullptr;
				}
			}
		}
		return current;
	}
	node* remove(node*, const int (&)[2]);//hidden modifier declaration as overload
	
	node* convert_sorted_array(const T*, __int64, __int64);
	
	bool search(node* current,const T& key){
		if(!current) return false;
        if(key<current->key)
			return search(current->left, key);
		if(key>current->key)
			return search(current->right, key);
		return true;
	}
	
	void clear(node* current){
		if(!current) return;
		clear(current->left);
		clear(current->right);
		delete current;
	}
};

#endif
