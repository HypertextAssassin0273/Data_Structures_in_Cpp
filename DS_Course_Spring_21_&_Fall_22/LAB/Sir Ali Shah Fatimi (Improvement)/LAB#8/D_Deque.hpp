#ifndef D_DEQUE_GUARD
#define D_DEQUE_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif
	
template<typename T>
class D_Deque{//Dynamic Deque (i.e. Doubly Linked-List Double ended Queue for both FIFO & LILO orders)
typedef D_Deque __DD;
public:
	struct node{
	    T data;
    	node *next, *prev;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://default ctor
			data(data), next(nullptr), prev(nullptr){}
    #else
		template<typename... _T>
		node(_T&&... data)noexcept://variadic template & emplaced ctor
			data{std::forward<_T>(data)...},//perfect forwarding
			next(nullptr), prev(nullptr){}
	#endif
	};
private:
	/* Class Attributes */
	static const unsigned int max_capacity=~((unsigned int)0);
    node *head, *tail;
	size_t _size;

public:
	/* Constructors */
#if __cplusplus >= 201103L
	template<typename... _T>
	D_Deque(const size_t& n=0, _T&&... new_data)noexcept://default & emplaced fill ctor
		head(nullptr), tail(nullptr), _size(0){
		if(n<=max_capacity)
			while(n>_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	D_Deque(const size_t& n=0, const T& new_data=T())noexcept://default & fill ctor
		head(nullptr), tail(nullptr), _size(0){
		if(n<=max_capacity)
			while(n>_size)
				push_back(new_data);
	}
#endif
	D_Deque(const __DD &other)noexcept://copy ctor
		head(nullptr), tail(nullptr), _size(0){
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    __DD& operator=(const __DD &other)noexcept{//copy assignment operator
    	if(this!=&other){//self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
        }
        return *this;
    }
#if __cplusplus >= 201103L
 	D_Deque(__DD&& other)noexcept://move ctor
 		head(other.head), tail(other.tail), _size(other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}
	__DD& operator=(__DD&& other)noexcept{//move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			head=other.head; tail=other.tail; _size=other._size;//2) steal other's data
  			other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
  		}
		return *this;
	}
	
	template<typename _T, size_t N>
	D_Deque(_T (&&list)[N])noexcept://move/r-value initializer_list based ctor
		head(nullptr), tail(nullptr), _size(0){
		for(const auto& it:list)//traversing list through iterator
        	push_back(it);
	}
#endif
	
	/* Accessors & Mutators */
public:
#if __cplusplus >= 201103L
	template<typename... _T>
	node* new_node(_T&&... new_data)const{ return new node(std::forward<_T>(new_data)...); }
#else
	node* new_node(const T& new_data)const{ return new node(new_data); }
#endif
	
    T& operator[](const size_t& n){
		if(n==_size-1)
			return tail->data;
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& at(const size_t& n){
		if (n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		if(n==_size-1)
			return tail->data;
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	
	T& front()const{ return head->data; }
	T& back()const{ return tail->data; }
	
	node* front_node()const{ return head; }
	node* back_node()const{ return tail; }
	
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
		new_node->next=head;
		if(head)
			head->prev=new_node;
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
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
        }
        ++_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!head) return;
    	if (!head->next){
			delete head;
	        head=tail=nullptr;
    	}
    	else{
    		node *temp=head->next;
			delete head;
    		head=temp;
    		head->prev=nullptr;
    	}
    	--_size;
	}
	node* pop_front(bool){
    	if(!head) return nullptr;
    	node* popped=nullptr;
    	if (!head->next){
			popped=head; 
	        head=tail=nullptr;
    	}
    	else{
    		node *temp=head->next;
   			popped=head;
			popped->next=nullptr;
    		head=temp;
    		head->prev=nullptr;
    	}
    	--_size;
    	return popped;
	}
	
	void pop_back(){//Complexity: O(1)
		if(!tail) return;
    	if (!tail->prev){
			delete tail;
	        head=tail=nullptr;
    	}
    	else{
			node *temp=tail->prev;
			delete tail;
    		tail=temp;
    		tail->next=nullptr;
		}
    	--_size;
    }
    node* pop_back(bool){
		if(!tail) return nullptr;
        node* popped=nullptr;
    	if (!tail->prev){
				popped=tail; 
	        head=tail=nullptr;
    	}
    	else{
			node *temp=tail->prev;
			popped=tail;
			popped->prev=nullptr;
    		tail=temp;
    		tail->next=nullptr;
		}
    	--_size;
    	return popped;
    }
    	
	void clear(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
		tail=nullptr;
		_size=0;
	}
	
	/* Traverse Methods */
	void traverse_forward()const{
    	if(!head){
    		std::cout<<"D_Deque is empty!"<<'\n';
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		std::cout<<it->data<<' ';
		std::cout<<'\n';
	}
	void traverse_backward()const{
    	if(!tail){
       		std::cout<<"List is empty!"<<'\n';
        	return;
    	}
		for(node* it=tail;it;it=it->prev)
    		std::cout<<it->data<<' ';
		std::cout<<'\n';
	}
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __DD& self){//same as traverse_forward
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __DD& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
		
	~D_Deque(){ clear(); }//dtor
};

#endif
