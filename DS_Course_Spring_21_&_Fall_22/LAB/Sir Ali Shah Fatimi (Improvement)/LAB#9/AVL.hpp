#ifndef AVL_GUARD
#define AVL_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class AVL{
protected:
	struct node{
		T data;
		__int64 height, count;
		node *left, *right;
		
	#if __cplusplus >= 201103L
		template<typename _T>
    	node(_T&& data)noexcept:
			data(std::forward<_T>(data)), height(1), count(1), left(nullptr), right(nullptr){}
	#else
		node(const T& data)noexcept:
			data(data), height(1), count(1), left(nullptr), right(nullptr){}
	#endif
	};
	
	node *root;
	__int64 _size;
	
public:
	AVL()noexcept://default ctor
		root(nullptr), _size(0){}
	
	AVL(const AVL &other)noexcept://copy ctor
		root(nullptr), _size(0){
		copy(other.root);
	}
	AVL& operator=(const AVL &other)noexcept{//copy assignment operator
		if(this!=&other){//self-assignment protection
			clear();
  			copy(other.root);
  		}
		return *this;
	}
#if __cplusplus >= 201103L
 	AVL(AVL&& other)noexcept://move ctor
  		root(other.root), _size(other._size){
		other.root=nullptr; other._size=0;
	}
	AVL& operator=(AVL&& other)noexcept{//move assignment operator
  		if(this!=&other){
			clear();
  			root=other.root; _size=other._size;
  			other.root=nullptr; other._size=0;
  		}
		return *this;
	}
	AVL(std::initializer_list<T> list)noexcept://initializer_list based ctor
		root(nullptr),_size(0){
		for(const auto& it:list)//traversing list through iterator
        	insert(it);
	}
#endif
	
	__int64 size()const{ return _size; }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void post_order_traversal()const{ post_order_traversal(root); }
	
#if __cplusplus >= 201103L
	template<typename _T>
	void insert(_T&& key){ root=insert(std::forward<_T>(key),root); }//_T&& -> universal reference
#else
	void insert(const T& key){ root=insert(key,root); }
#endif
	void remove(const T& key){ root=remove(key,root); }
	bool search(const T& key)const{ return search(key,root); }
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	~AVL(){ clear(root); }
	
protected:
	__int64 max(__int64 a, __int64 b)const{ return (a>b)?a:b; }
	__int64 height(node *current)const{ return current?current->height:0; }
	__int64 balance_factor(node *current)const{ return current?height(current->left)-height(current->right):0; }
	
	node* right_rotate(node *y){
  		node *x=y->left,*T2=x->right;
  		x->right=y; y->left=T2;//perform rotation
  		/* update heights */
  		y->height=max(height(y->left),height(y->right))+1;
  		x->height=max(height(x->left),height(x->right))+1;
  		return x;
	}
	node* left_rotate(node *x){
  		node *y=x->right,*T2=y->left;
  		y->left=x; x->right=T2;
 		x->height=max(height(x->left),height(x->right))+1;
		y->height=max(height(y->left),height(y->right))+1;
  		return y;
	}
	void copy(node* current){//copies data in sorted order
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
#if __cplusplus >= 201103L	
	template<typename _T>
	node* insert(_T&& key, node* current){
		if(!current){
			++_size;
			return new node(std::forward<_T>(key));
		}
#else
	node* insert(const T& key, node* current){
		if(!current){
			++_size;
			return new node(key);
		}
#endif
		if(key==current->data){
        	++(current->count);
        	return current;
    	}
		if(key<current->data)
			current->left=insert(key,current->left);
		else
			current->right=insert(key,current->right);
		current->height=max(height(current->left),height(current->right))+1;
  		/* balancing the tree by updating balance_factor of each node */
		__int64 bf=balance_factor(current);
  		if(bf>1)
    		if(key<current->left->data)//left left case
      			return right_rotate(current);
    		else if(key>current->left->data){//left right case
      			current->left=left_rotate(current->left);
      			return right_rotate(current);
    		}
  		if(bf<-1)
    		if(key>current->right->data)//right right case
      			return left_rotate(current);
    		else if(key<current->right->data){//right left case
    			current->right=right_rotate(current->right);
      			return left_rotate(current);
    		}
		return current;
	}
	node* min_value_node(node *current){//returns the inorder successor
		if(current)
			while(current->left)//finds the left-most leaf
				current=current->left;
		return current;
	}
	node* remove(const T& key, node* current){
		if(!current)
			return current;
		if(key<current->data)
			current->left=remove(key,current->left);
		else if(key>current->data)
			current->right=remove(key,current->right);
		else{//current node is same as key
			if(current->count>1){
				--(current->count);
				return current;
			}
			if(!current->left||!current->right){//if the node is with only one child or no child
				node *temp=current->left?current->left:current->right;
				if(!temp){//no child case
					temp=current;
					current=nullptr;
				}
				else//one child case
				#if __cplusplus >= 201103L
					*current=std::move(*temp);//move-assignment of node
				#else
					*current=*temp;//copy-assignment of node
				#endif
				--_size;
				delete temp;
			}
			else{/*Note: If the node has two children, it places the in-order successor in position
						 of the node to be deleted & deletes the in-order successor */
				node *temp=min_value_node(current->right);
				current->data=temp->data;//data of min_value_node can't be moved, only copy assignment is possible
				current->count=temp->count;
				temp->count=1;//so we don't remove duplicates again
				current->right=remove(temp->data,current->right);
			}
		}
		if(!current)
			return current;
		current->height=max(height(current->left),height(current->right))+1;
		/* balancing the tree by updating balance_factor of each node */
  		__int64 bf=balance_factor(current);
  		if(bf>1)
    		if(balance_factor(current->left)>-1)
      			return right_rotate(current);
    		else{
      			current->left=left_rotate(current->left);
      			return right_rotate(current);
    		}
  		if(bf<-1)
    		if(balance_factor(current->left)<1)
      			return left_rotate(current);
    		else{
    			current->right=right_rotate(current->right);
      			return left_rotate(current);
    		}
		return current;		
	}
	bool search(const T& key, node* current)const{
		if(!current)
			return false;
        if(key<current->data)
			return search(key,current->left);
		if(key>current->data)
			return search(key,current->right);
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
