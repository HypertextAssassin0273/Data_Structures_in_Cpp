#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class SLL{//i.e. Singly Linked-List
    typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
    	node *next;
    	
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr){}
		
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
		node* pop(const T& new_data){
			if(!ptr)
    	   		return nullptr;
	    	node *temp=ptr->next,*popped=ptr;
    		ptr=temp;
    		popped->data=new_data;
    		popped->next=nullptr;
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
		void clear(){
			node* temp;
			while(ptr){
	   			temp=ptr->next;
	    		delete ptr;
    			ptr=temp;	
			}
		}
		~garbage_collector(){ clear(); }
		/*Drawback: 
			1) whenever a list is destroyed, its node transfer to its' type of garbage collector 
			at O(n) complexity */
	};
	
	static garbage_collector GC;
	node *head;
	__uint32 _size;
public:
	SLL()noexcept:head(nullptr),_size(0){}//i.e. default ctor
private:
	SLL(const SLL &other)noexcept;
    SLL& operator=(const SLL &other)noexcept;
public:
   /* Accessors & Mutators */
	node* new_node(const T& new_data)const{ return GC.ptr?GC.pop(new_data):new node(new_data); }

    T& operator[](__uint32 n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";
			throw false;
		}
		node* it=head;
		for(__uint32 i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& front()const{
		if (head)
			return head->data;
		throw false;
	}
	__uint32 size()const{ return _size; }

public:
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
    }
    void push_front(node* new_node){
        new_node->next=head;
        head=new_node;
		++_size;
    }
    node* pop_front(bool flag=false){//Complexity:O(1)
    	if(!head)
    	    return nullptr;
    	node* temp=nullptr;
    	if(flag){
    		temp=head;
			head=head->next;
			temp->next=nullptr;
		}
		else{
			temp=head->next;
			GC.push(head);
			head=temp;
    	}
		--_size;
    	return temp;
	}

    void traverse()const{
    	if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		cout<<*it<<" ";
    		
		cout<<endl;
	}
	void clear(){//i.e. not efficient
		node* temp;
			while(head){
	   			temp=head->next;
	    		GC.push(head);
    			head=temp;	
			}
		_size=0;
	}
	/* Iterators */
	struct iterator{
		iterator():ptr(nullptr){}
    	iterator(node* ptr):ptr(ptr){}
    	
    	node& operator*()const{ return *ptr; }
    	node* operator->()const{ return ptr; }
    	
		iterator& operator++(){ ptr=ptr->next; return *this; }
		iterator operator++(int){ iterator temp(*this); ptr=ptr->next; return temp; }
		
		bool operator==(const iterator& other)const{ return ptr==other.ptr; }
		bool operator!=(const iterator& other)const{ return ptr!=other.ptr; }
	private:
		node* ptr;
    };
	iterator begin()const{ return iterator(head); }//i.e. points to first element
	iterator end()const{ return iterator(nullptr); }//i.e. points to last element

	/* Comparison Operators */
	bool operator==(const SLL& other)const;
	bool operator!=(const SLL& other)const;
	
	/* Two list based Operations */
	void fill_other_reversely(SLL &other);
	void fill_other_reversely(SLL &other,bool)const;
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~SLL(){ clear(); }//i.e. dtor
};
template<typename T>
typename SLL<T>::garbage_collector SLL<T>::GC;

