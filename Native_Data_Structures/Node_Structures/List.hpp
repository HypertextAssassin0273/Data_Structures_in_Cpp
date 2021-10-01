/* List as Doubly Linked-List (same as STL::list) */
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Concept of Garbage Collector is also implemented to improve efficiency of program in some specific cases
	3) Safe when accessing elements with accessors (Exception somewhat handled)
	4) All neccessary STL List class 'modifiers' & 'iterators' are provided
*/
#ifndef LIST_GUARD
#define LIST_GUARD 1

#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif


/** Base Class for List (i.e. Doubly Linked-List) **/
template<typename T>
class List_Base{//i.e. holds all common functionalities of child classes
public:
	struct node{
	    T data;
    	node *next,*prev;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr),prev(nullptr){}
    #else
		template<typename... _T>
		node(_T&&... data)noexcept://i.e. variadic template & emplaced ctor
			data{std::forward<_T>(data)...},//i.e. perfect forwarding
			next(nullptr),prev(nullptr){}
	#endif
		
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
	static const unsigned int max_capacity=~((unsigned int)0);
    node *head,*tail;
	size_t _size;
	
	/* Constructor */
	List_Base(node* head=nullptr,node* tail=nullptr,const size_t& _size=0)noexcept:
		head(head),tail(tail),_size(_size){}
	
