/** Doubly Linked List (as List) **/
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Safe when accessing elements with accessors (Exception somewhat handled)
	3) All neccessary STL List class 'modifiers' & 'iterators' are provided
	4) Garbage Collector version is also available for improved efficiency in long-run situations
*/
#ifndef LIST_GUARD
#define LIST_GUARD 1

#include "Node.hpp"
#include "../Utilities/Swap.hpp"
#include "../Utilities/Garbage_Collector.hpp"
#include "../Utilities/Reverse_Iterator_Adapter.hpp"

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

/** Standard Minimal Version of STL::list **/
//NOTE: for optimize results, no bound exception safety provided for position based modifiers
template<typename T>
class List{
	typedef List __L;
public:
	typedef DLL_Node<T> node;
	
protected:
	/* Main-Class Attributes */
	static const unsigned int max_capacity=~((unsigned int)0);
    node *head, *tail;
	
public:
	/* Constructors & Assignment Operators */
	List()noexcept://default ctor
		head(nullptr), tail(nullptr){}
	
	List(size_t n, const T& new_data=T())noexcept://fill ctor
		head(nullptr), tail(nullptr){
		if(n&&n<=max_capacity){
			head=tail=new node(new_data);			
			for(node* new_node;--n;tail=tail->next=new_node){
				new_node=new node(new_data);
				new_node->prev=tail;
			}
		}
	}
	
