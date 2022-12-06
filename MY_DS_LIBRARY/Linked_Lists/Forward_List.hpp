/** Singly Linked List (as Forward_List) **/
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Safe when accessing elements with accessors (Exception somewhat handled)
	3) All neccessary STL List class 'modifiers' & 'iterators' are provided
	4) Garbage Collector version is also available for improved efficiency in long-run situations
*/
#ifndef FORWARD_LIST_GUARD
#define FORWARD_LIST_GUARD 1

#include "Node.hpp"
#include "../Utilities/Swap.hpp"
#include "../Utilities/Garbage_Collector.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

/** Standard Minimal Version of STL::forward_list **/
//NOTE: for optimize results, no bound exception safety provided for position based modifiers
template<typename T>
class Forward_List{
	typedef Forward_List __FL;
public:
	typedef SLL_Node<T> node;
	
protected:
	/* Main-Class Attribute */
    node *head;
	
public:
	/* Constructors & Assignment Operators */
	Forward_List()noexcept://default ctor
		head(nullptr){}
	
	Forward_List(size_t n, const T& new_data=T())noexcept://fill ctor
		head(nullptr){
		if(n){
			node* tail=head=new node(new_data);
			while(--n)
				tail=tail->next=new node(new_data);
		}
	}
	
	//copy semantics (deep copy):
	Forward_List(const __FL &other)noexcept://copy ctor
		head(nullptr){
		if(other.head){//1) copy other's data
			node* tail=head=new node(other.head->data);
			for(node* it=other.head->next;it;it=it->next)
				tail=tail->next=new node(it->data);
		}
	}
    __FL& operator=(const __FL &other)noexcept{//copy assignment operator
    	if(this==&other) return *this;//self-assignment protection
		clear();//1) clear existing resources
        if(other.head){//2) copy other's data
			node* tail=head=new node(other.head->data);
			for(node* it=other.head->next;it;it=it->next)
				tail=tail->next=new node(it->data);
		}
		return *this;
    }
#if __cplusplus >= 201103L
	
 	//move semantics (shallow copy):
	Forward_List(__FL&& other)noexcept://move ctor
		head(other.head){//1) steal other's data
		other.head=nullptr;//2) set other's ptr to null state
	}
	__FL& operator=(__FL&& other)noexcept{//move assignment operator
  		if(this==&other) return *this;
		clear();//1) clear existing resources
  		head=other.head;//2) steal other's data
  		other.head=nullptr;//3) set other to null state
		return *this;
	}
	
	template<typename _T, size_t N>
	Forward_List(_T (&&init_list)[N])noexcept://move/r-value initializer_list based ctor
		head(nullptr){
		if(N){
			node* tail=head=new node(std::move(init_list[0]));
			for(size_t i=1;i<N;++i)//constructs singly linked-list in ascending order
				tail=tail->next=new node(std::move(init_list[i]));
		}
	}
#endif
	
	/* Accessors & Mutators */
    T& operator[](size_t n){
		node* it=head;
		while(n--) it=it->next;
		return it->data;
	}

	T& front(){ return head->data; }
	const T& front()const{ return head->data; }
	
	node* front_node(){ return head; }
	//NOTE: for data safety in read-only object, const overloads isn't provided for node accessor.
	
