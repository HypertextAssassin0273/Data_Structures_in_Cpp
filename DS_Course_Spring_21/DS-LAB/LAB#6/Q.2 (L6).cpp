#include<iostream>
using namespace std;

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class DLL{
protected:
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
	DLL(__uint64 n=0)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. default ctor
		if(n<=max_capacity)
			while(n>_size)
           		push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	DLL(__uint64 n,_T&&... new_data)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. emplaced fill ctor
		if(n<=max_capacity)
			while(n>_size)
				push_back(new_data...);
	}
#else
	DLL(__uint64 n,const T& new_data)noexcept:head(nullptr),tail(nullptr),_size(0){
		if(n<=max_capacity)
			while(n>_size)
				push_back(new_data);
	}
#endif
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
#if __cplusplus >= 201103L
 	DLL(DLL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		head(other.head),tail(other.tail),_size(other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	DLL& operator=(DLL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
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
	
	/* Overloaded 'cin/cout' Methods */
	friend ostream& operator<<(ostream& out,const DLL& list){//i.e. same as traverse_forward
		for(node *it=list.head;it;it=it->next)
    		out<<*it<<" ";
		return out;
	}
	friend istream& operator>>(istream& in,DLL& list){//Note: works best for updating values
		for(node *it=list.head;it;it=it->next)
    		in>>*it;
		return in;
	}
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~DLL(){ clear(); }//i.e. dtor
};
template<typename T>
typename DLL<T>::garbage_collector DLL<T>::GC;


class Intelligence_Info:public DLL<int>{
	int hijacked,last_member;
public:
	Intelligence_Info()noexcept:
		hijacked(-1),last_member(-1){}//i.e. triggers default DLL ctor
	
	void find(){
			node* temp=head;
			int count=0;
			
			while(temp){
				if(!temp->data){
					hijacked=count;
					break;
				}
				count++;
				temp=temp->next;
			}
			while(temp!=head){
				temp=temp->prev;
				count--;
			}
			while(temp){
				if(temp->data==1){
					last_member=count;
					break;
				}
				count++;
				temp=temp->next;
			}
		}
		/*Note: if any node consists of 0, that cabin(node) is hijacked and if any node consists 1 
			then that cabin(node) consist of last member */
	
	friend ostream& operator<<(ostream& out,const Intelligence_Info& self){
		out<<"Note: cabin/node starts from 0th index"<<endl
		   <<"0->represents hijacked\t1->represents last hidden member\n"<<endl
		   <<"Cabins are: "<<(DLL<int>)self<<endl //i.e. traverse DLL nodes in forward direction
		   <<"Hijacked cabin is: "<<self.hijacked<<" index"<<endl
		   <<"Last hidden member is: "<<self.last_member<<" index"<<endl;
		return out;
	}
};

int main(){
	Intelligence_Info obj;
	obj.push_back(12);
	obj.push_back(9);
	obj.push_back(0);
	obj.push_back(5);
	obj.push_back(26);
	obj.push_back(1);
	obj.find();
	cout<<obj;
	return 0;
}
