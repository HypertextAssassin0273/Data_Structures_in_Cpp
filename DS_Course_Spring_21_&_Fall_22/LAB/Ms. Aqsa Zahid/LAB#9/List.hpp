#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

#ifndef LIST_GUARD
#define LIST_GUARD 1

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

/* List as Doubly Linked-List (same as STL::list) */
/*  Highlights:
	1) Main emphasis on 'rule of five' (move semantics applicable with C++11 settings)
	2) Concept of Garbage Collector is also implemented to improve efficiency of program in some specific cases
	3) Safe when accessing elements with accessors (Exception somewhat handled)
	4) All neccessary STL List class 'modifiers' & 'iterators' are provided
*/
template<typename T>
class List{
    typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
    	node *next,*prev;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr),prev(nullptr){}
    #else
		template<typename... _T>
		node(_T&&... data)noexcept://i.e. variadic template ctor
			data{std::forward<_T>(data)...},next(nullptr),prev(nullptr){}
	#endif
		
		friend ostream& operator<<(ostream& out,const node& self){
			out<<self.data;
			return out;
		}
		friend istream& operator>>(istream& in,node& self){
			in>>self.data;
			return in;
		}
	};
	
	struct garbage_collector{//i.e. implementing stack by LIFO order
		static const __uint32 max_capacity=128;
		__uint32 _size;
		node *ptr;
		
		garbage_collector():_size(0),ptr(nullptr){}
		
		void push(node* _new){//i.e. complexity O(1)
			_new->next=ptr;
			ptr=_new;
			++_size;
			if(_size>=max_capacity)
				release();
		}
		void push(node* new_head,node* new_tail,__uint32 new_size){//i.e. complexity O(1)
			new_tail->next=ptr;
			ptr=new_head;
			_size+=new_size;
			if(_size>=max_capacity)
				release();
		}//i.e. useful when a list is destroyed & its' nodes needs to transfer to garbage collector at O(1) complexity
	#if __cplusplus >= 201103L
		node* pop(T&& new_data){//i.e. complexity O(1)
			if(!ptr)
    	   		return nullptr;
	    	node *popped=ptr;
    		ptr=ptr->next;
    		--_size;
    		popped->data=move(new_data);
    		popped->next=popped->prev=nullptr;
    		return popped;
		}
		template<typename... _T>
		node* pop(_T&&... new_data){
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
    		popped->next=popped->prev=nullptr;
    		return popped;
		}
		void release(){
			node* temp;
			__uint32 prev_size=_size;
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
	
	static const __uint32 max_capacity=~((__uint32)0);
	static garbage_collector GC;
    node *head,*tail;
	__uint32 _size;
public:
	List(__uint64 n=0)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. default ctor
		if(n<=max_capacity)
			while(n>_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	List(__uint64 n,_T&&... new_data)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. emplaced fill ctor
		if(n<=max_capacity)
			while(n>_size)
				push_back(new_data...);
	}
#else
	List(__uint64 n,const T& new_data)noexcept:head(nullptr),tail(nullptr),_size(0){
		if(n<=max_capacity)
			while(n>_size)
				push_back(new_data);
	}
#endif
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	List(initializer_list<T> list)noexcept:head(nullptr),tail(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	List(const List &other)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    List& operator=(const List &other)noexcept{//i.e. copy assignment func.
    	if(this==&other)//i.e. self-assignment protection
    		return *this;
		clear();//1) clear existing resources
        for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//2) copy other's data
        return *this;
    }
#if __cplusplus >= 201103L
 	List(List&& other)noexcept://i.e. move ctor (C++11 Construct)
  		head(other.head),tail(other.tail),_size(other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	List& operator=(List&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		head=other.head; tail=other.tail; _size=other._size;//2) steal other's data
  		other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
  		return *this;
	}
#endif

	/* Accessors & Mutators */
#if __cplusplus >= 201103L
	node* new_node(T&& new_data)const{ return GC.ptr?GC.pop(move(new_data)):new node(move(new_data)); }
	template<typename... _T>
	node* new_node(_T&&... new_data)const{ return GC.ptr?GC.pop(new_data...):new node(new_data...); }
#else
	node* new_node(const T& new_data)const{ return GC.ptr?GC.pop(new_data):new node(new_data); }
#endif
    T& operator[](__uint32 n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		if(n==_size-1)
			return tail->data;
		node* it=head;
		for(__uint32 i=0;i<n;++i,it=it->next);
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
	__uint32 size()const{ return _size; }
	
    /*i.e. Modifiers */
    bool empty()const{ return head?false:true; }
#if __cplusplus >= 201103L
	void push_front(T&& new_data){//i.e. move_front
		push_front(GC.ptr?GC.pop(move(new_data)):new node(move(new_data)));
	}
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. emplace_front
		push_front(GC.ptr?GC.pop(new_data...):new node(new_data...));//i.e. direct initialization is possible
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
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
	void push_back(T&& new_data){//i.e. move_back
		push_back(GC.ptr?GC.pop(move(new_data)):new node(move(new_data)));
	}
	template<typename... _T>
	void push_back(_T&&... new_data){//i.e. emplace_back
		push_back(GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	push_back(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!tail)//i.e. anyone of them can be used to check
    		head=tail=new_node;
        else{
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
        }
        ++_size;
	}
    node* pop_front(bool flag=false){//Complexity:O(1)
    	if(!head)
    	    return nullptr;
    	node* popped=nullptr;
    	if (!head->next){
	        if(flag)
				popped=head; 
			else 
				GC.push(head);
	        head=tail=nullptr;
    	}
    	else{
    		node *temp=head->next;
    		if(flag){
    			popped=head;
				popped->next=nullptr;
			}
			else 
				GC.push(head);
    		head=temp;
    		head->prev=nullptr;
    	}
    	--_size;
    	return popped;
	}
	node* pop_back(bool flag=false){//Complexity: O(1)
		if(!tail)
        	return nullptr;
        node* popped=nullptr;
    	if (!tail->prev){
	        if(flag) 
				popped=tail; 
			else 
				GC.push(tail);
	        head=tail=nullptr;
    	}
    	else{
			node *temp=tail->prev;
			if(flag){
				popped=tail;
				popped->prev=nullptr;
			}
			else
				GC.push(tail);
    		tail=temp;
    		tail->next=nullptr;
		}
    	--_size;
    	return popped;
    }
#if __cplusplus >= 201103L
	void push_middle(T&& new_data){//i.e. move_middle
		push_middle(GC.ptr?GC.pop(move(new_data)):new node(move(new_data)));
	}
	template<typename... _T>
	void push_middle(_T&&... new_data){//i.e. emplace_middle
		push_middle(GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
	void push_middle(const T& new_data){
	    push_middle(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!head)
			head=tail=new_node;
        else if(!head->next){
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
        }
        else{
    	    node *slow_ptr=head,*fast_ptr=head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    new_node->prev=slow_ptr;
		    slow_ptr->next=new_node;
		    new_node->next->prev=new_node;
		}
	    ++_size;
	}
	node* pop_middle(bool flag=false){
	    if(!head)
        	return nullptr;
        node* popped=nullptr;
    	if (!head->next){
	        if(flag)
				popped=head;
			else
				GC.push(head);
	        head=tail=nullptr;
    	}
    	else{
		    node *slow_ptr=head,*fast_ptr=head;
	        while(fast_ptr&&fast_ptr->next){
    	       	fast_ptr=fast_ptr->next->next;
       	    	slow_ptr=slow_ptr->next;
    		}
    	    slow_ptr->prev->next=slow_ptr->next;
    	    if(slow_ptr->next)
				slow_ptr->next->prev=slow_ptr->prev;
			else
				tail=head;
    		if(flag) 
				popped=slow_ptr;
			else
				GC.push(slow_ptr);
		}
    	--_size;
    	return popped;
	}
#if __cplusplus >= 201103L
	void insert(__int64 index,T&& new_data){
		insert(index,GC.ptr?GC.pop(move(new_data)):new node(move(new_data)));
	}
	template<typename... _T>
	void insert(__int64 index,_T&&... new_data){//i.e. emplace_randomly
		insert(index,GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
	void insert(__int64 index,const T& new_data){
		insert(index,GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void insert(__int64 index,node* new_node){
		if(index<0||index>_size)
			return;
    	if(!index){
			push_front(new_node);
			return;
    	}
		if(index==_size){
			push_back(new_node);
			return;
		}
		node *temp=head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
    	temp->next=new_node;
    	temp2->prev=temp->next;
		temp->next->next=temp2;
		temp->next->prev=temp;
		++_size;
	}
	node* erase(__int64 index,bool flag=false){//i.e. removes node randomly
		if(index<0||index>=_size)
			return nullptr;
    	if(!index)
    		return pop_front(flag);
		if(index==_size-1)
			return pop_back(flag);
		node *temp=head;
		for(__int64 i=0;i<index-1;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next,*popped=nullptr;
    	if(flag)
			popped=temp->next;
		else
			GC.push(temp->next);
    	temp->next=temp2;
    	temp2->prev=temp;
    	--_size;
    	return popped;
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void resize(__int64 new_size,_T&&... new_data){//i.e. emplaced_resize
#else
	void resize(__int64 new_size,const T& new_data=T()){
#endif
		if (new_size<0||new_size>max_capacity)
			return;
		if(new_size>_size)
			while(new_size>_size)
			#if __cplusplus >= 201103L
				push_back(new_data...);
    		#else
				push_back(new_data);
			#endif
    	else
    		while(new_size<_size)
				pop_back();
	}
	void unique(){
		if (head&&head->next)//i.e. do nothing if size < 2
        	unique(head);
	}
private: /*i.e. Hidden methods */
	void unique(node* temp){//i.e. works best for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		if(temp->next)
					temp->next->prev=temp;
				else
					tail=temp;
				GC.push(to_delete);
        		--_size;
        		unique(temp);
        	}
        	else //i.e. advances only if no deletion
	            unique(temp->next); 
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
public:
#if __cplusplus >= 201103L
	void sorted_insert(T&& new_data,bool direction_flag=true){
		sorted_insert(GC.ptr?GC.pop(move(new_data)):new node(move(new_data)),direction_flag);
	}
#endif
	void sorted_insert(const T& new_data,bool direction_flag=true){
		sorted_insert(GC.ptr?GC.pop(new_data):new node(new_data),direction_flag);
	}
	void sorted_insert(node* new_node,bool direction_flag=true){
		if(direction_flag)
			ascending_sorted_insert(new_node);
		else
			descending_sorted_insert(new_node);
		++_size;
	}
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
	void reverse(){
		if(!head||!head->next)
			return;
		node* temp=head;
		head=tail;
		tail=temp;
	#if __cplusplus >= 201103L	
		for(auto& it:*this){
    		temp=it.next;
    		it.next=it.prev;
    		it.prev=temp;
		}
	#else
		for(node *it=head;it;it=it->next){
    		temp=it->next;
    		it->next=it->prev;
    		it->prev=temp;
		}
	#endif
	}
	void merge(List &other,__int64 pos=0){
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
    void traverse_forward()const{
    	if(!head){
    		cout<<"List is empty!"<<endl;
        	return;
    	}
	#if __cplusplus >= 201103L
		for(const auto& it:*this)
			cout<<it<<" ";
	#else
		for(node *it=head;it;it=it->next)
    		cout<<*it<<" ";
	#endif
		cout<<endl;
	}
	void traverse_backward()const{
    	if(!tail){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    #if __cplusplus >= 201103L
    	for(const auto& it:reverse_adapter(*this))
			cout<<it<<" ";
	#else
		for(node *it=tail;it;it=it->prev)
    		cout<<*it<<" ";
	#endif
		cout<<endl;
	}
	void clear(){
		if(head){
			GC.push(head,tail,_size);
			tail=head=nullptr;
		}
		_size=0;
	}
	
	/* Comparison Operators */
	bool operator==(const List& other)const{
		if(other._size<_size)
			return false;
		for (node *i=head,*j=other.head;i;i=i->next,j=j->next)
    		if (i->data!=j->data)
      			return false;
  		return true;
	}
	bool operator!=(const List& other)const{ return !(*this==other); }
	
	bool operator<(const List& other)const{
  		node *i=head,*j=other.head;
  		for (;i;i=i->next,j=j->next){
  			if(i==other.tail||j->data<i->data)
  				return false;
  			else if(i->data<j->data)
  				return true;
		}
		return i!=other.tail;
	}
    bool operator>(const List& other)const{ return other<*this; }
	bool operator<=(const List& other)const{ return !(other<*this); }
	bool operator>=(const List& other)const{ return !(*this<other); }

 	/* Iterators */
	template<bool flag>//i.e. true-> forward_iterator, false->reverse_iterator
	struct _iterator{
		typedef _iterator self;
		
		_iterator():ptr(nullptr){}
    	_iterator(node* ptr):ptr(ptr){}
    	
    	node& operator*()const{ return *ptr; }
    	node* operator->()const{ return ptr; }
    	
    	self& operator++(){ flag?ptr=ptr->next:ptr=ptr->prev; return *this; }
    	self& operator--(){ flag?ptr=ptr->prev:ptr=ptr->next; return *this; }
		self operator++(int){ self temp(*this); flag?ptr=ptr->next:ptr=ptr->prev; return temp; }
		self operator--(int){ self temp(*this); flag?ptr=ptr->prev:ptr=ptr->next; return temp; }
		
		bool operator==(const self& other)const{ return ptr==other.ptr; }
		bool operator!=(const self& other)const{ return ptr!=other.ptr; }
	private:
		node* ptr;
    };
    typedef _iterator<true> iterator;
    typedef _iterator<false> r_iterator;
	
    iterator begin()const{ return iterator(head); }
	iterator end()const{ return iterator(nullptr); }	
    r_iterator rbegin()const{ return r_iterator(tail); }
	r_iterator rend()const{ return r_iterator(nullptr); }
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
	
	/* Overloaded 'cin/cout' Methods */
	friend ostream& operator<<(ostream& out,const List& list){//i.e. same as traverse_forward
		for(node *it=list.head;it;it=it->next)
    		out<<*it<<" ";
		return out;
	}
	friend istream& operator>>(istream& in,List& list){//Note: works best for updating values
		for(node *it=list.head;it;it=it->next)
    		in>>*it;
		return in;
	}
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~List(){ clear(); }//i.e. dtor
};
template<typename T>
typename List<T>::garbage_collector List<T>::GC;

#endif
