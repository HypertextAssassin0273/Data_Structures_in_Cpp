#include<iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class xor_list{//i.e. xor doubly linked-list (memory efficient)
	typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
		node *xnode;//i.e. contains Xor of next node & previous node
		
	#if __cplusplus < 201103L
		node(const T& data=T())noexcept://i.e. default ctor
			data(data),xnode(nullptr){}
	#else
		template<typename... _T>
		node(_T&&... data)noexcept://i.e. variadic template & emplaced ctor
			data{std::forward<_T>(data)...},//i.e. perfect forwarding
			xnode(nullptr){}
	#endif
		
		friend std::ostream& operator<<(std::ostream& out,const node& self){
			out<<self.data;
			return out;
		}
		friend std::istream& operator>>(std::istream& in,node& self){
			in>>self.data;
			return in;
		}
	};
	
	node* XOR(node* x,node* y)const{//i.e. returns xored value of the node addresses
		return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(x)^reinterpret_cast<uintptr_t>(y));
	}
	
	node *head,*tail;
	__uint32 _size;
public:
	xor_list(const __uint64& n=0)noexcept:head(nullptr),tail(nullptr),_size(0){//i.e. default ctor
		while(n>_size)
			push_back(T());
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	xor_list(const __uint64& n,_T&&... new_data)noexcept:
		head(nullptr),tail(nullptr),_size(0){//i.e. emplaced fill ctor
			while(n>_size)
				push_back(std::forward<_T>(new_data)...);
	}
#else
	xor_list(const __uint64& n,const T& new_data)noexcept://i.e. fill ctor
		head(nullptr),tail(nullptr),_size(0){
			while(n>_size)
				push_back(new_data);
	}
#endif
	xor_list(const xor_list &other)noexcept:
		head(nullptr),tail(nullptr),_size(0){//i.e. copy ctor
		node *curr=other.head,*next,*prev=nullptr;
		while(curr){
			push_back(curr->data);//1) copy other's data
			next=XOR(prev,curr->xnode);
			prev=curr;
			curr=next;
		}
	}
	xor_list& operator=(const xor_list &other)noexcept{//i.e. copy assignment func.
		if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
			node *curr=other.head,*next,*prev=nullptr;
			while(curr){
				push_back(curr->data);//2) copy other's data
				next=XOR(prev,curr->xnode);
				prev=curr;
				curr=next;
			}
		}
		return *this;
	}
#if __cplusplus >= 201103L
	xor_list(xor_list&& other)noexcept://i.e. move ctor
		head(other.head),tail(other.tail),_size(other._size){//1) steal other's data
		other.head=nullptr; other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}
	xor_list& operator=(xor_list&& other)noexcept{//i.e. move assignment
		if(this!=&other){
			clear();//1) clear existing resources
			head=other.head; tail=other.tail; _size=other._size;//2) steal other's data
			other.head=nullptr; other.tail=nullptr; other._size=0;//3) set 'other' to null state
		}
		return *this;
	}
	xor_list(std::initializer_list<T> list)noexcept://i.e.initializer_list based ctor
		head(nullptr),tail(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
			push_back(it);
	}
#endif

	/* Accessors & Mutators */
	T& operator[](__uint32 n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			std::cout<<"\nError: Given Index is Out of Bound!\n";			
	 		throw false;
		}
		if(n==_size-1)
			return tail->data;
		node *curr=head,*next,*prev=nullptr;
		while(n){
			next=XOR(prev,curr->xnode);
			prev=curr;
			curr=next;
			--n;
		}
		return curr->data;
	}
	T& front()const{
		if (tail)
			return head->data;
		throw false;
	}
	T& back()const{
		if (tail)
			return tail->data;
		throw false;
	}
	__uint32 size()const{ return _size; }
	bool empty()const{ return head?false:true; }
	
	/*i.e. Modifiers */
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
		new_node->xnode=head;
		if(head)
			head->xnode=XOR(new_node,head->xnode);//head->prev=new_node
		else
			tail=new_node;
		head=new_node;
		++_size;
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
		if(!tail)//i.e. anyone of them can be used to check
			head=tail=new_node;
		else{
			new_node->xnode=XOR(tail,new_node->xnode);//new_node->prev=tail
			tail->xnode=XOR(new_node,tail->xnode);//tail->next=new_node
			tail=new_node;
		}
		++_size;
	}
	node* pop_front(bool flag=false){//Complexity: O(1)
		if(!head)
			return nullptr;
		node* popped=nullptr;
		if (!head->xnode){
			if(flag)
				popped=head; 
			else
				delete head;
			head=tail=nullptr;
		}
		else{
			node *temp=head->xnode,*next=XOR(head,head->xnode->xnode);//stores next of xored node
			if(flag){
				popped=head;
				popped->xnode=nullptr;
			}
			else
				delete head;
			head=temp;
			head->xnode=next;
		}
		--_size;
		return popped;
	}
	node* pop_back(bool flag=false){//Complexity: O(1)
		if(!tail)
			return nullptr;
		node* popped=nullptr;
		if (!tail->xnode){
			if(flag) 
				popped=tail; 
			else 
				delete tail;
			head=tail=nullptr;
		}
		else{
			node *temp=tail->xnode,*prev=XOR(tail,tail->xnode->xnode);//stores prev of xored node
			if(flag){
				popped=tail;
				popped->xnode=nullptr;
			}
			else
				delete tail;
			tail=temp;
			tail->xnode=prev;
		}
		--_size;
		return popped;
	}
	void traverse_forward()const{
		if(!head){
			std::cout<<"List is empty!"<<'\n';
			return;
		}
		node *curr=head,*next,*prev=nullptr;
		while(curr){
			std::cout<<*curr<<" ";
			next=XOR(prev,curr->xnode);
			prev=curr;
			curr=next;
		}
		std::cout<<'\n';
	}
	void traverse_backward()const{
		if(!tail){
			std::cout<<"List is empty!"<<'\n';
			return;
		}
		node *curr=tail,*next=nullptr,*prev;
		while(curr){
			std::cout<<*curr<<' ';
			prev=XOR(next,curr->xnode);
			next=curr;
			curr=prev;
		}
		std::cout<<'\n';
	}
	void reverse(){//Complexity: O(1)
		if(!head||!head->xnode)
			return;
		node* temp=head;
		head=tail;
		tail=temp;
	}
	void clear(){
		node *next,*temp=nullptr;
			while(head){
				next=XOR(head->xnode,temp);
	   			temp=head;
				delete head;
				head=next;	
			}
		tail=nullptr;
		_size=0;
	}
	
	~xor_list(){ clear(); }//i.e. dtor
};


int main(){
#if __cplusplus >= 201103L
	xor_list<int> xlist={1,2,3,4};
#else
	xor_list<int> xlist;
	for(int i=1;i<5;++i)
		xlist.push_back(i);
#endif
	xlist.push_front(0);//0 1 2 3 4
	
	xlist.push_back(xlist.pop_front(true));//0 1 2 3 4-> 1 2 3 4 0 (i.e. node transfer)
	
	xlist.pop_back();//1 2 3 4 0-> 1 2 3 4
	
	xlist.reverse();//1 2 3 4-> 4 3 2 1
	
	xlist.traverse_forward();
	xlist.traverse_backward();
	return 0;
}
/* References:
https://www.geeksforgeeks.org/xor-linked-list-a-memory-efficient-doubly-linked-list-set-1/
https://www.youtube.com/watch?v=hMcHVfu3E8U
*/
