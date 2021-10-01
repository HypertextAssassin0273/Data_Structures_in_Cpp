#ifndef FORWARD_LIST_GUARD
#define FORWARD_LIST_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#else
using std::forward;//i.e. using namespace std in order to reduce their name
#endif


/** Base Class for Foward_List (i.e. Singly Linked-List) **/
template<typename T>
class Forward_List_Base{//i.e. holds all common functionalities of child classes
public:
	struct node{
	    T data;
    	node *next;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)noexcept://i.e. emplaced ctor
			data{std::forward<_T>(data)...},//i.e. perfect forwarding
			next(nullptr){}
	#endif
    	static void swap_data(node &xp,node &yp){//i.e. swaps current data
			T temp=xp.data;
	 		xp.data=yp.data;
			yp.data=temp;
		}
		
		//i.e. use these operators when u want to keep data private/protected
		friend std::ostream& operator<<(std::ostream& out,const node& self){
			out<<self.data;
			return out;
		}
		friend std::istream& operator>>(std::istream& in,node& self){
			in>>self.data;
			return in;
		}
	};
protected:
	/* Class Attributes */
    node *head;
	size_t _size;
	
	/* Constructor */
	Forward_List_Base(node* head=nullptr,const size_t& _size=0)noexcept:
		head(head),_size(_size){}
	
	/* Accessors & Mutators */
public:
#if __cplusplus >= 201103L
	template<typename... _T>
	node* new_node(_T&&... new_data)const{ return new node(forward<_T>(new_data)...); }
#else
	node* new_node(const T& new_data)const{ return new node(new_data); }