	/* Accessors & Mutators */
public:
#if __cplusplus >= 201103L
	template<typename... _T>
	node* new_node(_T&&... new_data)const{ return new node(std::forward<_T>(new_data)...); }
#else
	node* new_node(const T& new_data)const{ return new node(new_data); }
#endif
    T& operator[](const size_t& n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		if(n==_size-1)
			return tail->data;
		node* it=head;
		for(size_t i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& front()const{
		if (head)
			return head->data;
		throw false;
	}
	T& back()const{
		if (tail)
			return tail->data;
		throw false;
	}
	node* front_node()const{ return head; }
	node* back_node()const{ return tail; }
	size_t size()const{ return _size; }
	bool empty()const{ return head?false:true; }
	
	
	/* Modifiers */
	void sort(bool direction_flag=true){//i.e. slightly improved insertion-sort
    	node* current=head;
    	head=tail=nullptr;//i.e. disconnecting links to 'current' list
    	while (current){
        	node* temp=current->next;
        	current->prev=current->next=nullptr;//i.e. disconnecting links to 'current' list
        	if(direction_flag)
				ascending_sorted_insert(current);
			else
				descending_sorted_insert(current);
        	current=temp;
    	}
	}
	
	void ascending_sorted_insert(node* new_node){
	    if (!head){
	    	head=tail=new_node;
	    	return;
		}
  		if(new_node->data<head->data){
    	    head->prev=new_node;
    	    new_node->next=head;
    	    head=new_node;
    	    return;
    	}
		if(new_node->data>tail->data){
        	new_node->prev=tail;
        	tail->next=new_node;
        	tail=new_node;
        	return;
    	}
    	node *temp=head->next;
    	while (temp->data<new_node->data)
    		temp=temp->next;
    	temp->prev->next=new_node;
    	new_node->prev=temp->prev;
    	temp->prev=new_node;
    	new_node->next=temp;
	}
	void descending_sorted_insert(node* new_node){
	    if (!head){
	    	head=tail=new_node;
	    	return;
		}
  		if(new_node->data>head->data){
    	    head->prev=new_node;
    	    new_node->next=head;
    	    head=new_node;
    	    return;
    	}
		if(new_node->data<tail->data){
        	new_node->prev=tail;
        	tail->next=new_node;
        	tail=new_node;
        	return;
    	}
    	node *temp=tail->prev;
    	while (temp->data<new_node->data)
    		temp=temp->prev;
    	temp->next->prev=new_node;
    	new_node->next=temp->next;
    	temp->next=new_node;
    	new_node->prev=temp;
	}
	
	void reverse(){
		if(!head||!head->next)
			return;
		node* temp=head;
		head=tail;
		tail=temp;
		for(node *it=head;it;it=it->next){
    		temp=it->next;
    		it->next=it->prev;
    		it->prev=temp;
		}
	}
	
	void merge(List_Base &other,const size_t& pos=0){
		if(!other.head||pos<0||pos>_size)
			return;//i.e. do nothing if 'other' have no nodes or size exceeds the given pos
		node *temp=nullptr;
		if(!pos){//i.e. if pos is '0', then directly join head of other to head of 'this'
			other.tail->next=head;
			head->prev=other.tail;
			head=other.head;
		}
		else if(pos==_size){
			tail->next=other.head;
			other.head->prev=tail;
			tail=other.tail;
		}
		else{
			node *temp2=head;
			for(int i=1;i<pos;++i)
				temp2=temp2->next;
			temp=temp2->next;
			temp2->next=other.head;
			other.head->prev=temp2;
			other.tail->next=temp;
			temp->prev=other.tail;
		}
		_size+=other._size;
		other.head=other.tail=nullptr;
		other._size=0;
	}
	
	/* Non-Modifiers */
    void traverse_forward()const{
    	if(!head){
    		std::cout<<"List is empty!"<<'\n';
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
	
	/* Comparators */
	bool operator==(const List_Base& other)const{
		if(other._size!=_size)
			return false;
		for (node *iter1=head,*iter2=other.head;iter1&&iter2;iter1=iter1->next,iter2=iter2->next)
    		if (iter1->data!=iter2->data)
      			return false;
  		return true;
	}
	bool operator!=(const List_Base& other)const{ return !(*this==other); }
	
	bool operator<(const List_Base& other)const{
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
    bool operator>(const List_Base& other)const{ return other<*this; }
	bool operator<=(const List_Base& other)const{ return !(other<*this); }
	bool operator>=(const List_Base& other)const{ return !(*this<other); }
	
	/* Iterators */
	struct _iterator{//i.e. forward_iterator
    	_iterator(node* ptr=nullptr)noexcept://i.e. ctor
			ptr(ptr){}
    	
		node& operator*()const{ return *ptr; }//i.e. accessor
    	
    	//i.e. modifiers
		_iterator& operator++(){ ptr=ptr->next; return *this; }
    	_iterator& operator--(){ ptr=ptr->prev; return *this; }
		_iterator operator++(int){ _iterator temp(*this); ptr=ptr->next; return temp; }
		_iterator operator--(int){ _iterator temp(*this); ptr=ptr->prev; return temp; }
		
		//i.e. comparators
		bool operator==(const _iterator& other)const{ return ptr==other.ptr; }
		bool operator!=(const _iterator& other)const{ return ptr!=other.ptr; }
	private:
		node* ptr;
    };
	struct _r_iterator:public _iterator{//i.e. reverse_iterator
    	_r_iterator(node* ptr=nullptr)noexcept:
			base(ptr){}
    	
    	//i.e. overloaded modifiers
    	_r_iterator& operator++(){ base::ptr=base::ptr->prev; return *this; }
    	_r_iterator& operator--(){ base::ptr=base::ptr->next; return *this; }
		_r_iterator operator++(int){ _r_iterator temp(*this); base::ptr=base::ptr->prev; return temp; }
		_r_iterator operator--(int){ _r_iterator temp(*this); base::ptr=base::ptr->next; return temp; }
	private:
		typedef _iterator base;
    };
    
	_iterator begin()const{ return _iterator(head); }
	_iterator end()const{ return _iterator(nullptr); }
	_r_iterator rbegin()const{ return _r_iterator(tail); }
	_r_iterator rend()const{ return _r_iterator(nullptr); }
	
	/* Overloaded 'cin/cout' Methods */
	friend std::ostream& operator<<(std::ostream& out,const List_Base& self){//i.e. same as traverse_forward
		for(node *it=self.head;it;it=it->next)
    		out<<it->data<<' ';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,List_Base& self){//Note: better for updating values
		for(node *it=self.head;it;it=it->next)
    		in>>it->data;
		return in;
	}
};


template<typename T,bool=false>
class List;//i.e. forward declaration (for template specialization)


/** Standard Minimal Version of STL::list (default) **/
template<typename T>
class List<T,false>:public List_Base<T>{
	typedef List_Base<T> base;
public:
	typedef typename base::node node;

	/* Constructors */
	List(const size_t& n=0)noexcept{//i.e. default ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	List(const size_t& n,_T&&... new_data)noexcept{//i.e. emplaced fill ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	List(const size_t& n,const T& new_data)noexcept{//i.e. fill ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
				push_back(new_data);
	}
#endif
	List(const List &other)noexcept{//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    List& operator=(const List &other)noexcept{//i.e. copy assignment operator
    	if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
        }
        return *this;
    }
#if __cplusplus >= 201103L
 	List(List&& other)noexcept://i.e. move ctor
  		base(other.head,other.tail,other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	List& operator=(List&& other)noexcept{//i.e. move assignment operator
  		if(this!=&other){
			clear();//1) clear existing resources
  			base::head=other.head; base::tail=other.tail; base::_size=other._size;//2) steal other's data
  			other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
  		}
		return *this;
	}
	List(std::initializer_list<T> list)noexcept{//i.e.initializer_list based ctor
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	
    /* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. emplace_front, direct initialization is possible
		push_front(new node(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
#endif
	}
	void push_front(node* new_node){
		new_node->next=base::head;
		if(base::head)
			base::head->prev=new_node;
		else
			base::tail=new_node;
		base::head=new_node;
		++base::_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//i.e. emplace_back
		push_back(new node(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	push_back(new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!base::tail)//i.e. anyone of them can be used to check
    		base::head=base::tail=new_node;
        else{
			new_node->prev=base::tail;
			base::tail->next=new_node;
			base::tail=new_node;
        }
        ++base::_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!base::head) return;
    	if (!base::head->next){
			delete base::head;
	        base::head=base::tail=nullptr;
    	}
    	else{
    		node *temp=base::head->next;
			delete base::head;
    		base::head=temp;
    		base::head->prev=nullptr;
    	}
    	--base::_size;
	}
	node* pop_front(bool){
    	if(!base::head) return nullptr;
    	node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head; 
	        base::head=base::tail=nullptr;
    	}
    	else{
    		node *temp=base::head->next;
   			popped=base::head;
			popped->next=nullptr;
    		base::head=temp;
    		base::head->prev=nullptr;
    	}
    	--base::_size;
    	return popped;
	}
	
	void pop_back(){//Complexity: O(1)
		if(!base::tail) return;
    	if (!base::tail->prev){
			delete base::tail;
	        base::head=base::tail=nullptr;
    	}
    	else{
			node *temp=base::tail->prev;
			delete base::tail;
    		base::tail=temp;
    		base::tail->next=nullptr;
		}
    	--base::_size;
    }
    node* pop_back(bool){
		if(!base::tail) return nullptr;
        node* popped=nullptr;
    	if (!base::tail->prev){
				popped=base::tail; 
	        base::head=base::tail=nullptr;
    	}
    	else{
			node *temp=base::tail->prev;
			popped=base::tail;
			popped->prev=nullptr;
    		base::tail=temp;
    		base::tail->next=nullptr;
		}
    	--base::_size;
    	return popped;
    }
    
#if __cplusplus >= 201103L
 template<typename... _T>
	void push_middle(_T&&... new_data){//i.e. emplace_middle in O(logn) time
		push_middle(new node(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){
	    push_middle(new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!base::head)
			base::head=base::tail=new_node;
        else if(!base::head->next){
			new_node->prev=base::tail;
			base::tail->next=new_node;
			base::tail=new_node;
        }
        else{
    	    node *slow_ptr=base::head,*fast_ptr=base::head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    new_node->prev=slow_ptr;
		    slow_ptr->next=new_node;
		    new_node->next->prev=new_node;
		}
	    ++base::_size;
	}
	
	void pop_middle(){//i.e. pop_middle in O(logn) time
	    if(!base::head) return;
    	if (!base::head->next){
			delete base::head;
	        base::head=base::tail=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				base::tail=base::head;
			delete slow_ptr;
		}
    	--base::_size;
	}
	node* pop_middle(bool){
	    if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head;
	        base::head=base::tail=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				base::tail=base::head;
			popped=slow_ptr;
		}
    	--base::_size;
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(__int64 index,_T&&... new_data){//i.e. emplace randomly in O(n) time
		insert(index,new node(std::forward<_T>(new_data)...));
#else
	void insert(__int64 index,const T& new_data){
		insert(index,new node(new_data));
#endif
	}
	void insert(const size_t& index,node* new_node){
		if(index<0||index>base::_size) return;
    	if(!index){ push_front(new_node); return; }
		if(index==base::_size){ push_back(new_node); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
    	temp->next=new_node;
    	temp2->prev=temp->next;
		temp->next->next=temp2;
		temp->next->prev=temp;
		++base::_size;
	}
	
	void erase(const size_t& index){//i.e. removes node randomly in O(n) time
		if(index<0||index>=base::_size) return;
    	if(!index){ pop_front(); return; }
		if(index==base::_size-1){ pop_back(); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
		delete temp->next;
    	temp->next=temp2;
    	temp2->prev=temp;
    	--base::_size;
	}
	node* erase(const size_t& index,bool){
		if(index<0||index>=base::_size) return nullptr;
    	if(!index) return pop_front(true);
		if(index==base::_size-1) return pop_back(true);
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next,*popped=nullptr;
		popped=temp->next;
    	temp->next=temp2;
    	temp2->prev=temp;
    	--base::_size;
    	return popped;
	}
	void erase(node *current){//i.e. removes node randomly in O(1) time if current node is given
		if(!(current&&base::head)) return;//Warning: no exception is possible to efficiently identify wrong node address
    	if(current==base::head){ pop_front(); return; }
		if(current==base::tail){ pop_back(); return; }
		current->prev->next=current->next;
		current->next->prev=current->prev;
		delete current;
		--base::_size;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void resize(const size_t& new_size,_T&&... new_data){//i.e. emplaced_resize
#else
	void resize(const size_t& new_size,const T& new_data=T()){
#endif
		if (new_size<0||new_size>base::max_capacity)
			return;
		if(new_size>base::_size)
			while(new_size>base::_size)
			#if __cplusplus >= 201103L
				push_back(std::forward<_T>(new_data)...);
    		#else
				push_back(new_data);
			#endif
    	else
    		while(new_size<base::_size)
				pop_back();
	}
	
	void unique(){
		if (base::head&&base::head->next)//i.e. do nothing if size < 2
        	unique(base::head);
	}
private: //i.e. hidden method
	void unique(node* temp){//i.e. works best for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		if(temp->next)
					temp->next->prev=temp;
				else
					base::tail=temp;
				delete to_delete;
        		--base::_size;
        		unique(temp);
        	}
        	else //i.e. advances only if no deletion
	            unique(temp->next); 
   	 	}
	}
	
public:
#if __cplusplus >= 201103L
	template<typename _T>
	void sorted_insert(_T&& new_data,bool direction_flag=true){
		sorted_insert(new node(std::forward<_T>(new_data)),direction_flag);
	}
#endif
	void sorted_insert(const T& new_data,bool direction_flag=true){
		sorted_insert(new node(new_data),direction_flag);
	}
	void sorted_insert(node* new_node,bool direction_flag=true){
		direction_flag?ascending_sorted_insert(new_node):descending_sorted_insert(new_node);
		++base::_size;
	}
	
	void clear(){
		node* temp;
		while(base::head){
	   		temp=base::head->next;
	    	delete base::head;
    		base::head=temp;	
		}
		base::tail=nullptr;
		base::_size=0;
	}
	
 	/* Iterators */
	typedef typename base::_iterator iterator;
	typedef typename base::_r_iterator r_iterator;
#if __cplusplus >= 201103L
private:
	struct reverse_adapter{//i.e. defined to use reverse_iterator on 'range-based' loop
		reverse_adapter(const List& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const List& ref;
	};
public:
	//i.e. reversely traverse List without changing it (inside range-based loop)
	reverse_adapter reverse_iterator()const{ return reverse_adapter(*this); }
#endif
	
	~List(){ clear(); }//i.e. dtor
};


/** Optimized Version with Garbage Collector **/
template<typename T>
class List<T,true>:public List_Base<T>{
	typedef List_Base<T> base;
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
			if(_size>=base::max_capacity)
				release();
		}
		void push(node* new_head,node* new_tail,size_t new_size){//i.e. complexity O(1)
			new_tail->next=ptr;
			ptr=new_head;
			_size+=new_size;
			if(_size>=base::max_capacity)
				release();
		}
		//i.e. useful when a list is destroyed & its' nodes need to transfer to garbage collector at O(1) complexity
	#if __cplusplus >= 201103L
		template<typename... _T>
		node* pop(_T&&... new_data){//i.e. complexity O(1)
	#else
		node* pop(const T& new_data){
    #endif
			if(!ptr) return nullptr;
	    	node *popped=ptr;
    		ptr=ptr->next;
    		--_size;
    	#if __cplusplus >= 201103L
    		popped->data={std::forward<_T>(new_data)...};
    	#else
    		popped->data=new_data;
    	#endif
    		popped->next=popped->prev=nullptr;
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
			_size=0;
		}
		~garbage_collector(){ clear(); }
	};
	
	/* Class Attribute (additional) */
	static garbage_collector GC;

public:
	/* Constructors */
	List(const size_t& n=0)noexcept{//i.e. default ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	List(const size_t& n,_T&&... new_data)noexcept{//i.e. emplaced fill ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	List(const size_t& n,const T& new_data)noexcept{//i.e. fill ctor
		if(n<=base::max_capacity)
			while(n>base::_size)
				push_back(new_data);
	}
#endif
	List(const List &other)noexcept{//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    List& operator=(const List &other)noexcept{//i.e. copy assignment func.
    	if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
        	for(node *it=other.head;it;it=it->next)
        	   	push_back(it->data);//2) copy other's data
        }
        return *this;
    }
#if __cplusplus >= 201103L
 	List(List&& other)noexcept://i.e. move ctor
  		base(other.head,other.tail,other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	List& operator=(List&& other)noexcept{//i.e. move assignment func
  		if(this!=&other){
			clear();//1) clear existing resources
  			base::head=other.head; base::tail=other.tail; base::_size=other._size;//2) steal other's data
  			other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
  		}
		return *this;
	}
	List(std::initializer_list<T> list)noexcept{//i.e.initializer_list based ctor
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	
    /* Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. emplace_front, direct initialization is possible
		push_front(GC.ptr?GC.pop(std::forward<_T>(new_data)...):new node(std::forward<_T>(new_data)...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_front(node* new_node){
		new_node->next=base::head;
		if(base::head)
			base::head->prev=new_node;
		else
			base::tail=new_node;
		base::head=new_node;
		++base::_size;
    }
    
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//i.e. emplace_back
		push_back(GC.ptr?GC.pop(std::forward<_T>(new_data)...):new node(std::forward<_T>(new_data)...));
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	push_back(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!base::tail)//i.e. anyone of them can be used to check
    		base::head=base::tail=new_node;
        else{
			new_node->prev=base::tail;
			base::tail->next=new_node;
			base::tail=new_node;
        }
        ++base::_size;
	}
	
    void pop_front(){//Complexity:O(1)
    	if(!base::head) return;
    	if (!base::head->next){
			GC.push(base::head);
	        base::head=base::tail=nullptr;
    	}
    	else{
    		node *temp=base::head->next;
			GC.push(base::head);
    		base::head=temp;
    		base::head->prev=nullptr;
    	}
    	--base::_size;
	}
	node* pop_front(bool){
    	if(!base::head) return nullptr;
    	node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head; 
	        base::head=base::tail=nullptr;
    	}
    	else{
    		node *temp=base::head->next;
   			popped=base::head;
			popped->next=nullptr;
    		base::head=temp;
    		base::head->prev=nullptr;
    	}
    	--base::_size;
    	return popped;
	}
	
	void pop_back(){//Complexity: O(1)
		if(!base::tail) return;
    	if (!base::tail->prev){
			GC.push(base::tail);
	        base::head=base::tail=nullptr;
    	}
    	else{
			node *temp=base::tail->prev;
			GC.push(base::tail);
    		base::tail=temp;
    		base::tail->next=nullptr;
		}
    	--base::_size;
    }
	node* pop_back(bool){
		if(!base::tail) return nullptr;
        node* popped=nullptr;
    	if (!base::tail->prev){
			popped=base::tail;
	        base::head=base::tail=nullptr;
    	}
    	else{
			node *temp=base::tail->prev;
			popped=base::tail;
			popped->prev=nullptr;
    		base::tail=temp;
    		base::tail->next=nullptr;
		}
    	--base::_size;
    	return popped;
    }
    
#if __cplusplus >= 201103L
 template<typename... _T>
	void push_middle(_T&&... new_data){//i.e. emplace_middle in O(logn) time
		push_middle(GC.ptr?GC.pop(std::forward<_T>(new_data)...):new node(std::forward<_T>(new_data)...));
#else
	void push_middle(const T& new_data){
	    push_middle(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!base::head)
			base::head=base::tail=new_node;
        else if(!base::head->next){
			new_node->prev=base::tail;
			base::tail->next=new_node;
			base::tail=new_node;
        }
        else{
    	    node *slow_ptr=base::head,*fast_ptr=base::head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    new_node->prev=slow_ptr;
		    slow_ptr->next=new_node;
		    new_node->next->prev=new_node;
		}
	    ++base::_size;
	}
	
	void pop_middle(){//i.e. pop_middle in O(logn) time
	    if(!base::head) return;
    	if (!base::head->next){
			GC.push(base::head);
	        base::head=base::tail=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				base::tail=base::head;
			GC.push(slow_ptr);
		}
    	--base::_size;
	}
	node* pop_middle(bool){
	    if(!base::head) return nullptr;
        node* popped=nullptr;
    	if (!base::head->next){
			popped=base::head;
	        base::head=base::tail=nullptr;
    	}
    	else{
		    node *slow_ptr=base::head,*fast_ptr=base::head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				base::tail=base::head;
			popped=slow_ptr;
		}
    	--base::_size;
    	return popped;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(__int64 index,_T&&... new_data){//i.e. emplace randomly in O(n) time
		insert(index,GC.ptr?GC.pop(std::forward<_T>(new_data)...):new node(std::forward<_T>(new_data)...));
#else
	void insert(__int64 index,const T& new_data){
		insert(index,GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void insert(const size_t& index,node* new_node){
		if(index<0||index>base::_size)
			return;
    	if(!index){
			push_front(new_node);
			return;
    	}
		if(index==base::_size){
			push_back(new_node);
			return;
		}
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
    	temp->next=new_node;
    	temp2->prev=temp->next;
		temp->next->next=temp2;
		temp->next->prev=temp;
		++base::_size;
	}
	
	void erase(const size_t& index){//i.e. removes node randomly in O(n) time
		if(index<0||index>=base::_size) return;
    	if(!index){ pop_front(); return; }
		if(index==base::_size-1){ pop_back(); return; }
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
		GC.push(temp->next);
    	temp->next=temp2;
    	temp2->prev=temp;
    	--base::_size;
	}
	node* erase(const size_t& index,bool){
		if(index<0||index>=base::_size) return nullptr;
    	if(!index) return pop_front(true);
		if(index==base::_size-1) return pop_back(true);
		node *temp=base::head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next,*popped=nullptr;
		popped=temp->next;
    	temp->next=temp2;
    	temp2->prev=temp;
    	--base::_size;
    	return popped;
	}
	void erase(node *current){//i.e. removes node randomly in O(1) time if current node is given
		if(!(current&&base::head)) return;//Warning: no exception is possible to efficiently identify wrong node address
    	if(current==base::head){ pop_front(); return; }
		if(current==base::tail){ pop_back(); return; }
		current->prev->next=current->next;
		current->next->prev=current->prev;
		GC.push(current);
		--base::_size;
	}
	
#if __cplusplus >= 201103L
	template<typename... _T>
	void resize(const size_t& new_size,_T&&... new_data){//i.e. emplaced_resize
#else
	void resize(const size_t& new_size,const T& new_data=T()){
#endif
		if (new_size<0||new_size>base::max_capacity)
			return;
		if(new_size>base::_size)
			while(new_size>base::_size)
			#if __cplusplus >= 201103L
				push_back(std::forward<_T>(new_data)...);
    		#else
				push_back(new_data);
			#endif
    	else
    		while(new_size<base::_size)
				pop_back();
	}
	
	void unique(){
		if (base::head&&base::head->next)//i.e. do nothing if size < 2
        	unique(base::head);
	}
private: //i.e. hidden method
	void unique(node* temp){//i.e. works best for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		if(temp->next)
					temp->next->prev=temp;
				else
					base::tail=temp;
				GC.push(to_delete);
        		--base::_size;
        		unique(temp);
        	}
        	else //i.e. advances only if no deletion
	            unique(temp->next); 
   	 	}
	}
	
public:
#if __cplusplus >= 201103L
	void sorted_insert(T&& new_data,bool direction_flag=true){
		sorted_insert(GC.ptr?GC.pop(std::forward<T>(new_data)):new node(std::forward<T>(new_data)),direction_flag);
	}
#endif
	void sorted_insert(const T& new_data,bool direction_flag=true){
		sorted_insert(GC.ptr?GC.pop(new_data):new node(new_data),direction_flag);
	}
	void sorted_insert(node* new_node,bool direction_flag=true){
		direction_flag?ascending_sorted_insert(new_node):descending_sorted_insert(new_node);
		++base::_size;
	}
		
	void clear(){//i.e. O(1) complexity
		if(base::head){
			GC.push(base::head,base::tail,base::_size);
			base::tail=base::head=nullptr;
		}
		base::_size=0;
	}
	
 	/* Iterators */
 	typedef typename base::_iterator iterator;
	typedef typename base::_r_iterator r_iterator;
#if __cplusplus >= 201103L
private:
	struct reverse_adapter{//i.e. defined to use reverse_iterator on 'range-based' loop
		reverse_adapter(const List& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const List& ref;
	};
public:
	//i.e. reversely traverse List without changing it (inside range-based loop)
	reverse_adapter reverse_iterator()const{ return reverse_adapter(*this); }
#endif
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~List(){ clear(); }//i.e. dtor
};

template<typename T>
typename List<T,true>::garbage_collector List<T,true>::GC;//i.e. initializing static member ctor

#endif
