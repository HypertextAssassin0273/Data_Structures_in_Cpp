#ifndef XOR_LIST_GUARD
#define XOR_LIST_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class xor_list{//xor doubly linked-list (memory efficient)
	typedef xor_list __XL;
public:
	struct node{
	    T data;
		node *xnode;//contains Xor of next node & previous node
		
	#if __cplusplus < 201103L
		node(const T& data=T())noexcept://default ctor
			data(data), xnode(nullptr){}
	#else
		template<typename... _T>
		node(_T&&... data)noexcept://variadic template & emplaced ctor
			data{std::forward<_T>(data)...},//perfect forwarding
			xnode(nullptr){}
	#endif
	};
	
	node* XOR(node* x,node* y)const{//returns xored value of the node addresses
		return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(x)^reinterpret_cast<uintptr_t>(y));
	}
	
private:	
	node *head, *tail;
	size_t _size;
	
public:
	xor_list()noexcept:
		head(nullptr), tail(nullptr), _size(0){}//default ctor
	
#if __cplusplus >= 201103L
	template<typename... _T>
	xor_list(size_t n, _T&&... new_data)noexcept:
		head(nullptr), tail(nullptr), _size(0){//emplaced fill ctor
			while(n>_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	xor_list(size_t n, const T& new_data=T())noexcept://fill ctor
		head(nullptr), tail(nullptr), _size(0){
			while(n>_size)
				push_back(new_data);
	}
#endif
	
	xor_list(const __XL &other)noexcept:
		head(nullptr),tail(nullptr),_size(0){//copy ctor
		node *curr=other.head, *next, *prev=nullptr;
		while(curr){
			push_back(curr->data);//1) copy other's data
			next=XOR(prev, curr->xnode);
			prev=curr;
			curr=next;
		}
	}
	__XL& operator=(const __XL &other)noexcept{//copy assignment operator
		if(this==&other) return *this;//self-assignment protection
		clear();//1) clear existing resources
		node *curr=other.head, *next, *prev=nullptr;
		while(curr){
			push_back(curr->data);//2) copy other's data
			next=XOR(prev ,curr->xnode);
			prev=curr;
			curr=next;
		}
		return *this;
	}
	
#if __cplusplus >= 201103L
	xor_list(__XL&& other)noexcept://move ctor
		head(other.head), tail(other.tail), _size(other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}
	__XL& operator=(__XL&& other)noexcept{//move assignment
		if(this==&other) return *this;
		clear();//1) clear existing resources
		head=other.head; tail=other.tail; _size=other._size;//2) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
		return *this;
	}
	
	template<typename _T, size_t N>
	xor_list(_T (&&init_list)[N])noexcept://move initializer_list ctor
		head(nullptr), tail(nullptr), _size(0){
		for(auto& iter:init_list)//traversing array of r-value references through iterator
			push_back(std::move(iter));
	}
#endif

	/* Accessors & Mutators */
	T& operator[](size_t n){
		if(n==_size-1)
			return tail->data;
		node *curr=head, *next, *prev=nullptr;
		while(n){
			next=XOR(prev, curr->xnode);
			prev=curr;
			curr=next;
			--n;
		}
		return curr->data;
	}
	
	T& front(){ return head->data; }
	const T& front()const{ return head->data; }
	
	T& back(){ return tail->data; }
	const T& back()const{ return tail->data; }
	
	size_t size()const{ return _size; }
	bool empty()const{ return !head; }
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//emplace_front, direct initialization is possible
		push_front(new node(std::forward<_T>(new_data)...));
#else
	void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
#endif
	}
	void push_front(node* new_node){
		new_node->xnode=head;
		if(head)
			head->xnode=XOR(new_node, head->xnode);//head->prev=new_node
		else
			tail=new_node;
		head=new_node;
		++_size;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//emplace_back
		push_back(new node(std::forward<_T>(new_data)...));
#else
	void push_back(const T& new_data){//Complexity: O(1)
		push_back(new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!tail)//anyone of them can be used to check
			head=tail=new_node;
		else{
			new_node->xnode=XOR(tail, new_node->xnode);//new_node->prev=tail
			tail->xnode=XOR(new_node, tail->xnode);//tail->next=new_node
			tail=new_node;
		}
		++_size;
	}
	
	//NOTE: change it to different overloads instead of flag
	node* pop_front(bool flag=false){//Complexity: O(1)
		if(!head) return nullptr;
		node* popped;
		if (!head->xnode){
			if(flag) popped=head; 
			else delete head;
			head=tail=nullptr;
		}else{
			node *temp=head->xnode, *next=XOR(head, head->xnode->xnode);//stores next of xored node
			if(flag){
				popped=head;
				popped->xnode=nullptr;
			}
			else delete head;
			head=temp;
			head->xnode=next;
		}
		--_size;
		return popped;
	}
	
	node* pop_back(bool flag=false){//Complexity: O(1)
		if(!tail) return nullptr;
		node* popped;
		if (!tail->xnode){
			if(flag) popped=tail; 
			else delete tail;
			head=tail=nullptr;
		}else{
			node *temp=tail->xnode, *prev=XOR(tail, tail->xnode->xnode);//stores prev of xored node
			if(flag){
				popped=tail;
				popped->xnode=nullptr;
			}
			else delete tail;
			tail=temp;
			tail->xnode=prev;
		}
		--_size;
		return popped;
	}
	
	void traverse_forward()const{
		if(!head){
			std::cout<<"List is empty!"<<'\n';
			return;
		}
		node *curr=head, *next, *prev=nullptr;
		while(curr){
			std::cout<<curr->data<<' ';
			next=XOR(prev, curr->xnode);
			prev=curr;
			curr=next;
		}
		std::cout<<'\n';
	}
	void traverse_backward()const{
		if(!tail){
			std::cout<<"List is empty!"<<'\n';
			return;
		}
		node *curr=tail, *next=nullptr, *prev;
		while(curr){
			std::cout<<curr->data<<' ';
			prev=XOR(next, curr->xnode);
			next=curr;
			curr=prev;
		}
		std::cout<<'\n';
	}
	
	void reverse(){//Complexity: O(1)
		if(_size>1) std::swap(head, tail);
	}
	
	void clear(){
		node *next, *temp=nullptr;
			while(head){
				next=XOR(head->xnode, temp);
	   			temp=head;
				delete head;
				head=next;	
			}
		tail=nullptr;
		_size=0;
	}
	
	~xor_list(){ clear(); }//dtor
};

#endif