#endif
    T& operator[](const size_t& n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& front()const{
		if (head)
			return head->data;
		throw false;
	}
	node* front_node()const{ return head; }
	size_t size()const{ return _size; }
	bool empty()const{ return head?false:true; }
	
	/* Modifiers */
	void reverse(){
		if(head) reverse_recursively(head);
		else std::cout<<"List is empty!"<<'\n';
	}
private: //i.e. hidden recursive method
	node* reverse_recursively(node *temp){//i.e. worst-case: O(n)
		if(!temp->next)
			head=temp;
		else{
			reverse_recursively(temp->next)->next=temp;//i.e. direct assigning to returned ptr's next_ptr
			temp->next=nullptr;
		}
		return temp;
	}
public:
	void merge(Forward_List_Base &other,const __int64& pos=0){
		if(!other.head||pos>_size)
			return;//i.e. do nothing if other have no nodes or size exceeds the given pos
		node *temp;
		if(!pos){//i.e. if pos is '0', then directly join head of other to head of list1
			temp=head;
			head=other.head;
		}
		else{
			node *list1_temp=head;
			for(int i=1;i<pos;++i)
				list1_temp=list1_temp->next;
			temp=list1_temp->next;
			list1_temp->next=other.head;
		}
		while(other.head->next)
			other.head=other.head->next;
		other.head->next=temp;
		other.head=nullptr;
		_size+=other._size;
		other._size=0;
	}
	void swap_nodes(const size_t& posX,const size_t& posY){
		if (posX==posY)//i.e. do nothing if x & y are same
			return;
		node *prevX=nullptr,*currX=head;
		while (currX&&currX->data!=posX){//i.e. search for X (keep track of prevX and CurrX)
		    prevX=currX;
    		currX=currX->next;
		}
		node *prevY=nullptr,*currY=head;
		while (currY&&currY->data!=posY){//i.e. search for Y (keep track of prevY and CurrY)
    		prevY=currY;
    		currY=currY->next;
		}
		if (!currX||!currY)//i.e. do nothing if either x or y isn't present
    		return;
		if (prevX)//i.e. if X is not head of linked list then make Y as new head
    		prevX->next=currY;
		else
    		head=currY;
		if (prevY)//i.e. if Y is not head of linked list then make X as new head
    		prevY->next=currX;
		else
    		head=currX;
    	/*i.e. swap next_ptrs */
		node *temp=currY->next;
		currY->next=currX->next;
		currX->next=temp;
	}
	void swap_data(const size_t& posX,const size_t& posY){
		if (posX==posY)//i.e. do nothing if x & y are same
			return;
		node *currX=head,*currY=head;
		while (currX&&currX->data!=posX)//i.e. search for X
    		currX=currX->next;
		while (currY&&currY->data!=posY)//i.e. search for Y
    		currY=currY->next;
    	if (!currX||!currY)//i.e. do nothing if either x or y isn't present
    		return;
    	node::swap_data(*currX,*currY);
	}
	void sort(bool direction_flag=true){//i.e. improved bubble sort, using data-swap
    	if (!head||!head->next)//i.e. do nothing if size is 0 or 1
    	    return;
		for(node *ptr=nullptr,*lptr=nullptr;true;lptr=ptr){
	        bool swapped=false;
	        for (ptr=head;ptr->next!=lptr;ptr=ptr->next){
	        	if(direction_flag){
            		if (ptr->data>ptr->next->data){//i.e. ascending order
 	    	    	    node::swap_data(*ptr,*ptr->next);
    	            	swapped=true;
            		}
				}
            	else{
            		if (ptr->data<ptr->next->data){//i.e. descending order
 	    	    	    node::swap_data(*ptr,*ptr->next);
    	            	swapped=true;
            		}
				}
        	}
        	if(!swapped)
        		break;
    	}
	}
	
	/* Non-Modifiers */
	void traverse()const{//i.e. traverse_forward
    	if(!head){
       		std::cout<<"List is empty!"<<'\n';
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		std::cout<<it->data<<' ';
		std::cout<<'\n';
	}	
	bool detect_loop(){//i.e. Floyd’s Cycle Algorithm (extra)
 	   	node *slow_ptr=head,*fast_ptr=head;
    	while (slow_ptr&&fast_ptr&&fast_ptr->next){
    	    slow_ptr=slow_ptr->next;
    	    fast_ptr=fast_ptr->next->next;
    	    if (slow_ptr==fast_ptr)
    	        return true;
    	}
    	return false;
	}
	
	/* Comparators */
	bool operator==(const Forward_List_Base& other)const{
		if(other._size!=_size)
			return false;
		for (node *iter1=head,*iter2=other.head;iter1&&iter2;iter1=iter1->next,iter2=iter2->next)
    		if (iter1->data!=iter2->data)
      			return false;
  		return true;
	}
	bool operator!=(const Forward_List_Base& other)const{ return !(*this==other); }
	
	bool operator<(const Forward_List_Base& other)const{
  		node *iter1=head,*iter2=other.head; 
		size_t i=0;
  		for (;iter1&&iter2;iter1=iter1->next,iter2=iter2->next,++i){
  			if(i==other._size||iter2->data<iter1->data)
  				return false;
  			else if(iter1->data<iter2->data)
  				return true;
		}
		return i!=other._size;
	}
    bool operator>(const Forward_List_Base& other)const{ return other<*this; }
	bool operator<=(const Forward_List_Base& other)const{ return !(other<*this); }
	bool operator>=(const Forward_List_Base& other)const{ return !(*this<other); }
	
	/* Iterator */
	struct iterator{//i.e. forward_iterator
    	iterator(node* ptr=nullptr):ptr(ptr){}
    	
    	node& operator*()const{ return *ptr; }
    	
		iterator& operator++(){ ptr=ptr->next; return *this; }
		iterator operator++(int){ iterator temp(*this); ptr=ptr->next; return temp; }
		
		bool operator==(const iterator& other)const{ return ptr==other.ptr; }
		bool operator!=(const iterator& other)const{ return ptr!=other.ptr; }
	private:
		node* ptr;
    };
    
	iterator begin()const{ return iterator(head); }//i.e. points to first element
	iterator end()const{ return iterator(nullptr); }//i.e. points to last element
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out,const Forward_List_Base& self){//i.e. same as traverse
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,Forward_List_Base& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
};


template<typename T,bool=false>
class Forward_List;//i.e. forward declaration (for template specialization)


/** Standard Minimal Version of STL::forward_list (default) **/
template<typename T>
class Forward_List<T,false>:public Forward_List_Base<T>{
typedef Forward_List_Base<T> base;
public:
	typedef typename base::node node;
	
	/* Constructors */
	Forward_List(const size_t& n=0)noexcept{//i.e. default ctor
			while(n>base::_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	Forward_List(const size_t& n,_T&&... new_data)noexcept{//i.e. emplaced fill ctor
			while(n>base::_size)
				push_back(forward<_T>(new_data)...);
	}
#else
	Forward_List(const size_t& n,const T& new_data)noexcept{//i.e. fill ctor
			while(n>base::_size)
				push_back(new_data);
	}
#endif
	Forward_List(const Forward_List &other)noexcept{//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
	       	push_back(it->data);//1) copy other's data
	}
    Forward_List& operator=(const Forward_List &other)noexcept{//i.e. copy assignment operator
    	if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
    	}
		return *this;
    }
#if __cplusplus >= 201103L
 	Forward_List(Forward_List&& other)noexcept://i.e. move ctor
  		base(other.head,other._size){//1) steal other's data
		other.head=nullptr; other._size=0;//2) set other's ptr to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	Forward_List& operator=(Forward_List&& other)noexcept{//i.e. move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			base::head=other.head; base::_size=other._size;//2) steal other's data
  			other.head=nullptr; other._size=0;//3) set other to null state
  		}
		return *this;
	}
	Forward_List(std::initializer_list<T> list)noexcept{//i.e.initializer_list based ctor
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. direct initialization is also possible
		push_front(new node(forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=base::head;
        base::head=new_node;
		++base::_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){
		push_back(new node(forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(n)
    	push_back(new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!base::head)
    		base::head=new_node;
        else{
        	node *temp=base::head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
        }
        ++base::_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!base::head) return;
    	node* temp=base::head->next;
		delete base::head;
		base::head=temp;
		--base::_size;
	}
	node* pop_front(bool){
    	if(!base::head) return nullptr;
    	node* temp=base::head;
		base::head=base::head->next;
		temp->next=nullptr;
		--base::_size;
    	return temp;
	}
	
	void pop_back(){//Complexity: O(n)
		if(!base::head) return;
    	if (!base::head->next){
			delete base::head;
	        base::head=nullptr;
    	}
		node *temp=base::head;
        for(;temp->next->next;temp=temp->next);
		delete temp->next;
        temp->next=nullptr;
        --base::_size;
    }
    node* pop_back(bool){
		if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head; 
	        base::head=nullptr;
    	}
    	else{
		    node *temp=base::head;
        	for(;temp->next->next;temp=temp->next);
			popped=temp->next;
        	temp->next=nullptr;
		}
        --base::_size;
    	return popped;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){//i.e. O(logn)
		push_middle(new node(forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){
	    push_middle(new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!base::head)
			base::head=new_node;
        else{
			node *slow_ptr=base::head,*fast_ptr=base::head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    slow_ptr->next=new_node;
		}
	    ++base::_size;
	}
	
	void pop_middle(){//i.e. O(logn)
	    if(!base::head) return;
    	if (!base::head->next){
			delete base::head;
	        base::head=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head,*prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			delete slow_ptr;
		}
    	--base::_size;
	}
	node* pop_middle(bool){
	    if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head;
	        base::head=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head,*prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			popped=slow_ptr;
		}
    	--base::_size;
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(const __int64& index,_T&&... new_data){
		insert(index,new node(forward<_T>(new_data)...));
#else
	void insert(const __int64& index,const T& new_data){
		insert(index,new node(new_data));
#endif
	}
	void insert(const __int64& index,node* new_node){
		if(index<0||index>base::_size) return;
    	if(!index){ push_front(new_node); return; }
		if(index==base::_size){ push_back(new_node); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
		temp->next=new_node;
		temp->next->next=temp2;
		++base::_size;
	}
	
	void erase(const __int64& index){
		if(index<0||index>=base::_size) return;
    	if(!index){ pop_front(); return; }
		if(index==base::_size-1){ pop_back(); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
		delete temp->next;
    	temp->next=temp2;
    	--base::_size;
	}
	node* erase(const __int64& index,bool){
		if(index<0||index>=base::_size) return nullptr;
    	if(!index) return pop_front(true);
		if(index==base::_size-1) return pop_back(true);
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next,*popped=temp->next;
    	temp->next=temp2;
    	--base::_size;
    	return popped;
	}
	
	void remove_consecutive_duplicates(){
		if (base::head)//i.e. do nothing if size is 0
        	remove_consecutive_duplicates_recursively(base::head);
	}
	//TODO: void remove_all_duplicates();
private: //i.e. hidden recursive method
	void remove_consecutive_duplicates_recursively(node* temp){//i.e. works best for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		delete to_delete;
        		--base::_size;
        		remove_consecutive_duplicates_recursively(temp);
        	}
        	else //i.e. advances only if no deletion
	            remove_consecutive_duplicates_recursively(temp->next); 
   	 	}
	}
public:
	
	void clear(){
		node* temp;
		while(base::head){
	   		temp=base::head->next;
	    	delete base::head;
    		base::head=temp;	
		}
		base::_size=0;
	}
	
	/* Iterator */
	typedef typename base::iterator iterator;
	
	~Forward_List(){ clear(); }//i.e. dtor
};


/** Optimized Version with Garbage Collector **/
template<typename T>
class Forward_List<T,true>:public Forward_List_Base<T>{
typedef Forward_List_Base<T> base;
public:
	typedef typename base::node node;
protected:
	struct garbage_collector{//i.e. implementing stack by LIFO order
		static const size_t max_capacity=128;
		size_t _size;
		node *ptr;
		
		garbage_collector():_size(0),ptr(nullptr){}
		
		void push(node* _new){//i.e. complexity O(1)
			_new->next=ptr;
			ptr=_new;
			++_size;
			if(_size>=max_capacity)
				release();
		}
	#if __cplusplus >= 201103L
		template<typename... _T>
		node* pop(_T&&... new_data){//i.e. complexity O(1)
	#else
		node* pop(const T& new_data){
    #endif
			if(!ptr)
    	   		return nullptr;
	    	node *popped=ptr;
    		ptr=ptr->next;
    		--_size;
    	#if __cplusplus >= 201103L
    		popped->data={forward<_T>(new_data)...};
    	#else
    		popped->data=new_data;
    	#endif
    		popped->next=nullptr;
    		return popped;
		}
		void release(){
			node* temp;
			size_t prev_size=_size;
			while(_size>prev_size/2){
				temp=ptr->next;
	    		delete ptr;
    			ptr=temp;
				--_size;
			}
		}
		void clear(){//i.e. complexity O(n)
			node* temp;
			while(ptr){
	   			temp=ptr->next;
	    		delete ptr;
    			ptr=temp;
			}
		}
		~garbage_collector(){ clear(); }
		/*Drawback:
			whenever a list is destroyed, its node transfer to its' type of garbage collector 
			at O(n) complexity */
	};
	
	/* Class Attribute (additional) */
	static garbage_collector GC;

public:
	/* Constructors */
	Forward_List(const size_t& n=0)noexcept{//i.e. default ctor
			while(n>base::_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	Forward_List(const size_t& n,_T&&... new_data)noexcept{//i.e. emplaced fill ctor
			while(n>base::_size)
				push_back(forward<_T>(new_data)...);
	}
#else
	Forward_List(const size_t& n,const T& new_data)noexcept{//i.e. fill ctor
			while(n>base::_size)
				push_back(new_data);
	}
#endif
	Forward_List(const Forward_List &other)noexcept{//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
	       	push_back(it->data);//1) copy other's data
	}
    Forward_List& operator=(const Forward_List &other)noexcept{//i.e. copy assignment operator
    	if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
    	}
		return *this;
    }
#if __cplusplus >= 201103L
 	Forward_List(Forward_List&& other)noexcept://i.e. move ctor
  		base(other.head,other._size){//1) steal other's data
		other.head=nullptr; other._size=0;//2) set other's ptr to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	Forward_List& operator=(Forward_List&& other)noexcept{//i.e. move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			base::head=other.head; base::_size=other._size;//2) steal other's data
  			other.head=nullptr; other._size=0;//3) set other to null state
  		}
		return *this;
	}
	Forward_List(std::initializer_list<T> list)noexcept{//i.e.initializer_list based ctor
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. direct initialization is also possible
		push_front(GC.ptr?GC.pop(forward<_T>(new_data)...):new node(forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=base::head;
        base::head=new_node;
		++base::_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){
		push_back(GC.ptr?GC.pop(forward<_T>(new_data)...):new node(forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(n)
    	push_back(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!base::head)
    		base::head=new_node;
        else{
        	node *temp=base::head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
        }
        ++base::_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!base::head) return;
    	node* temp=base::head->next;
		GC.push(base::head);
		base::head=temp;
		--base::_size;
	}
	node* pop_front(bool){
    	if(!base::head) return nullptr;
    	node* temp=base::head;
		base::head=base::head->next;
		temp->next=nullptr;
		--base::_size;
    	return temp;
	}
	
	void pop_back(){//Complexity: O(n)
		if(!base::head) return;
    	if (!base::head->next){
			GC.push(base::head);
	        base::head=nullptr;
    	}
		node *temp=base::head;
        for(;temp->next->next;temp=temp->next);
		GC.push(temp->next);
        temp->next=nullptr;
        --base::_size;
    }
    node* pop_back(bool){
		if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head; 
	        base::head=nullptr;
    	}
    	else{
		    node *temp=base::head;
        	for(;temp->next->next;temp=temp->next);
			popped=temp->next;
        	temp->next=nullptr;
		}
        --base::_size;
    	return popped;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){
		push_middle(GC.ptr?GC.pop(forward<_T>(new_data)...):new node(forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){
	    push_middle(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!base::head)
			base::head=new_node;
        else{
			node *slow_ptr=base::head,*fast_ptr=base::head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    slow_ptr->next=new_node;
		}
	    ++base::_size;
	}
	
	void pop_middle(){//i.e. O(logn)
	    if(!base::head) return;
    	if (!base::head->next){
			GC.push(base::head);
	        base::head=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head,*prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			GC.push(slow_ptr);
		}
    	--base::_size;
	}
	node* pop_middle(bool){
	    if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head;
	        base::head=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head,*prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			popped=slow_ptr;
		}
    	--base::_size;
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(const __int64& index,_T&&... new_data){
		insert(index,GC.ptr?GC.pop(forward<_T>(new_data)...):new node(forward<_T>(new_data)...));
#else
	void insert(const __int64& index,const T& new_data){
		insert(index,GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void insert(const __int64& index,node* new_node){
		if(index<0||index>base::_size) return;
    	if(!index){ push_front(new_node); return; }
		if(index==base::_size){ push_back(new_node); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
		temp->next=new_node;
		temp->next->next=temp2;
		++base::_size;
	}
	
	void erase(const __int64& index){
		if(index<0||index>=base::_size) return;
    	if(!index){ pop_front(); return; }
		if(index==base::_size-1){ pop_back(); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
		GC.push(temp->next);
    	temp->next=temp2;
    	--base::_size;
	}
	node* erase(const __int64& index,bool){
		if(index<0||index>=base::_size) return nullptr;
    	if(!index) return pop_front(true);
		if(index==base::_size-1) return pop_back(true);
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next,*popped=temp->next;
    	temp->next=temp2;
    	--base::_size;
    	return popped;
	}

	void remove_consecutive_duplicates(){
		if (base::head)//i.e. do nothing if size is 0
        	remove_consecutive_duplicates_recursively(base::head);
	}
	//TODO: void remove_all_duplicates();
private: //i.e. hidden recursive method
	void remove_consecutive_duplicates_recursively(node* temp){//i.e. works best for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		GC.push(to_delete);
        		--base::_size;
        		remove_consecutive_duplicates_recursively(temp);
        	}
        	else //i.e. advances only if no deletion
	            remove_consecutive_duplicates_recursively(temp->next); 
   	 	}
	}
public:
	
	void clear(){//i.e. O(n) complexity
		node* temp;
			while(base::head){
	   			temp=base::head->next;
	    		GC.push(base::head);
    			base::head=temp;	
			}
		base::_size=0;
	}
	
	/* Iterator */
	typedef typename base::iterator iterator;
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~Forward_List(){ clear(); }//i.e. dtor
};

template<typename T>
typename Forward_List<T,true>::garbage_collector Forward_List<T,true>::GC;//i.e. initializing static member ctor

#endif