	bool empty()const{ return !head; }
	
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'empty()==false' for 'front' accessor.
		2) use condition 'n<size()' for '[]' operator accessor.
	*/
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//emplace_front [direct initialization is also possible]
		push_front(new node(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=head;
        head=new_node;
    }
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//emplace_back
		push_back(new node(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(n)
    	push_back(new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(head){
			node *temp=head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
		}
        else head=new_node;
	}
	
	void pop_front(){//Complexity:O(1)
    	if(!head) return;
    	node* temp=head->next;
		delete head;
		head=temp;
	}
	node* pop_front(bool){
    	if(!head) return nullptr;
    	node* popped=head;
		head=head->next;
		popped->next=nullptr;
    	return popped;
	}
	
	void pop_back(){//Complexity: O(n)
		if(!head) return;
    	if(head->next){
			node *temp=head;
        	while(temp->next->next)
				temp=temp->next;
			delete temp->next;
        	temp->next=nullptr;
    	}else{
    		delete head;
	        head=nullptr;
		}
    }
    node* pop_back(bool){
		if(!head) return nullptr;
        node* popped;
    	if(head->next){
			node *temp=head;
        	while(temp->next->next)
				temp=temp->next;
			popped=temp->next;
        	temp->next=nullptr;
    	}else{
    		popped=head; 
	        head=nullptr;
		}
    	return popped;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){//emplace_middle
		push_middle(new node(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){//Complexity: O(logn)
	    push_middle(new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(head){
			node *slow_ptr=head, *fast_ptr=head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    slow_ptr->next=new_node;
		}
		else head=new_node;
	}
	
	void pop_middle(){//Complexity: O(logn)
	    if(!head) return;
    	if(head->next){
    		node *slow_ptr=head, *fast_ptr=head, *prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			delete slow_ptr;
    	}else{
		    delete head;
	        head=nullptr;
		}
	}
	node* pop_middle(bool){
	    if(!head) return nullptr;
        node* popped;
    	if(head->next){
			node *slow_ptr=head, *fast_ptr=head, *prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
			popped=slow_ptr;
			popped->next=nullptr;
    	}else{
    		popped=head;
	        head=nullptr;
		}
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(size_t index, _T&&... new_data){//emplaces node at given index position
		insert(index, new node(std::forward<_T>(new_data)...));
#else
	void insert(size_t index, const T& new_data){//Complexity: O(n)
		insert(index, new node(new_data));
#endif
	}
	void insert(size_t index, node* new_node){
    	if(!index){ push_front(new_node); return; }
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next;
		target->next=new_node;
		new_node->next=temp;
	}
	
#if __cplusplus >= 201103L
	template<bool=true>
#endif //Note: this helps us to forcefully use this overload version when datatype is integer
	void erase(size_t index=0){//removes given index position node in O(n) complexity
    	if(!index){ pop_front(); return; }
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next;
		delete target->next;
    	target->next=temp;
	}
	node* erase(size_t index, bool){
    	if(!index) return pop_front(true);
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next, *popped=target->next;
    	target->next=temp;
    	popped->next=nullptr;
    	return popped;
	}
	void erase(const T& key){//removes targeted node in O(n) complexity
//		if(!head) return;
    	if(key==front()){ pop_front(); return; }
//		if(!head->next) return;
		node *target=head;
		while(target->next->data!=key){
			target=target->next;
//			if(!target->next) return;
		}
    	node* temp=target->next->next;
		delete target->next;
    	target->next=temp;
	}//Note: for optimize results, bound exception safeties are removed
	void erase(node *current){//removes given random node in O(n) complexity
    	if(current==head){ pop_front(); return; }
		if(!(current&&head)) return;
		node *previous=head;
		while(previous->next!=current){
			previous=previous->next;
			if(!previous->next) return;
		}
		previous->next=current->next;
		delete current;
	}//Warning: no exception is provided to identify wrong node address
	
	void resize(size_t new_size, const T& new_data=T()){//Complexity: O(n+m)
		size_t n=size();
		if(new_size>n){
			n=new_size-n;
			while(n--) push_back(new_data);
		}else if(new_size<n){
    		n-=new_size;
    		while(n--) pop_back();
		}
	}
	
	void unique(){ if(head) unique(head); }//removes consecutive duplicates
	
	//TODO: void remove_all_duplicates(...);
	
	void sort(bool direction_flag=true){//slightly improved insertion-sort with O(n^2) complexity
    	void (__FL::*fp)(node*)=direction_flag?&ascending_sorted_insert:
											  &descending_sorted_insert;//function_pointer
		node* current=head;
    	head=nullptr;//disconnecting link to 'current' list
    	while(current){
        	node* temp=current->next;
        	(this->*fp)(current);//calling pointed member function
        	current=temp;
    	}
	}//Note: use when 'move semantics' aren't available for respective type & list has heavy-weight objects
	
#if __cplusplus >= 201103L
	template<typename _T>
	void sorted_insert(_T&& new_data, bool direction_flag=true){//Complexity: O(n)
		sorted_insert(new node(std::forward<_T>(new_data)), direction_flag);
#else
	void sorted_insert(const T& new_data, bool direction_flag=true){
		sorted_insert(new node(new_data), direction_flag);
#endif
	}
	void sorted_insert(node* new_node, bool direction_flag=true){
		direction_flag?ascending_sorted_insert(new_node):descending_sorted_insert(new_node);
	}
	
	void reverse(){ if(head) reverse_recursively(head); }//Complexity: O(n)
	
	void merge(__FL &other, size_t pos=0){
		if(!other.head) return;//do nothing if other have no nodes
		node *temp;
		if(!pos){//if pos is '0', then directly join 'head' of 'other' to 'head' of 'this'
			temp=head;
			head=other.head;
		}else{
			node *target=head;
			for(size_t i=1;i<pos;++i)
				target=target->next;
			temp=target->next;
			target->next=other.head;
		}
		while(other.head->next)
			other.head=other.head->next;
		other.head->next=temp;//connecting 'tail' of 'other' to 'temp'
		other.head=nullptr;
	}
	
	void swap_nodes(const T& X, const T& Y){//efficient when datatype 'T' has no 'move semantics' available
		if(X==Y) return;//do nothing if X & Y are same
		node **prevX=nullptr, **prevY=nullptr;
		//note: these double ptrs track reference of ptr that points node holding data same as X or Y
		for(node **head_ref=&head;*head_ref;head_ref=&(*head_ref)->next){//search for X & Y in list
			if((*head_ref)->data==X)
				prevX=head_ref;//store previous node ptr of X
			else if((*head_ref)->data==Y)
				prevY=head_ref;//store previous node ptr of Y
		}
		if(prevX&&prevY){//do nothing if either of them aren't present
			swap(*prevX, *prevY);//swap previous ptrs
			swap((*prevX)->next, (*prevY)->next);//swap previous's next ptrs (a.k.a current pointed nodes)
		}
	}
//	void swap_nodes(const T& X, const T& Y){//slight less efficient version (easy to understand)
//		if(X==Y) return;//do nothing if X & Y are same
//		node *prevX=nullptr, *currX=head;
//		while(currX&&currX->data!=X){//search for X (keep track of prevX and CurrX)
//		    prevX=currX;
//    		currX=currX->next;
//		}
//		node *prevY=nullptr, *currY=head;
//		while(currY&&currY->data!=Y){//search for Y (keep track of prevY and CurrY)
//    		prevY=currY;
//    		currY=currY->next;
//		}
//		if(currX&&currY){//do nothing if either x or y isn't present
//			(prevX?prevX->next:head)=currY;//if X is head then set Y as new head, else join previous X to Y
//			(prevY?prevY->next:head)=currX;//if Y is head then set X as new head, else join previous Y to X
//			swap(currX->next, currY->next);//swap next ptrs
//		}
//	}
	
	void swap_data(const T& X, const T& Y){//efficient when datatype 'T' has 'move semantics' available
		if(X==Y) return;//do nothing if X & Y are same
		node *currX=head, *currY=head;
		while(currX&&currX->data!=X)//search for X & then set its current position as pointer
    		currX=currX->next;
		while(currY&&currY->data!=Y)//search for Y & then set its current position as pointer
    		currY=currY->next;
    	if(currX&&currY)//do nothing if either X or Y isn't present
    		swap(currX->data, currY->data);
	}
	
	void clear(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
	}
	
	/* Non-Modifiers */
	size_t size()const{//counts total nodes/values
		size_t i=0;
		for(node *it=head;it;it=it->next) ++i;
		return i;
	}
	void traverse()const{//traverse_forward
    	if(!head){
       		std::cout<<"List is empty!"<<'\n';
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		std::cout<<it->data<<' ';
		std::cout<<'\n';
	}
	bool detect_loop()const{//Floyd’s Cycle Algorithm (Note: should be static or part of Algorithm directory)
 	   	node *slow_ptr=head, *fast_ptr=head;
    	while(slow_ptr&&fast_ptr&&fast_ptr->next){
    	    slow_ptr=slow_ptr->next;
    	    fast_ptr=fast_ptr->next->next;
    	    if(slow_ptr==fast_ptr) return true;
    	}
    	return false;
	}
	
	/* Comparators */
	bool operator==(const __FL& other)const{
		node *iter1=head, *iter2=other.head;
		while(iter1&&iter2){
			if(iter1->data!=iter2->data) return false;
			iter1=iter1->next, iter2=iter2->next;
		}
  		return iter1==iter2;
	}
	bool operator!=(const __FL& other)const{ return !(*this==other); }
	
	bool operator<(const __FL& other)const{
  		node *iter1=head, *iter2=other.head; 
  		while(iter1){
  			if(!iter2||iter1->data>iter2->data) return false;
  			else if(iter1->data<iter2->data) return true;
  			iter1=iter1->next, iter2=iter2->next;
		}
		return iter1!=iter2;
	}
    bool operator>(const __FL& other)const{ return other<*this; }
	bool operator<=(const __FL& other)const{ return !(other<*this); }
	bool operator>=(const __FL& other)const{ return !(*this<other); }
	
	/* Iterator */
	template<typename DRT>//data return type (i.e. for handling const & non-const both)
	class FL_Iterator{//traverses in forward direction
		typedef FL_Iterator __self;
		node* ptr;
	public:
    	FL_Iterator(node* ptr=nullptr)noexcept://default ctor
			ptr(ptr){}
		//accessors:
    	DRT& operator*()const{ return ptr->data; }
    	DRT& operator[](size_t n)const{ node* it=ptr; while(n--) it=it->next; return it->data; }
		//modifiers:
		__self& operator++(){ ptr=ptr->next; return *this; }
		__self operator++(int){ __self temp(*this); ptr=ptr->next; return temp; }
		__self& operator+=(size_t n){ while(n--) ptr=ptr->next; return *this; }
		__self operator+(size_t n)const{ node* it=ptr; while(n--) it=it->next; return __self(it); }
		//comparators:
		bool operator==(const __self& other)const{ return ptr==other.ptr; }
		bool operator!=(const __self& other)const{ return ptr!=other.ptr; }
    };
    
    //available forward_list iterator objects (const/non_const):
	typedef FL_Iterator<T> iterator;
	typedef FL_Iterator<const T> const_iterator;
    
    //available forward_list iterator methods:
	iterator begin(){ return iterator(head); }//points to first element
	iterator end(){ return iterator(nullptr); }//points end of list i.e. null
	
	const_iterator begin()const{ return const_iterator(head); }//const (read only) version
	const_iterator end()const{ return const_iterator(nullptr); }
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __FL& self){//same as traverse
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __FL& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
	
	/* Destructor (a.k.a. dtor) */
	~Forward_List(){ clear(); }
	
	/* Hidden Methods */
private:
	void unique(node* temp){//works best for sorted data
    	if(temp->next){
        	if(temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		delete to_delete;
        		unique(temp);
        	}
        	else unique(temp->next);//advances only if no deletion
   	 	}
	}
	
	void ascending_sorted_insert(node* new_node){
		if(!head||new_node->data<=head->data){
    	    new_node->next=head;
    	    head=new_node;
    	}else{
    		node *temp=head;
    		while(temp->next&&temp->next->data<new_node->data)
    			temp=temp->next;
    		new_node->next=temp->next;
    		temp->next=new_node;
		}
	}
	void descending_sorted_insert(node* new_node){
		if(!head||new_node->data>=head->data){
    	    new_node->next=head;
    	    head=new_node;
    	}else{
    		node *temp=head;
    		while(temp->next&&temp->next->data>new_node->data)
    			temp=temp->next;
    		new_node->next=temp->next;
    		temp->next=new_node;
		}
	}
	
protected:
	node* reverse_recursively(node *temp){//worst-case: O(n)
		if(temp->next){
			reverse_recursively(temp->next)->next=temp;//direct assigning to returned ptr's next_ptr
			temp->next=nullptr;
		}
		else head=temp;
		return temp;
	}
};


/** Optimized Version with Garbage Collector **/
template<typename T>
class Forward_List_O:
	public Forward_List<T>{
	
	/* Simplified Type Names (for Forward_List_O) */
	typedef Forward_List_O __FLO;
	typedef Forward_List<T> base;
	typedef typename base::node node;
	
	using base::head;
	
	/* Main-Class Attributes */
	static garbage_collector<node> GC;
	size_t _size;
	node *tail;
	
public:
	/* Constructors & Assignment Operators */
	Forward_List_O()noexcept://default ctor
		_size(0), tail(nullptr){}
	
	Forward_List_O(size_t n, const T& new_data=T())noexcept://fill ctor
		_size(n), tail(nullptr){
		if(n){
			tail=head=GC.empty()?new node(new_data):GC.pop(new_data);
			while(--n)
				tail=tail->next=GC.empty()?new node(new_data):GC.pop(new_data);
		}
	}
	
	//copy semantics (deep copy):
	Forward_List_O(const __FLO &other)noexcept://copy ctor
		_size(other._size), tail(nullptr){
		if(other.head){
			tail=head=GC.empty()?new node(other.head->data):GC.pop(other.head->data);
			for(node* it=other.head->next;it;it=it->next)
				tail=tail->next=GC.empty()?new node(it->data):GC.pop(it->data);
		}
	}
    __FLO& operator=(const __FLO &other)noexcept{//copy assignment operator
    	if(this==&other) return *this;
		clear();
        if(other.head){
        	_size=other._size;
			tail=head=GC.empty()?new node(other.head->data):GC.pop(other.head->data);
			for(node* it=other.head->next;it;it=it->next)
				tail=tail->next=GC.empty()?new node(it->data):GC.pop(it->data);
		}
		return *this;
    }
#if __cplusplus >= 201103L
	
	//move semantics (shallow copy):
	Forward_List_O(__FLO&& other)noexcept://move ctor
		_size(other._size), tail(other.tail), base(std::move(other)){
		other._size=0; other.tail=nullptr;
	}
	__FLO& operator=(__FLO&& other)noexcept{//move assignment operator
  		if(this==&other) return *this;
		clear();
  		head=other.head; tail=other.tail; _size=other._size;
  		other.head=other.tail=nullptr; other._size=0;
		return *this;
	}
	
	template<typename _T, size_t N>
	Forward_List_O(_T (&&init_list)[N])noexcept://move/r-value initializer_list based ctor
		_size(N), tail(nullptr){
		if(N){
			tail=head=GC.empty()?new node(std::move(init_list[0])):GC.pop(std::move(init_list[0]));
			for(size_t i=1;i<N;++i)
				tail=tail->next=GC.empty()?new node(std::move(init_list[i])):GC.pop(std::move(init_list[i]));
		}
	}
#endif
	
	/* Accessors & Mutators */
	T& back(){ return tail->data; }
	const T& back()const{ return tail->data; }
	
	node* back_node(){ return tail; }
	//NOTE: for data safety in read-only object, const overloads aren't provided for node accessors.
	
	size_t size()const{ return _size; }
	
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//emplace_front
		push_front(GC.empty()?new node(std::forward<_T>(new_data)...):
							  GC.pop(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=head;
        head=new_node;
        if(!tail) tail=head;
        ++_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//emplace_back
		push_back(GC.empty()?new node(std::forward<_T>(new_data)...):
							 GC.pop(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	push_back(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
	}
	void push_back(node *new_node){
		tail=(tail?tail->next:head)=new_node;
        ++_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!head) return;
    	node* temp=head->next;
		GC.push(head);
		head=temp;
		if(!head) tail=nullptr;
		--_size;
	}
	node* pop_front(bool){
		if(!head) return nullptr;
    	node* popped=head;
		head=head->next;
		(head?popped->next:tail)=nullptr;
		--_size;
    	return popped;
	}
	
	void pop_back(){//Complexity: O(n)
		if(!head) return;
    	if(head->next){
			node *temp=head;
        	while(temp->next->next)
				temp=temp->next;
			GC.push(temp->next);
        	temp->next=nullptr;
        	tail=temp;
    	}else{
    		GC.push(head);
	        head=tail=nullptr;
		}
        --_size;
    }
    node* pop_back(bool){
		if(!head) return nullptr;
        node* popped;
    	if(head->next){
			node *temp=head;
        	while(temp->next->next)
				temp=temp->next;
			popped=temp->next;
        	temp->next=nullptr;
        	tail=temp;
    	}else{
    		popped=head; 
	        head=tail=nullptr;
		}
		--_size;
    	return popped;
    }/*Side-Note:
		if we preserve previous of tail too, then this pop_back operation can also have O(1) time complexity, 
		but this WILL decrease performance of other operations (since we need to update previous pointer).
	 */
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){//emplace_middle
		push_middle(GC.empty()?new node(std::forward<_T>(new_data)...):
							   GC.pop(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){//Complexity: O(logn)
	    push_middle(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!head)
			head=tail=new_node;
		else if(head->next){
			node *slow_ptr=head, *fast_ptr=head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    slow_ptr->next=new_node;
        }else{
        	tail->next=new_node;
			tail=new_node;
		}
		++_size;
	}
	
	void pop_middle(){//Complexity: O(logn)
	    if(!head) return;
    	if(head->next){
			node *slow_ptr=head,*fast_ptr=head, *prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
	        if(!slow_ptr->next) tail=head;
			GC.push(slow_ptr);
    	}else{
    		GC.push(head);
	        head=tail=nullptr;
		}
    	--_size;
	}
	node* pop_middle(bool){
	    if(!head) return nullptr;
        node* popped;
    	if(head->next){
			node *slow_ptr=head, *fast_ptr=head, *prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
	        if(!slow_ptr->next) tail=head;
			popped=slow_ptr;
    	}else{
    		popped=head;
	        head=tail=nullptr;
		}
		--_size;
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(size_t index, _T&&... new_data){//emplaces node at given index position
		insert(index, GC.empty()?new node(std::forward<_T>(new_data)...):
								 GC.pop(std::forward<_T>(new_data)...));
#else
	void insert(size_t index, const T& new_data){//Complexity: O(n)
		insert(index, GC.empty()?new node(new_data):GC.pop(new_data));
#endif
	}
	void insert(size_t index, node* new_node){
    	if(!index){ push_front(new_node); return; }
    	if(index==_size){ push_back(new_node); return; }
    	if(index>_size){ delete new_node; return; }
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next;
		target->next=new_node;
		new_node->next=temp;
		++_size;
	}
	
#if __cplusplus >= 201103L
	template<bool=true>
#endif
	void erase(size_t index=0){//removes given index position node in O(n) complexity
    	if(!index){ pop_front(); return; }
    	if(index==_size-1){ pop_back(); return; }
    	if(index>=_size) return;
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next;
		GC.push(target->next);
    	target->next=temp;
    	--_size;
	}
	node* erase(size_t index, bool){
		if(!index) return pop_front(true);
		if(index==_size-1) return pop_back(true);
		if(index>=_size) return nullptr;
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next, *popped=target->next;
    	target->next=temp;
    	--_size;
    	return popped;
	}
	void erase(const T& key){//removes targeted node in O(n) complexity
//		if(!head) return;
    	if(key==base::front()){ pop_front(); return; }
    	if(key==back()){ pop_back(); return; }
//		if(!head->next) return;
		node *target=head;
		while(target->next->data!=key){
			target=target->next;
//			if(!target->next) return;
		}
    	node* temp=target->next->next;
		GC.push(target->next);
    	target->next=temp;
    	--_size;
	}//Note: for optimize results, bound exception safeties are removed
	void erase(node *current){
    	if(current==head){ pop_front(); return; }
    	if(current==tail){ pop_back(); return; }
		if(!(current&&head)) return;
		node *previous=head;
		while(previous->next!=current){
			previous=previous->next;
			if(!previous->next) return;
		}
		previous->next=current->next;
		delete current;
		--_size;
	}
	
	void resize(size_t new_size, const T& new_data=T()){//Complexity: O(n)
		while(new_size>_size)
			push_back(GC.empty()?new node(new_data):GC.pop(new_data));
    	while(new_size<_size)
			pop_back();
	}
	
	void unique(){ if(head) unique(head); }//removes consecutive duplicates
	
	//TODO: void remove_all_duplicates(...);//using base::remove_all_duplicates()
	
	void sort(bool direction_flag=true){//slightly improved insertion-sort with O(n^2) complexity
    	void (__FLO::*fp)(node*)=direction_flag?&ascending_sorted_insert:
												&descending_sorted_insert;//function_pointer
		node* current=head;
    	head=tail=nullptr;//disconnecting links to 'current' list
    	while(current){
        	node* temp=current->next;
        	(this->*fp)(current);//calling pointed member function
        	current=temp;
    	}
	}//Note: use when 'move semantics' aren't available for respective type & list has heavy-weight objects
	
#if __cplusplus >= 201103L
	template<typename _T>
	void sorted_insert(_T&& new_data, bool direction_flag=true){//Complexity: O(n)
		sorted_insert(GC.empty()?new node(std::forward<_T>(new_data)):
								 GC.pop(std::forward<_T>(new_data)), direction_flag);
#else
	void sorted_insert(const T& new_data, bool direction_flag=true){
		sorted_insert(GC.empty()?new node(new_data):GC.pop(new_data), direction_flag);
#endif
	}
	void sorted_insert(node* new_node, bool direction_flag=true){
		direction_flag?ascending_sorted_insert(new_node):descending_sorted_insert(new_node);
		++_size;
	}
	
	void reverse(){
		if(_size>1){
			tail=head;
			base::reverse_recursively(head);
		}
	}
	
	void merge(__FLO &other, size_t pos=0){
		if(!other.head||pos>_size) return;//bound exception safety
		if(!pos){//if pos is '0', then directly join head of other to head of 'this'
			other.tail->next=head;
			head=other.head;
		}else if(pos==_size){
			tail->next=other.head;
			tail=other.tail;
		}else{
			node *target=head;
			for(size_t i=1;i<pos;++i)
				target=target->next;
			node *temp=target->next;
			target->next=other.head;
			other.tail->next=temp;
		}
		_size+=other._size;
		other.head=other.tail=nullptr; other._size=0;//set 'other' to null state
	}
	
	void swap_nodes(const T& X, const T& Y){//efficient when datatype 'T' has no 'move semantics' available
		if(X==Y) return;
		node **prevX=nullptr, **prevY=nullptr;
		for(node **head_ref=&head;*head_ref;head_ref=&(*head_ref)->next){
			if((*head_ref)->data==X) prevX=head_ref;
			else if((*head_ref)->data==Y) prevY=head_ref;
		}
		if(prevX&&prevY){
			if(*prevX==tail) tail=*prevY;//if X is tail then set Y as new tail
			else if(*prevY==tail) tail=*prevX;//if Y is tail then set X as new tail
			swap(*prevX, *prevY);
			swap((*prevX)->next, (*prevY)->next);
		}
	}
//	void swap_nodes(const T& X, const T& Y){//slight less efficient version (easy to understand)
//		if(X==Y) return;
//		node *prevX=nullptr, *currX=head;
//		while(currX&&currX->data!=X){
//		    prevX=currX;
//    		currX=currX->next;
//		}
//		node *prevY=nullptr, *currY=head;
//		while(currY&&currY->data!=Y){
//    		prevY=currY;
//    		currY=currY->next;
//		}
//		if(currX&&currY){
//			if(currX==tail) tail=currY;
//			else if(currY==tail) tail=currX;
//			(prevX?prevX->next:head)=currY;
//			(prevY?prevY->next:head)=currX;
//			swap(currX->next, currY->next);
//		}
//	}
	
	void clear(){//O(1) complexity
		if(tail){
			GC.push(head, tail, _size);
			head=tail=nullptr; _size=0;//set to null state
		}
	}
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//destroys all preserved nodes in GC of resepective 'T' type
	static void release_gc(size_t n){ GC.release(n, true); }//destroys 'n' preserved nodes.... 
	
	/* Destructor */
	~Forward_List_O(){ clear(); }
	
	/* Hidden Method */
private:
	void unique(node* temp){
    	if(temp->next){
        	if(temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		if(!temp->next) tail=temp;
        		GC.push(to_delete);
        		--_size;
        		unique(temp);
        	}
        	else unique(temp->next); 
   	 	}
	}
	
	void ascending_sorted_insert(node* new_node){
		if(!head){
			new_node->next=nullptr;
			head=tail=new_node;
		}else if(new_node->data<=head->data){
    	    new_node->next=head;
    	    head=new_node;
    	}else if(new_node->data>=tail->data){
			new_node->next=nullptr;
			tail=tail->next=new_node;
		}else{
    		node *temp=head;
    		while(temp->next->data<new_node->data)
    			temp=temp->next;
    		new_node->next=temp->next;
    		temp->next=new_node;
		}
	}
	void descending_sorted_insert(node* new_node){
		if(!head){
			new_node->next=nullptr;
			head=tail=new_node;
		}else if(new_node->data>=head->data){
    	    new_node->next=head;
    	    head=new_node;
    	}else if(new_node->data<=tail->data){
			new_node->next=nullptr;
			tail=tail->next=new_node;
		}else{
    		node *temp=head;
    		while(temp->next->data>new_node->data)
    			temp=temp->next;
    		new_node->next=temp->next;
    		temp->next=new_node;
		}
	}
};

template<typename T>
garbage_collector<typename Forward_List<T>::node> Forward_List_O<T>::GC(128);//default GC object ctor call
//Note: gets invoked if no explicit specialized static member call is present for respective type

/*specialized static member call format:
template<>
garbage_collector<Forward_List<int>::node> Forward_List_O<int>::GC(256);
*/

#endif
