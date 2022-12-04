#ifndef D_STACK_GUARD
#define D_STACK_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#else
using std::forward;//using namespace std in order to reduce their name
#endif

template<typename T>
class D_Stack{//Dynamic Stack (i.e. Singly Linked-List Stack in LIFO order)
	typedef D_Stack __DS;
public:
	struct node{
	    T data;
    	node *next;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://default ctor
			data(data), next(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)noexcept://emplaced ctor
			data{std::forward<_T>(data)...},//perfect forwarding
			next(nullptr){}
	#endif
	};
private:
	/* Class Attributes */
    node *head;
	size_t _size;
	
public:	
	/* Constructors */
#if __cplusplus >= 201103L
	template<typename... _T>
	D_Stack(const size_t& n=0, _T&&... new_data)noexcept://default & emplaced fill ctor
			head(nullptr), _size(0){
			while(n>_size)
				push(forward<_T>(new_data)...);
	}
#else
	D_Stack(const size_t& n=0, const T& new_data=T())noexcept://default & fill ctor
			head(nullptr), _size(0){
			while(n>_size)
				push(new_data);
	}
#endif
	D_Stack(const __DS &other)noexcept://copy ctor
		head(nullptr), _size(0){
    	for(node *it=other.head;it;it=it->next)
	       	push(it->data);//1) copy other's data
	}
    __DS& operator=(const __DS &other)noexcept{//copy assignment operator
    	if(this!=&other){//self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push(it->data);//2) copy other's data
    	}
		return *this;
    }
#if __cplusplus >= 201103L
 	D_Stack(__DS&& other)noexcept://move ctor
  		head(other.head), _size(other._size){//1) steal other's data
		other.head=nullptr; other._size=0;//2) set other's ptr to null state
	}
	__DS& operator=(__DS&& other)noexcept{//move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			head=other.head; _size=other._size;//2) steal other's data
  			other.head=nullptr; other._size=0;//3) set other to null state
  		}
		return *this;
	}
	
	template<typename _T, size_t N>
	D_Stack(_T (&&list)[N])noexcept://move/r-value initializer_list based ctor
		head(nullptr), _size(0){
		for(const auto& it:list)//traversing list through iterator
        	push(it);
	}
#endif

	/* Accessors & Mutators */
#if __cplusplus >= 201103L
	template<typename... _T>
	node* new_node(_T&&... new_data)const{ return new node(forward<_T>(new_data)...); }
#else
	node* new_node(const T& new_data)const{ return new node(new_data); }
#endif
    
	T& operator[](const size_t& n){
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& at(const size_t& n){
		if (n>=_size){//parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	
	T& front()const{ return head->data; }
	node* front_node()const{ return head; }
	
	size_t size()const{ return _size; }
	bool empty()const{ return !head; }
	//NOTE: data accessors might require explicit execption safety handling
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push(_T&&... new_data){//direct initialization is also possible
		push(new node(forward<_T>(new_data)...));
#else
    void push(const T& new_data){//Complexity: O(1)
		push(new node(new_data));
#endif
    }
    void push(node* new_node){
        new_node->next=head;
        head=new_node;
		++_size;
    }
    
    void pop(){//Complexity:O(1)
    	if(!head) return;
    	node* temp=head->next;
		delete head;
		head=temp;
		--_size;
	}
	node* pop(bool){
    	if(!head) return nullptr;
    	node* temp=head;
		head=head->next;
		temp->next=nullptr;
		--_size;
    	return temp;
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
	
	void reverse_traverse(){ reverse_traverse(head); }//traverse stack in ascending order
	void reverse_traverse(node* temp){
		if(!temp) return;
		reverse_traverse(temp->next);
		std::cout<<temp->data<<' ';
	}
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __DS& self){//traverse stack in descending order
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __DS& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
	
	
	~D_Stack(){ clear(); }//dtor
};

#endif
