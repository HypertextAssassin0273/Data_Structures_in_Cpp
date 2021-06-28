#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class DLL{//i.e. Doubly Linked-List (same as STL::list)
    typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
    	node *next,*prev;
    	
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr),prev(nullptr){}
		
		friend ostream& operator<<(ostream& out,const node& self){
			out<<self.data;
			return out;
		}
		friend istream& operator>>(istream& in,node& self){
			in>>self.data;
			return in;
		}
	};
	
	struct garbage_collector{//i.e. implementing stack
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
		node* pop(const T& new_data){//i.e. complexity O(1)
			if(!ptr)
    	   		return nullptr;
	    	node *popped=ptr;
    		ptr=ptr->next;
    		--_size;
    		popped->data=new_data;
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
	
	static garbage_collector GC;
    node *head,*tail;
	__uint32 _size;
public:
	DLL()noexcept:head(nullptr),tail(nullptr),_size(0){}//i.e. default ctor
	
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	DLL(initializer_list<T> list)noexcept:head(nullptr),tail(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	DLL(const DLL &other)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    DLL& operator=(const DLL &other)noexcept{//i.e. copy assignment func.
    	if(this==&other)//i.e. self-assignment protection
    		return *this;
		clear();//1) clear existing resources
        for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//2) copy other's data
        return *this;
    }
    
	/* Accessors */
	node* new_node(const T& new_data)const{ return GC.ptr?GC.pop(new_data):new node(new_data); }
   	T& operator[](__uint32 n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		if(n==_size-1)
			return tail->data;//i.e. same as back()
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
    
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
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
    void push_back(const T& new_data){//Complexity: O(1)
    	push_back(GC.ptr?GC.pop(new_data):new node(new_data));
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
		reverse_adapter(const DLL& ref):ref(ref){}
		r_iterator begin(){ return ref.rbegin(); }
		r_iterator end(){ return ref.rend(); }
	private:
		const DLL& ref;
	};
public:
	//i.e. reversely traverse DLL without changing it (inside range-based loop)
	reverse_adapter reverse_iterator()const{ return reverse_adapter(*this); }
#endif
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	/* Extras */
	T get_minimum();
	void find_first_non_repeating_element();
private:
	void find_first_non_repeating_element(node*,bool&);

public:
	~DLL(){ clear(); }//i.e. dtor
};
template<typename T>
typename DLL<T>::garbage_collector DLL<T>::GC;

