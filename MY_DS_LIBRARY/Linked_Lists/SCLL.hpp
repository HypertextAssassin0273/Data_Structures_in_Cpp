#ifndef SCLL_GUARD
#define SCLL_GUARD 1

#include "Node.hpp"
#include "../Utilities/Swap.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class SCLL{//Singly Circular Linked-List
public:
	typedef SLL_Node<T> node;
	
private:
    node *tail;
	size_t _size;
	
public:
	SCLL()noexcept://default ctor
		tail(nullptr), _size(0){}
	
	SCLL(const SCLL &other)noexcept://copy ctor
		tail(nullptr), _size(0){
    	if(!other.tail) return;
		node *it=other.tail->next;
		do{
    		push_back(it->data);//1) copy other's data
    		it=it->next;
		}while(it!=other.tail->next);
    }
    SCLL& operator=(const SCLL &other)noexcept{//copy assignment func.
    	if(this==&other) return *this;//self-assignment protection
		clear();//1) clear existing resources
		if(!other.tail) return *this;
    	node *it=other.tail->next;
		do{
    		push_back(it->data);//2) copy other's data
    		it=it->next;
		}while(it!=other.tail->next);
    }
    
#if __cplusplus >= 201103L
 	SCLL(SCLL&& other)noexcept://move ctor (C++11 Construct)
  		tail(other.tail), _size(other._size){//1) steal other's data
		other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}
	SCLL& operator=(SCLL&& other)noexcept{//move assignment func (C++11 Construct)
  		if(this==&other) return *this;
		clear();//1) clear existing resources
  		tail=other.tail; _size=other._size;//2) steal other's data
  		other.tail=nullptr; other._size=0;//3) set 'other' to null state
		return *this;
	}
	
	template<typename _T, size_t N>
	SCLL(_T (&&init_list)[N])noexcept://move initializer_list ctor
		tail(nullptr), _size(0){
		for(auto& iter:init_list)//traversing array of r-value references through iterator
			push_back(std::move(iter));
	}
#endif

	/* Accessors & Mutators */
    T& operator[](size_t n){
		if(n==_size-1)
			return tail->data;
		node* it=tail->next;
		while(n--) it=it->next;
		return it->data;
	}
	
	T& front(){ return tail->next->data; }
	const T& front()const{ return tail->next->data; }
	
	T& back(){ return tail->data; }
	const T& back()const{ return tail->data; }
	
	size_t size()const{ return _size; }
	
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'empty()==false' for 'front' & 'back' accessors.
		2) use condition 'n<size()' for '[]' operator accessor.
	*/
	
    /* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//emplace_front
		push_front(new node(std::forward<_T>(new_data)...));//direct initialization is possible
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
#endif
	}
	void push_front(node* new_node){
		if(tail){
			new_node->next=tail->next;//Note: head == tail->next
			tail->next=new_node;
		}else{
			tail=new_node;
			tail->next=tail;
		}
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
	void push_back(node* new_node){
		if(tail){
			new_node->next=tail->next;
			tail=tail->next=new_node;
    	}else{
			tail=new_node;
    		tail->next=tail;
        }
        ++_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!tail) return;
    	if(tail->next==tail){
	        delete tail;
	        tail=nullptr;
    	}else{
    		node *temp=tail->next->next;
			delete tail->next;
    		tail->next=temp;
    	}
    	--_size;
	}
	
	void pop_back(){//Complexity: O(n)
		if(!tail) return;
    	if(tail->next==tail){
	        delete tail;
	        tail=nullptr;
    	}else{
			node* head=tail->next, *temp=head;
        	while(temp->next!=tail)
        		temp=temp->next;
        	delete tail;
        	tail=temp;
        	tail->next=head;//converting to circular again by joining link
		}
    	--_size;
    }

#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){//emplace_middle
		push_middle(new node(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){
		push_middle(new node(new_data));
#endif
	}
	void push_middle(node* new_node){
	    if(!tail||tail->next==tail){ push_back(new_node); return; }
    	node *slow_ptr=tail->next, *fast_ptr=tail->next->next;//tail->next==head
        while(fast_ptr!=tail->next&&fast_ptr->next!=tail->next){
            fast_ptr=fast_ptr->next->next;
           	slow_ptr=slow_ptr->next;
        }
		new_node->next=slow_ptr->next;
		slow_ptr->next=new_node;
	    ++_size;
	}
	void pop_middle(){
	    if(!tail) return;
    	if (tail->next==tail||tail->next->next==tail){ pop_back(); return; }
	    node *slow_ptr=tail->next, *fast_ptr=tail->next, *prev;
        do{
           	fast_ptr=fast_ptr->next->next;
           	prev=slow_ptr;
           	slow_ptr=slow_ptr->next;
    	}while(fast_ptr!=tail->next&&fast_ptr->next!=tail->next);
        prev->next=slow_ptr->next;
    	delete slow_ptr;
    	--_size;
	}
	
    void traverse()const{
    	if(!tail){
       		std::cout<<"List is empty!"<<'\n';
        	return;
    	}
		node *temp=tail->next;
    	do{
    		std::cout<<temp->data<<' ';
    		temp=temp->next;
		}while(temp!=tail->next);
		std::cout<<'\n';
	}
	
	void clear(){
		if(!tail) return;
		if(tail->next==tail) delete tail;
		else{
			node* temp, *head=tail->next;
			tail->next=nullptr;//converting into non-circular by breaking link
			while(head){
	   			temp=head->next;
	    		delete head;
    			head=temp;
			}
		}
		tail=nullptr;
		_size=0;
	}
	
	~SCLL(){ clear(); }//dtor
};

#endif
