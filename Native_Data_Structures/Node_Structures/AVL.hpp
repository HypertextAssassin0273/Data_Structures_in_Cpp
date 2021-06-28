#ifndef AVL_GUARD
#define AVL_GUARD 1

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class AVL{
protected:
	struct node{
		T key;
		__int64 height,count;
		node *left,*right;
		
    	node(const T& key)noexcept:
			key(key),height(1),count(1),left(nullptr),right(nullptr){}
	};
	
	node *root;
	__int64 _size;
	
public:
	AVL()noexcept:
		root(nullptr),_size(0){}
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	AVL(initializer_list<T> list)noexcept:
		root(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	insert(it);
	}
#endif
	AVL(const AVL &other)noexcept://i.e. copy ctor
		root(nullptr),_size(0){
		copy(other.root);
	}
	AVL& operator=(const AVL &other)noexcept{//i.e. copy assignment func.
		if(this==&other)//i.e. self-assignment protection
			return *this;
		clear();
  		copy(other.root);
  		return *this;
	}
#if __cplusplus >= 201103L
 	AVL(AVL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		root(other.root),_size(other._size){
		other.root=nullptr; other._size=0;
	}
	AVL& operator=(AVL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();
  		root=other.root; _size=other._size;
  		other.root=nullptr; other._size=0;
  		return *this;
	}
#endif	
	
	__int64 size()const{ return _size; }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void post_order_traversal()const{ post_order_traversal(root); }
	
	void insert(const T& key){ root=insert(key,root); }
	void remove(const T& key){ root=remove(key,root); }
	bool search(const T& key){ return search(root,key); }
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	~AVL(){ clear(root); }
	
private:
	__int64 max(__int64 a,__int64 b)const{ return (a>b)?a:b; }
	__int64 height(node *current)const{ return current?current->height:0; }
	__int64 balance_factor(node *current)const{ return current?height(current->left)-height(current->right):0; }
	
	node* right_rotate(node *y){
  		node *x=y->left,*T2=x->right;
  		x->right=y; y->left=T2;//i.e. perform rotation
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
	void copy(node* current){//i.e. copies data in sorted order
		if (current){
			copy(current->left);
			insert(current->key);
			copy(current->right);
		}
	}
	void pre_order_traversal(node *current)const{
		if(current){
			cout<<current->key<<'('<<current->count<<") ";
			pre_order_traversal(current->left);
			pre_order_traversal(current->right);
		}
	}
	void in_order_traversal(node *current)const{
		if (current){
			in_order_traversal(current->left);
			cout<<current->key<<'('<<current->count<<") ";
			in_order_traversal(current->right);
		}
	}
	void post_order_traversal(node *current)const{
		if(current){
			post_order_traversal(current->left);
			post_order_traversal(current->right);
			cout<<current->key<<'('<<current->count<<") ";
		}
	}
	node* insert(const T& key,node* current){
		if (!current){
			++_size;
			return new node(key);
		}
		if (key==current->key){
        	++(current->count);
        	return current;
    	}
		if (key<current->key)
			current->left=insert(key,current->left);
		else
			current->right=insert(key,current->right);
		current->height=max(height(current->left),height(current->right))+1;
  		/*i.e. balancing the tree by updating balance_factor of each node */
		__int64 bf=balance_factor(current);
  		if (bf>1)
    		if (key<current->left->key)//i.e. left left case
      			return right_rotate(current);
    		else if(key>current->left->key){//i.e. left right case
      			current->left=left_rotate(current->left);
      			return right_rotate(current);
    		}
  		if (bf<-1)
    		if (key>current->right->key)//i.e. right right case
      			return left_rotate(current);
    		else if (key<current->right->key){//i.e. right left case
    			current->right=right_rotate(current->right);
      			return left_rotate(current);
    		}
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
		else{//i.e. current node is same as key
			if(current->count>1){
				--(current->count);
				return current;
			}
			if (!current->left||!current->right){//i.e. if the node is with only one child or no child
				node *temp=current->left?current->left:current->right;
				if(!temp){//i.e. no child case
					temp=current;
					current=nullptr;
				}
				else//i.e. one child case
				#if __cplusplus >= 201103L
					*current=move(*temp);
				#else
					*current=*temp;
				#endif
				--_size;
				delete temp;
			}
			else{/*Note: If the node has two children, it places the in-order successor in position
						 of the node to be deleted & deletes the in-order successor */
				node *temp=min_value_node(current->right);
				current->key=temp->key;
				current->count=temp->count;
				temp->count=1;
				current->right=remove(temp->key,current->right);
			}
		}
		if(!current)
			return current;
		current->height=max(height(current->left),height(current->right))+1;
		/*i.e. balancing the tree by updating balance_factor of each node */
  		__int64 bf=balance_factor(current);
  		if (bf>1)
    		if (balance_factor(current->left)>-1)
      			return right_rotate(current);
    		else{
      			current->left=left_rotate(current->left);
      			return right_rotate(current);
    		}
  		if (bf<-1)
    		if (balance_factor(current->left)<1)
      			return left_rotate(current);
    		else{
    			current->right=right_rotate(current->right);
      			return left_rotate(current);
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
