#ifndef SLL_GUARD
#define SLL_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#endif

template<typename T>
class SLL{//Singly Linked List
	struct node{//only visible/accessible within SLL classes
	    T data;
    	node *next;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())://default ctor
			data(data),next(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)://emplaced ctor
			data{std::forward<_T>(data)...},//perfect forwarding
			next(nullptr){}
	#endif
	};
	/* Private Member Attributes */
    node *head;
	size_t _size;
public:
	/* Constructors & Assignment Operators */
#if __cplusplus >= 201103L
	template<typename... _T>
	SLL(const size_t& n=0,_T&&... new_data)://default & emplaced fill ctor
		head(nullptr),_size(0){
			while(n>_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	SLL(const size_t& n=0,const T& new_data=T())://default & fill ctor
		head(nullptr),_size(0){
			while(n>_size)
				push_back(new_data);
	}
#endif
	
	//copy semantics (rule of three):
	SLL(const SLL &other)://copy ctor
		head(nullptr),_size(0){
    	for(node *it=other.head;it;it=it->next)
	       	push_back(it->data);//1) copy other's data
	}
    SLL& operator=(const SLL &other){//copy assignment operator
    	if(this!=&other){// self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
    	}
		return *this;
    }
    
#if __cplusplus >= 201103L
	//move semantics (rule of five):
 	SLL(SLL&& other)://i.e. move ctor
  		head(other.head),_size(other._size){//1) steal other's data
		other.head=nullptr; other._size=0;//2) set other's ptr to null state
	}
	SLL& operator=(SLL&& other){//move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			head=other.head; _size=other._size;//2) steal other's data
  			other.head=nullptr; other._size=0;//3) set other to null state
  		}
		return *this;
	}
	
	//custom implementations of initializer_list ctor: [note: only one can be used at a time]
	template<typename _T, size_t N>
	SLL(_T (&&list)[N],bool order_flag=false)://move initializer_list ctor {for r-values only}
		head(nullptr),_size(0){//Note: _T (&&)[N]=> temporary array of 'N' size & '_T' type
		if(order_flag)
			while(N>_size)//O(N) complexity, descending order
				push_front(std::move(list[_size]));
		else
			while(N>_size)//O(N^2) complexity, ascending order
				push_back(std::move(list[_size]));//elements of list are move constructed
	}
//	SLL(std::initializer_list<T> list)://brace copy initializer_list ctor
//		head(nullptr),_size(0){
//		for(const auto& it:list)//traversing list through iterator
//        	push_back(it);//elements of list are copy constructed
//	}
#endif
	
	/* Accessors */
    T& operator[](const size_t& n){
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& at(const size_t& n){//ensures exception safety
		if (n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	
	T& front(){ return head->data; }
	const T& front()const{ return head->data; }
	node* front_node(){ return head; }
	const node* front_node()const{ return head; }
	/*Important Notes (for ensuring exception safety manually):
		1) use condition '(front_node()||size())==true' for 'front' accessor
		2) use condition 'n>=0&&n<size()' for '[]' accessor
	*/
	size_t size()const{ return _size; }
	bool empty()const{ return !head; }
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//direct initialization is also possible
		push_front(new node(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//O(1) Complexity
		push_front(new node(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=head;
        head=new_node;
		++_size;
    }
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){
		push_back(new node(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//O(N) Complexity
    	push_back(new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!head)
    		head=new_node;
        else{
        	node *temp=head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
        }
        ++_size;
	}
	
	void pop_front(){//O(1) Complexity
    	if(!head) return;
    	node* temp=head->next;
		delete head;
		head=temp;
		--_size;
	}
	void pop_back(){//O(N) Complexity
		if(!head) return;
    	if (!head->next){
			delete head;
	        head=nullptr;
    	}
		node *temp=head;
        for(;temp->next->next;temp=temp->next);
		delete temp->next;
        temp->next=nullptr;
        --_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(const __int64& index,_T&&... new_data){
		insert(index,new node(std::forward<_T>(new_data)...));
#else
	void insert(const __int64& index,const T& new_data){
		insert(index,new node(new_data));
#endif
	}
	void insert(const __int64& index,node* new_node){
		if(index<0||index>_size) return;
    	if(!index){ push_front(new_node); return; }
		if(index==_size){ push_back(new_node); return; }
		node *temp=head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
		temp->next=new_node;
		temp->next->next=temp2;
		++_size;
	}
	
	void erase(const __int64& index){
		if(index<0||index>=_size) return;
    	if(!index){ pop_front(); return; }
		if(index==_size-1){ pop_back(); return; }
		node *temp=head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
		delete temp->next;
    	temp->next=temp2;
    	--_size;
	}
	
	void clear(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
		_size=0;
	}
	//additional specialized modifier:
	void rearrange_even_nos_at_beginning();
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out,const SLL& self){//same as: traverse()
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,SLL& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
	
	~SLL(){ clear(); }//dtor
};

#endif
