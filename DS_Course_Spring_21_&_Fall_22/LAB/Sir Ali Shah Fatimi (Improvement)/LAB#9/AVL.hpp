#ifndef AVL_GUARD
#define AVL_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class AVL{
public:
	struct node{
		T data;
		__int64 height, count;
		node *left, *right;
		
	#if __cplusplus >= 201103L
		template<typename _T>
    	node(_T&& data)noexcept://_T&& -> universal reference
			data(std::forward<_T>(data)), height(1), count(1), left(nullptr), right(nullptr){}
	#else
		node(const T& data)noexcept://default ctor
			data(data), height(1), count(1), left(nullptr), right(nullptr){}
	#endif
	};
	
protected:
	/* Main-Class Attributes */
	node *root;
	size_t _size;
	
public:
	/* Constructors & Assignment Operators */
	AVL()noexcept://default ctor
		root(nullptr), _size(0){}
	
	AVL(const AVL &other)noexcept://copy ctor
		root(nullptr), _size(0){
		copy(other.root);
	}
	AVL& operator=(const AVL &other)noexcept{//copy assignment operator
		if(this==&other) return *this;//self-assignment protection
		clear();
  		copy(other.root);
		return *this;
	}
#if __cplusplus >= 201103L
 	AVL(AVL&& other)noexcept://move ctor
  		root(other.root), _size(other._size){
		other.root=nullptr; other._size=0;
	}
	AVL& operator=(AVL&& other)noexcept{//move assignment operator
  		if(this==&other) return *this;
		clear();
  		root=other.root; _size=other._size;
  		other.root=nullptr; other._size=0;
		return *this;
	}
	
	template<typename _T, size_t N>
	AVL(_T (&&list)[N])noexcept://move initializer_list based ctor
		root(nullptr), _size(0){
		for(auto& it:list)//traversing list through iterator
        	insert(std::move(it));
	}
#endif
	
	/* Accessor */
	size_t size()const{ return _size; }
	
	const node* get_root()const{ return root; }
	
	/* Modifiers */
#if __cplusplus >= 201103L
	void insert(T&& key){ root=insert(&key, root); }//r-value version (shallow copy)
	void insert(T& key){ root=insert(key, root); }//l-value version (deep copy)
#else
	void insert(const T& key){ root=insert(key, root); }
#endif
	
	void remove(const T& key){ root=remove(key, root); }
	
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	/* Non-Modifiers */
	bool search(const T& key)const{ return search(key, root); }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void post_order_traversal()const{ post_order_traversal(root); }
	
	void display_in_ordered_bf()const;//declaration
	
	/* Destructor (a.k.a. dtor) */
	~AVL(){ clear(root); }
	
protected:
	/* Hidden Methods */
#if __cplusplus >= 201103L
	node* insert(T* key, node* current){
		if(!current){
			node* new_node=new node(std::move(*key)); 
			key=&new_node->data;//updating ptr for new memory location
			++_size;
			return new_node;
		}
		if(*key==current->data){ ++(current->count); return current; }
		if(*key<current->data)
			current->left=insert(key, current->left);
		else
			current->right=insert(key, current->right);
		current->height=calc_height(current);//height must be updated before balancing tree
  		return balance_tree(*key, current);//each node needs to be checked for keeping the tree balanced
	}
#endif
	node* insert(const T& key, node* current){
		if(!current){ ++_size; return new node(key); }
		if(key==current->data){ ++(current->count); return current; }
		if(key<current->data)
			current->left=insert(key, current->left);
		else
			current->right=insert(key, current->right);
		current->height=calc_height(current);
  		return balance_tree(key, current);
	}
	
	node* remove(const T& key, node* current){
		if(!current) return nullptr;
		if(key<current->data)
			current->left=remove(key, current->left);
		else if(key>current->data)
			current->right=remove(key, current->right);
		else{//current node is same as key
			if(current->count>1){ --(current->count); return current; }
			if(current->left&&current->right){//if node has both children, then replace itself with in-order successor
				node *temp=min_value_node(current->right);
				current->data=temp->data;//Note: here, data can only be copied (since move assignment isn't possible)
				current->count=temp->count;
				temp->count=1;//resetting count, so we can delete the in-order successor node
				current->right=remove(current->data, current->right);//removes the in-order successor
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
		current->height=calc_height(current);//updating height
		return balance_tree(current);//since key's respective node is removed, we need to rely on this version
	}
	
	bool search(const T& key, node* current)const{
		return current?
				key<current->data?
					search(key, current->left):
				key>current->data?
					search(key, current->right):
				true:false;
	}
	
	void clear(node* current){//destroys data in post-order manner
		if(current){
			clear(current->left);
			clear(current->right);
			delete current;
		}
	}
	
	void copy(node* current){//copies data in in-order (sorted) manner
		if (current){
			copy(current->left);
			insert(current->data);
			copy(current->right);
		}
	}
	
	void pre_order_traversal(node *current)const{
		if(current){
			std::cout<<current->data<<'('<<current->count<<") ";
			pre_order_traversal(current->left);
			pre_order_traversal(current->right);
		}
	}
	void in_order_traversal(node *current)const{
		if(current){
			in_order_traversal(current->left);
			std::cout<<current->data<<'('<<current->count<<") ";
			in_order_traversal(current->right);
		}
	}
	void post_order_traversal(node *current)const{
		if(current){
			post_order_traversal(current->left);
			post_order_traversal(current->right);
			std::cout<<current->data<<'('<<current->count<<") ";
		}
	}
	
	void display_in_ordered_bf(node*)const;//hidden declaration
	
	/* Helper Methods (for simplifying code) */
	__int64 get_height(node *current)const{ return current?current->height:0; }
	
	__int64 balance_factor(node *current)const{ return current?get_height(current->left)-get_height(current->right):0; }
	
	static __int64 max(__int64 a, __int64 b){ return a>b?a:b; }//alternate: std::max
	
	__int64 calc_height(node *current)const{ return max(get_height(current->left), get_height(current->right))+1; }
	
	node* right_rotate(node *y){
  		node *x=y->left, *temp=x->right;
  		x->right=y; y->left=temp;
  		x->height=calc_height(x);//update height
  		y->height=calc_height(y);
  		return x;
	}
	node* left_rotate(node *x){
  		node *y=x->right, *temp=y->left;
  		y->left=x; x->right=temp;
  		x->height=calc_height(x);
  		y->height=calc_height(y);
  		return y;
	}
	
	node* balance_tree(node* current){//checks & update balance factor for current node
		__int64 bf=balance_factor(current);
  		if(bf>1){
    		if(balance_factor(current->left)<0)//left right case
      			current->left=left_rotate(current->left);
      		return right_rotate(current);//otherwise, its left-left-case
    	}
    	if(bf<-1){
    		if(balance_factor(current->right)>0)//right left case
    			current->right=right_rotate(current->right);
      		return left_rotate(current);//otherwise, its right-right-case
    	}
    	return current;
	}
	node* balance_tree(const T& key, node* current){//efficient overloaded version
		__int64 bf=balance_factor(current);
  		if(bf>1){
    		if(key>current->left->data)//left right case
      			current->left=left_rotate(current->left);
      		return right_rotate(current);//otherwise, its left-left-case
    	}
    	if(bf<-1){
    		if(key<current->right->data)//right left case
    			current->right=right_rotate(current->right);
      		return left_rotate(current);//otherwise, its right-right-case
    	}
		return current;
	}//Note: use this version when key is available
	
	node* min_value_node(node *current){//returns the in-order successor
		if(current)
			while(current->left)//finds the left-most leaf
				current=current->left;
		return current;
	}
};

#endif