	//copy semantics (deep copy):
	List(const __L &other)noexcept://copy ctor
		head(nullptr), tail(nullptr){
		if(other.head){//1) copy other's data
			head=tail=new node(other.head->data);
			for(node *new_node, *it=other.head->next;it;it=it->next){
				new_node=new node(it->data);
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
		}
    }
    __L& operator=(const __L &other)noexcept{//copy assignment operator
    	if(this==&other) return *this;//self-assignment protection
		clear();//1) clear existing resources
		if(other.head){//2) copy other's data
			head=tail=new node(other.head->data);
			for(node *new_node, *it=other.head->next;it;it=it->next){
				new_node=new node(it->data);
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
		}
        return *this;
    }
#if __cplusplus >= 201103L
	
	//move semantics (shallow copy):
 	List(__L&& other)noexcept://move ctor
  		head(other.head), tail(other.tail){//1) steal other's data
		other.head=nullptr; other.tail=nullptr;//2) set 'other' to null state
	}
	__L& operator=(__L&& other)noexcept{//move assignment operator
  		if(this==&other) return *this;
		clear();//1) clear existing resources
  		head=other.head; tail=other.tail;//2) steal other's data
  		other.head=nullptr; other.tail=nullptr;//3) set 'other' to null state
		return *this;
	}
	
	template<typename _T, size_t N>
	List(_T (&&init_list)[N])noexcept://move/r-value initializer_list based ctor
		head(nullptr), tail(nullptr){
		if(N){
			head=tail=new node(std::move(init_list[0]));
			node* new_node; size_t i=1;
			while(i<N){//constructs doubly linked-list in ascending order
				new_node=new node(std::move(init_list[i++]));
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
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
	
	T& back(){ return tail->data; }
	const T& back()const{ return tail->data; }
	
	node* front_node(){ return head; }
	node* back_node(){ return tail; }
	//NOTE: for data safety in read-only object, const overloads aren't provided for node accessors.
	
	bool empty()const{ return !head; }
	
	/*Important Notes (for ensuring exception safety manually):
		1) use condition 'empty()==false' for 'front' & 'back' accessors.
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
		head=(head?head->prev:tail)=new_node;
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
		new_node->prev=tail;
		tail=(tail?tail->next:head)=new_node;
	}
	
	void pop_front(){//Complexity: O(1)
    	if(!head) return;
    	node* temp=head->next;
		delete head;
		head=temp;
		(head?head->prev:tail)=nullptr;
	}
	node* pop_front(bool){
    	if(!head) return nullptr;
    	node *popped=head;
		head=head->next;
		(head?(head->prev=popped->next):tail)=nullptr;
		return popped;
	}
	
	void pop_back(){//Complexity: O(1)
    	if(!tail) return;
    	node* temp=tail->prev;
		delete tail;
		tail=temp;
		(tail?tail->next:head)=nullptr;
	}
	node* pop_back(bool){
    	if(!tail) return nullptr;
    	node *popped=tail;
		tail=tail->prev;
		(tail?(tail->next=popped->prev):head)=nullptr;
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
		    if(slow_ptr->next){
		    	new_node->next=slow_ptr->next;
				slow_ptr->next->prev=new_node;
			}
			else tail=new_node;
			new_node->prev=slow_ptr;
		    slow_ptr->next=new_node;
		}
		else head=tail=new_node;
	}
	
	void pop_middle(){//Complexity: O(logn)
	    if(!head) return;
    	if(head->next){
			node *slow_ptr=head, *fast_ptr=head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				tail=head;
			delete slow_ptr;
    	}else{
    		delete head;
	        head=tail=nullptr;
		}
	}
	node* pop_middle(bool){
	    if(!head) return nullptr;
        node* popped;
    	if(head->next){
			node *slow_ptr=head, *fast_ptr=head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				tail=head;
			popped=slow_ptr;
			popped->next=popped->prev=nullptr;
    	}else{
    		popped=head;
	        head=tail=nullptr;
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
		(temp?temp->prev:tail)=new_node;
		new_node->next=temp;
		target->next=new_node;
		new_node->prev=target;
	}
	
	void erase(size_t index=0){//removes given index position node in O(n) complexity
    	if(!index){ pop_front(); return; }
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next;
		delete target->next;
    	target->next=temp;
    	(temp?temp->prev:tail)=target;
	}
	node* erase(size_t index, bool){
    	if(!index) return pop_front(true);
		node *target=head;
		for(size_t i=1;i<index;++i)
    		target=target->next;
    	node* temp=target->next->next, *popped=target->next;
    	target->next=temp;
    	(temp?temp->prev:tail)=target;
    	popped->next=popped->prev=nullptr;
    	return popped;
	}
	void erase(node *current){//removes given random node in O(1) complexity
    	if(current==head){ pop_front(); return; }
		if(current==tail){ pop_back(); return; }
//		if(!(head&&current&&current->prev&&current->next)) return;
		//Note: for optimize results, bound exception safeties are removed
		current->prev->next=current->next;
		current->next->prev=current->prev;
		delete current;
	}//Warning: no exception is provided to identify wrong node address
	
	void resize(size_t new_size, const T& new_data=T()){//Complexity: O(n+m)
		if(new_size>max_capacity) return;
		size_t n=size();
		if(new_size>n){
			n=new_size-n;
			while(n--) push_back(new_data);
		}else if(new_size<n){
    		n-=new_size;
    		while(n--) pop_back();
		}
	}
	
	void unique(){ if(head) unique(head); }//removes consecutive duplicates in O(n) complexity
	
	//TODO: void remove_all_duplicates(...);
	
	void sort(bool direction_flag=true){//slightly improved insertion-sort with O(n^2) complexity
    	void (__L::*fp)(node*)=direction_flag?&ascending_sorted_insert:
											  &descending_sorted_insert;//function_pointer
		node* current=head;
    	head=tail=nullptr;//disconnecting links to 'current' list
    	while(current){
        	node* temp=current->next;
        	(this->*fp)(current);//calling pointed member function
        	current=temp;
    	}
	}//Note: use when no 'move semantics' are available for respective type & list has heavy-weight objects
	
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
	
	void reverse(){//Complexity: O(n)
		swap(head, tail);
		for(node *it=head;it;it=it->next)
			swap(it->next, it->prev);
	}
	
	void merge(__L &other, size_t pos=0){
		if(!other.head) return;
		if(!pos){//if pos is '0', then directly join head of other to head of 'this'
			other.tail->next=head;
			head->prev=other.tail;
			head=other.head;
		}else{
			node *target=head;
			for(size_t i=1;i<pos;++i)
				target=target->next;
			node *temp=target->next;
			target->next=other.head;
			other.head->prev=target;
			other.tail->next=temp;
			(temp?temp->prev:tail)=other.tail;
		}
		other.head=other.tail=nullptr;
	}
	
	void swap_nodes(const T& X, const T& Y){//efficient when datatype 'T' has no 'move semantics' available
		if(X==Y) return;//do nothing if X & Y are same
		node *currX=head, *currY=head;
		while(currX&&currX->data!=X)//search for X while keeping track of CurrX
    		currX=currX->next;
		while(currY&&currY->data!=Y)//search for Y while keeping track of CurrY
    		currY=currY->next;
		if(currX&&currY){//do nothing if either X or Y isn't present
			swap(currX->next, currY->next);//swap next ptrs
			(currX->next?currX->next->prev:tail)=currX;
			//if Y is tail then set X as new tail, otherwise join next of Y to X			
			(currY->next?currY->next->prev:tail)=currY;
			//if X is tail then set Y as new tail, otherwise join next of X to Y
			swap(currX->prev, currY->prev);//swap previous ptrs
			(currX->prev?currX->prev->next:head)=currX;
			//if Y is head then set X as new head, otherwise join prev of Y to X
			(currY->prev?currY->prev->next:head)=currY;
			//if X is head then set Y as new head, otherwise join prev of X to Y
		}
	}
	void swap_data(const T& X, const T& Y){//efficient when datatype 'T' has 'move semantics' available
		if(X==Y) return;
		node *currX=head, *currY=head;
		while(currX&&currX->data!=X)
    		currX=currX->next;
		while(currY&&currY->data!=Y)
    		currY=currY->next;
    	if(currX&&currY)
    		swap(currX->data, currY->data);//swap data of targeted nodes directly
	}
	
	void clear(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
		tail=nullptr;
	}
	
	/* Non-Modifiers */
	size_t size()const{//counts total nodes/values in O(n) complexity
		size_t i=0;
		for(node *it=head;it;it=it->next) ++i;
		return i;
	}
    void traverse(bool direction_flag=false)const{
    	if(!head){ std::cout<<"List is empty!\n"; return; }
    	if(direction_flag)
			for(node* it=tail;it;it=it->prev)//traverses in descending order
    			std::cout<<it->data<<' ';
		else
			for(node *it=head;it;it=it->next)//traverses in ascending order (default)
    			std::cout<<it->data<<' ';
		std::cout<<'\n';
	}
	
	/* Comparators */
	bool operator==(const __L& other)const{
		node *iter1=head, *iter2=other.head;
		while(iter1&&iter2){
			if(iter1->data!=iter2->data) return false;
			iter1=iter1->next, iter2=iter2->next;
		}
  		return iter1==iter2;
	}
	bool operator!=(const __L& other)const{ return !(*this==other); }
	
	bool operator<(const __L& other)const{
  		node *iter1=head, *iter2=other.head; 
  		while(iter1){
  			if(!iter2||iter1->data>iter2->data) return false;
  			else if(iter1->data<iter2->data) return true;
  			iter1=iter1->next, iter2=iter2->next;
		}
		return iter1!=iter2;
	}
    bool operator>(const __L& other)const{ return other<*this; }
	bool operator<=(const __L& other)const{ return !(other<*this); }
	bool operator>=(const __L& other)const{ return !(*this<other); }
	
	/* Iterators */
	template<typename DRT>//data return type (i.e. for handling const & non-const both)
	class L_Iterator{//traverses in forward direction
		typedef L_Iterator __self;
	protected:
		node* ptr;
	public:
		L_Iterator(node* ptr=nullptr)noexcept://default ctor
			ptr(ptr){}
		//accessors:
		DRT& operator*()const{ return ptr->data; }
		DRT& operator[](__int64 n)const{
			node* it=ptr;
			if(n>0)
				while(n--) it=it->next;
			else
				while(n++) it=it->prev;
			return it->data;
		}
    	//modifiers:
		__self& operator++(){ ptr=ptr->next; return *this; }//pre-increment
    	__self& operator--(){ ptr=ptr->prev; return *this; }
		__self operator++(int){ __self temp(*this); ptr=ptr->next; return temp; }//post-increment
		__self operator--(int){ __self temp(*this); ptr=ptr->prev; return temp; }
		__self& operator+=(size_t n){ while(n--) ptr=ptr->next; return *this; }
		__self& operator-=(size_t n){ while(n--) ptr=ptr->prev; return *this; }
		__self operator+(size_t n)const{ node* it=ptr; while(n--) it=it->next; return __self(it); }
		__self operator-(size_t n)const{ node* it=ptr; while(n--) it=it->prev; return __self(it); }
		//comparators:
		bool operator==(const __self& other)const{ return ptr==other.ptr; }
		bool operator!=(const __self& other)const{ return ptr!=other.ptr; }
    };
	template<typename DRT>
	class L_Reverse_Iterator:
		public L_Iterator<DRT>{//traverses in reverse direction
		//simplified type names:
		typedef L_Reverse_Iterator __self;
		typedef L_Iterator<DRT> base;
		
		using base::ptr;
	public:
    	L_Reverse_Iterator(node* ptr=nullptr)noexcept://default ctor
			base(ptr){}
		DRT& operator[](__int64 n)const{//overloaded accessor
			node* it=ptr;
			if(n>0)
				while(n--) it=it->prev;
			else
				while(n++) it=it->next;
			return it->data;
		}
    	//overloaded modifiers:
    	__self& operator++(){ ptr=ptr->prev; return *this; }
    	__self& operator--(){ ptr=ptr->next; return *this; }
		__self operator++(int){ __self temp(*this); ptr=ptr->prev; return temp; }
		__self operator--(int){ __self temp(*this); ptr=ptr->next; return temp; }
		__self& operator+=(size_t n){ while(n--) ptr=ptr->prev; return *this; }
		__self& operator-=(size_t n){ while(n--) ptr=ptr->next; return *this; }
		__self operator+(size_t n)const{ node* it=ptr; while(n--) it=it->prev; return __self(it); }
		__self operator-(size_t n)const{ node* it=ptr; while(n--) it=it->next; return __self(it); }
    };
    
    //available list iterator objects (const/non_const):
	typedef L_Iterator<T> iterator;
	typedef L_Iterator<const T> const_iterator;
	
	typedef L_Reverse_Iterator<T> r_iterator;
	typedef L_Reverse_Iterator<const T> const_r_iterator;
    
    //available list iterator methods (return rvalue/temporary iterator):
	iterator begin(){ return iterator(head); }//points to first element
	iterator end(){ return iterator(nullptr); }//points end of list i.e. null
	
	const_iterator begin()const{ return const_iterator(head); }//const (read only) version
	const_iterator end()const{ return const_iterator(nullptr); }
	
	r_iterator rbegin(){ return r_iterator(tail); }//points to last element
	r_iterator rend(){ return r_iterator(nullptr); }//points end of list i.e. null
	
	const_r_iterator rbegin()const{ return const_r_iterator(tail); }//const (read only) version
	const_r_iterator rend()const{ return const_r_iterator(nullptr); }
	
#if __cplusplus >= 201103L
	//reversely traverse list using these methods (inside range-based loop):
	reverse_iterator_adapter<__L, r_iterator> r_iterator_adapter(){ 
		return reverse_iterator_adapter<__L, r_iterator>(*this);
	}
	reverse_iterator_adapter<const __L, r_iterator> r_iterator_adapter()const{
		return reverse_iterator_adapter<const __L, r_iterator>(*this);
	}
#endif
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out, const __L& self){//traverses in ascending order
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in, __L& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
	
	/* Destructor (a.k.a. dtor) */
	~List(){ clear(); }
	
	/* Hidden Methods */
private:
	void unique(node* temp){//works best for sorted data
    	if(temp->next){
        	if(temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		(temp->next?temp->next->prev:tail)=temp;
				delete to_delete;
        		unique(temp);
        	}
        	else unique(temp->next);//advances only if no deletion
   	 	}
	}
	
protected:
	void ascending_sorted_insert(node* new_node){
		if(!head){
			new_node->prev=new_node->next=nullptr;
			head=tail=new_node;
		}else if(new_node->data<=head->data){
    	    new_node->prev=nullptr;
    	    new_node->next=head;
    	    head=head->prev=new_node;
    	}else if(new_node->data>=tail->data){
    		new_node->next=nullptr;
        	new_node->prev=tail;
        	tail=tail->next=new_node;
    	}else{
    		node *temp=head->next;
    		while(temp->data<new_node->data)
    			temp=temp->next;
    		temp->prev->next=new_node;
    		new_node->prev=temp->prev;
    		temp->prev=new_node;
    		new_node->next=temp;
		}
	}
	void descending_sorted_insert(node* new_node){
	    if(!head){
			new_node->prev=new_node->next=nullptr;
			head=tail=new_node;
		}else if(new_node->data>=head->data){
    	    new_node->prev=nullptr;
    	    new_node->next=head;
    	    head=head->prev=new_node;
    	}else if(new_node->data<=tail->data){
    		new_node->next=nullptr;
        	new_node->prev=tail;
        	tail=tail->next=new_node;
    	}else{
    		node *temp=tail->prev;
    		while(temp->data<new_node->data)
    			temp=temp->prev;
    		temp->next->prev=new_node;
    		new_node->next=temp->next;
    		temp->next=new_node;
    		new_node->prev=temp;
		}
	}
};

/** Optimized Version with Garbage Collector **/
template<typename T>
class List_O:
	public List<T>{
	
	/* Simplified Type Names (for List_O) */
	typedef List_O __LO;
	typedef List<T> base;
	typedef typename base::node node;
	
	using base::head;
	using base::tail;
	
	/* Main-Class Attributes */
	static garbage_collector<node> GC;
	size_t _size;
	
public:
	/* Constructors & Assignment Operators */
	List_O()noexcept://default ctor
		_size(0){}
	
	List_O(size_t n, const T& new_data=T())noexcept://fill ctor
		_size(n<=base::max_capacity?n:throw){
		if(n){
			head=tail=GC.empty()?new node(new_data):GC.pop(new_data);
			for(node* new_node;--n;tail=tail->next=new_node){
				new_node=GC.empty()?new node(new_data):GC.pop(new_data);
				new_node->prev=tail;
			}
		}
	}
	
	//copy semantics (deep copy):
	List_O(const __LO &other)noexcept://copy ctor
    	_size(other._size){
    	if(other.head){
			head=tail=GC.empty()?new node(other.head->data):GC.pop(other.head->data);
			for(node *new_node, *it=other.head->next;it;it=it->next){
				new_node=GC.empty()?new node(it->data):GC.pop(it->data);
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
		}
    }
    __LO& operator=(const __LO &other)noexcept{//copy assignment operator
    	if(this==&other) return *this;
		clear();
        if(other.head){
        	_size=other._size;
			head=tail=GC.empty()?new node(other.head->data):GC.pop(other.head->data);
			for(node *new_node, *it=other.head->next;it;it=it->next){
				new_node=GC.empty()?new node(it->data):GC.pop(it->data);
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
		}
        return *this;
    }
#if __cplusplus >= 201103L
	
	//move semantics (shallow copy):
 	List_O(__LO&& other)noexcept://move ctor
  		_size(other._size), base(std::move(other)){
		other._size=0;
	}
	__LO& operator=(__LO&& other)noexcept{//move assignment operator
  		if(this==&other) return *this;
		clear();
  		head=other.head; tail=other.tail; _size=other._size;
  		other.head=other.tail=nullptr; other._size=0;
		return *this;
	}
	
	template<typename _T, size_t N>
	List_O(_T (&&init_list)[N])noexcept://move/r-value initializer_list based ctor
		_size(N<=base::max_capacity?N:throw){
		if(N){
			head=tail=GC.empty()?new node(std::move(init_list[0])):GC.pop(std::move(init_list[0]));
			node* new_node; size_t i=1;
			while(i<N){
				new_node=GC.empty()?new node(std::move(init_list[i++])):GC.pop(std::move(init_list[i++]));
				new_node->prev=tail;
				tail=tail->next=new_node;
			}
		}
	}
#endif
    
    /* Accessor */
    size_t size()const{ return _size; }
    
	/* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//emplace_front, direct initialization is possible
		base::push_front(GC.empty()?new node(std::forward<_T>(new_data)...):
									GC.pop(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		base::push_front(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
		++_size;
	}
    void push_front(node* new_node){ base::push_front(new_node); ++_size; }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//emplace_back
		base::push_back(GC.empty()?new node(std::forward<_T>(new_data)...):
							 	   GC.pop(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	base::push_back(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
		++_size;
	}
	void push_back(node* new_node){ base::push_back(new_node); ++_size; }
	
	void pop_front(){//Complexity: O(1)
    	if(!head) return;
    	node* temp=head->next;
		GC.push(head);
		head=temp;
		(head?head->prev:tail)=nullptr;
		--_size;
	}
	node* pop_front(bool){
		if(head) --_size;
    	return base::pop_front(true);
	}
	
	void pop_back(){//Complexity: O(1)
    	if(!tail) return;
    	node* temp=tail->prev;
		GC.push(tail);
		tail=temp;
		(tail?tail->next:head)=nullptr;
		--_size;
	}
	node* pop_back(bool){
		if(tail) --_size;
    	return base::pop_back(true);
	}
    
#if __cplusplus >= 201103L
 template<typename... _T>
	void push_middle(_T&&... new_data){//emplace_middle
		base::push_middle(GC.empty()?new node(std::forward<_T>(new_data)...):
							   		 GC.pop(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){//Complexity: O(logn)
	    base::push_middle(GC.empty()?new node(new_data):GC.pop(new_data));
#endif
		++_size;
	}
	void push_middle(node *new_node){ base::push_middle(new_node); ++_size; }
	
	void pop_middle(){//Complexity: O(logn)
	    if(!head) return;
    	if(head->next){
			node *slow_ptr=head, *fast_ptr=head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				tail=head;
			GC.push(slow_ptr);
    	}else{
    		GC.push(head);
	        head=tail=nullptr;
		}
		--_size;
	}
	node* pop_middle(bool){
		if(head) --_size;
    	return base::pop_middle(true);
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
		temp->prev=new_node;
		new_node->next=temp;
		target->next=new_node;
		new_node->prev=target;
		++_size;
	}
	
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
    	temp->prev=target;
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
    	temp->prev=target;
    	popped->next=popped->prev=nullptr;
		--_size;
    	return popped;
	}
	void erase(node *current){//removes given random node in O(1) complexity
		if(current==head){ pop_front(); return; }
		if(current==tail){ pop_back(); return; }
//		if(!(head&&current&&current->prev&&current->next)) return;
		//Note: for optimize results, bound exception safeties are removed
		current->prev->next=current->next;
		current->next->prev=current->prev;
		GC.push(current);
		--_size;
	}
	
	void resize(size_t new_size, const T& new_data=T()){//Complexity: O(n)
		if(new_size>base::max_capacity) return;
		while(new_size>_size)
			push_back(GC.empty()?new node(new_data):GC.pop(new_data));
		while(new_size<_size)
			pop_back();
	}
	
	void unique(){ if(head) unique(head); }
	
	//TODO: void remove_all_duplicates(...);//using base::remove_all_duplicates()
	
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
		direction_flag?base::ascending_sorted_insert(new_node):
					   base::descending_sorted_insert(new_node);
		++_size;
	}
	
	void reverse(){ if(_size>1) base::reverse(); }//Complexity: O(n)
	
	void merge(__LO &other, size_t pos=0){
		if(!other.head||pos>_size) return;//bound exception safety
		if(!pos){
			other.tail->next=head;
			head->prev=other.tail;
			head=other.head;
		}else if(pos==_size){
			tail->next=other.head;
			other.head->prev=tail;
			tail=other.tail;
		}else{
			node *target=head;
			for(size_t i=1;i<pos;++i)
				target=target->next;
			node *temp=target->next;
			target->next=other.head;
			other.head->prev=target;
			other.tail->next=temp;
			temp->prev=other.tail;
		}
		_size+=other._size;
		other.head=other.tail=nullptr; other._size=0;//set 'other' to null state
	}
	
	void clear(){//O(1) complexity
		if(head){
			GC.push(head, tail, _size);
			head=tail=nullptr; _size=0;//set to null state
		}
	}
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//destroys all preserved nodes in GC of resepective 'T' type
	static void release_gc(size_t n){ GC.release(n, true); }//destroys 'n' preserved nodes....
	
	/* Destructor */
	~List_O(){ clear(); }
	
	/* Hidden Methods */
private:
	void unique(node* temp){
    	if(temp->next){
        	if(temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		(temp->next?temp->next->prev:tail)=temp;
				GC.push(to_delete);
        		unique(temp);
        	}
        	else unique(temp->next);
   	 	}
	}
};

template<typename T>
garbage_collector<typename List<T>::node> List_O<T>::GC(128);//default GC object ctor call
//Note: gets invoked if no explicit specialized static member call is present for respective type

/*specialized static member call format:
template<>
garbage_collector<List<int>::node> List_O<int>::GC(256);
*/

#endif
