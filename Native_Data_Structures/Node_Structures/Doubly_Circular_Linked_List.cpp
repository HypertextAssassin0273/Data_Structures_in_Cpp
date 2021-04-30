#include<iostream>
using namespace std;

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class DCLL{//i.e. Doubly Circular Linked-List
    typedef unsigned long long __uint64;
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
    	node *next,*prev;
    	
    #if __cplusplus >= 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr),prev(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)noexcept://i.e. emplaced ctor
			data{std::forward<_T>(data)...},next(nullptr),prev(nullptr){}
	#endif
		
		friend ostream& operator<<(ostream& out,const node& obj){
			out<<obj.data;
			return out;
		}
		friend istream& operator<<(istream& in,node& obj){
			in>>obj.data;
			return in;
		}
	};
	
    node *tail;
	__uint32 _size;
public:
	DCLL()noexcept:tail(nullptr),_size(0){}//i.e. default ctor
	
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	DCLL(initializer_list<T> list)noexcept:tail(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	DCLL(const DCLL &other)noexcept:tail(nullptr),_size(0){//i.e. copy ctor
    	if(!other.tail)
			return;
		node *it=other.tail->next;
		do{
    		push_back(it->data);//1) copy other's data
    		it=it->next;
		}while(it!=other.tail->next);
    }
    DCLL& operator=(const DCLL &other)noexcept{//i.e. copy assignment func.
    	if(this==&other)//i.e. self-assignment protection
    		return *this;
		clear();//1) clear existing resources
		if(!other.tail)
			return *this;
        node *it=other.tail->next;
		do{
    		push_back(it->data);//2) copy other's data
    		it=it->next;
		}while(it!=other.tail->next);
        return *this;
    }
#if __cplusplus >= 201103L
 	DCLL(DCLL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		tail(other.tail),_size(other._size){//1) steal other's data
		other.tail=nullptr; other._size=0;//2) set 'other' to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	DCLL& operator=(DCLL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		tail=other.tail; _size=other._size;//2) steal other's data
  		other.tail=nullptr; other._size=0;//3) set 'other' to null state
  		return *this;
	}
#endif

	/* Accessors & Mutators */
    T& operator[](__uint32 n){
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		throw false;
		}
		if(!n)
			return tail->next->data;//i.e. same as front()
		if(n==_size-1)
			return tail->data;//i.e. same as back()
		node* it=tail->next;
		for(__uint32 i=0;i<n;++i,it=it->next);
		return it->data;
	}
	T& front()const{
		if (tail)
			return tail->next->data;
		throw false;
	}
	T& back()const{
		if (tail)
			return tail->data;
		throw false;
	}
	__uint32 size()const{ return _size; }
	
    /*i.e. Modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. emplace_front
		node *new_node=new node(new_data...);//i.e. direct initialization is possible
#else
    void push_front(const T& new_data){//Complexity: O(1)
		node *new_node=new node(new_data);
#endif
		if(!tail){
			tail=new_node;
			tail->next=tail->prev=tail;
		}
		else{
			new_node->next=tail->next;//head=tail->next
			tail->next->prev=new_node;
			tail->next=new_node;
			new_node->prev=tail;
		}
		++_size;
    }
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){//i.e. emplace_back
		node *new_node=new node(new_data...);
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	node *new_node=new node(new_data);
#endif
		if(!tail){
    		tail=new_node;
    		tail->next=tail->prev=tail;
    	}
        else{
			new_node->prev=tail;
			tail->next->prev=new_node;
			new_node->next=tail->next;
			tail->next=new_node;
			tail=new_node;
        }
        ++_size;
	}
    void pop_front(){//Complexity:O(1)
    	if(!tail)
    	    return;
    	if (tail->next==tail){
	        delete tail;
	        tail=nullptr;
    	}
    	else{
    		node *temp=tail->next->next;
			delete tail->next;
    		tail->next=temp;
    		temp->prev=tail;
    	}
    	--_size;
	}
	void pop_back(){//Complexity: O(1)
		if(!tail)
        	return;
    	if (tail->next==tail){
	        delete tail;
	        tail=nullptr;
    	}
    	else{
			node *temp=tail->prev;
			temp->next=tail->next;
			tail->next->prev=temp;
			delete tail;
    		tail=temp;
		}
    	--_size;
    }

#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){//i.e. emplace_middle
		if(!tail||tail->next==tail){
			push_back(new_data...);
			return;
		}
		node *new_node=new node(new_data...);
#else
	void push_middle(const T& new_data){
	    if(!tail||tail->next==tail){
			push_back(new_data);
			return;
		}
		node *new_node=new node(new_data);
#endif
    	node *slow_ptr=tail->next,*fast_ptr=tail->next->next;//i.e. tail->next==head
        while(fast_ptr!=tail->next&&fast_ptr->next!=tail->next){
            fast_ptr=fast_ptr->next->next;
           	slow_ptr=slow_ptr->next;
        }
		new_node->next=slow_ptr->next;
		new_node->prev=slow_ptr;
		slow_ptr->next=new_node;
	    new_node->next->prev=new_node;
	    ++_size;
	}
	void pop_middle(){
	    if(!tail)
        	return;
    	if (tail->next==tail||tail->next->next==tail){
    		pop_back();
	        return;
    	}
	    node *slow_ptr=tail->next,*fast_ptr=tail->next,*prev;
        do{
           	fast_ptr=fast_ptr->next->next;
           	prev=slow_ptr;
           	slow_ptr=slow_ptr->next;
    	}while(fast_ptr!=tail->next&&fast_ptr->next!=tail->next);
        slow_ptr->prev->next=slow_ptr->next;
		slow_ptr->next->prev=slow_ptr->prev;
    	delete slow_ptr;
    	--_size;
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(__int64 pos,_T&&... new_data){//i.e. emplace_randomly
#else
	void insert(__int64 pos,const T& new_data){
#endif
		if(!tail)
        	return;
    	if(pos<2){
    	#if __cplusplus >= 201103L
    		push_front(new_data...);
		#else
			push_front(new_data);
    	#endif
			return;
    	}
		if(pos>_size){
		#if __cplusplus >= 201103L
			push_back(new_data...);
		#else
			push_back(new_data);
		#endif
			return;
		}
		node *temp=tail->next;
		for(__int64 i=0;i<pos-2;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
    #if __cplusplus >= 201103L
		temp->next=new node(new_data...);
	#else
    	temp->next=new node(new_data);
    #endif
    	temp2->prev=temp->next;
		temp->next->next=temp2;
		temp->next->prev=temp;
	}
	void erase(__int64 pos){//i.e. removes node randomly
		if(!tail)
        	return;
    	if(pos<2){
    		pop_front();
    		return;
    	}
		if(pos>=_size){
			pop_back();
			return;
		}
		node *temp=tail->next;
		for(__int64 i=0;i<pos-2;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
    	delete temp->next;
    	temp->next=temp2;
    	temp2->prev=temp;
	}
	void reverse(){
		if(_size<2)
			return;
		node *temp,*it=tail->next;
		tail=tail->next;
		for(__uint32 i=0;i<_size;++i,it=it->next){
    		temp=it->next;
    		it->next=it->prev;
    		it->prev=temp;
		}
	}
    void traverse_forward()const{
    	if(!tail){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
		node *temp=tail->next;
    	do{
    		cout<<*temp<<" ";
    		temp=temp->next;
		}while(temp!=tail->next);
		cout<<endl;
	}
	void traverse_backward()const{
    	if(!tail){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
		node *temp=tail;
    	do{
    		cout<<*temp<<" ";
    		temp=temp->prev;
		}while(temp!=tail);
		cout<<endl;
	}
	void merge(DCLL &other,__int64 pos=0){
		if(!other.tail||pos<0||pos>_size)
			return;//i.e. do nothing if 'other' have no nodes or size exceeds the given pos
		node *temp;
		if(!pos){//i.e. if pos is '0', then directly join head of other to head of 'this'
			temp=tail->next;
			tail->next=other.tail->next;
			other.tail->next->prev=tail;
		}
		else{
			node *temp2=tail->next;
			for(int i=1;i<pos;++i)
				temp2=temp2->next;
			temp=temp2->next;
			temp2->next=other.tail->next;
			other.tail->next->prev=temp2;
		}
		other.tail->next=temp;
		temp->prev=other.tail;
		_size+=other._size;
		other.tail=nullptr;
		other._size=0;
	}
	void clear(){
		if(!tail)
			return;
		if(tail->next==tail)
			delete tail;
		else{
			node* temp,*head=tail->next;
			tail->next=nullptr;//i.e. converting into non-circular by breaking link
			while(head){
	   			temp=head->next;
	    		delete head;
    			head=temp;
			}
		}
		tail=nullptr;
	}
	
	~DCLL(){ clear(); }//i.e. dtor
};
int main(){
#if __cplusplus >= 201103L
	DCLL<int> list{1,2,3,4,5},list2{44,55,66};
#else
	DCLL<int> list;
	for(int i=1;i<=5;++i)
		list.push_back(i);
		
#endif
//	for(int i=1;i<=5;++i)
//		list.push_front(i);
	
//	list.pop_front();
//	list.pop_back();

//	list2=list;
//	list2=move(list);//C++11
	
//	list.push_middle(404);
//	list.pop_middle();
	
//	list.clear();
	
//	list.reverse();
	
//	list.insert(3,404);
//	list.erase(3);
	
	list.merge(list2,-1);
	
	list.traverse_forward();
	list.traverse_backward();

//	list2.traverse_forward();
//	list2.traverse_backward();
	return 0;
}
