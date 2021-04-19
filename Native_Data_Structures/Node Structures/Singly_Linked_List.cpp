#include<iostream>
using namespace std;

#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#endif

template<typename T>
class SLL{//i.e. Singly Linked-List
    typedef unsigned long long __uint64;
	typedef unsigned int __uint32;

    struct node{
	    T data;
    	node *next;
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)noexcept://i.e. emplaced ctor
			data{std::forward<_T>(data)...},next(nullptr){}
	#endif
    	static void swap_data(node &xp,node &yp){//i.e. swaps current data
			T temp=xp.data;
	 		xp.data=yp.data;
			yp.data=temp;
		}
		
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
	
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	SLL(initializer_list<T> list)noexcept:head(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	SLL(const SLL &other)noexcept:head(nullptr),_size(other._size){//i.e. copy ctor
    	for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//1) copy other's data
    }
    SLL& operator=(const SLL &other)noexcept{//i.e. copy assignment func.
    	if(this==&other)//i.e. self-assignment protection
    		return *this;
		clear();//1) clear existing resources
        for(node *it=other.head;it;it=it->next)
           	push_back(it->data);//2) copy other's data
        return *this;
    }
#if __cplusplus >= 201103L
 	SLL(SLL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		head(other.head),_size(other._size){//1) steal other's data
		other.head=nullptr; other._size=0;//2) set other's ptr to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	SLL& operator=(SLL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		head=other.head; _size=other._size;//2) steal other's data
  		other.head=nullptr; other._size=0;//3) set other to null state
  		return *this;
	}
#endif
   
   /* Accessors & Mutators */
#if __cplusplus >= 201103L
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
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. direct initialization is also possible
		push_front(GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
    }
    void push_front(node* new_node){
        new_node->next=head;
        head=new_node;
		++_size;
    }
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){
		push_back(GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
    void push_back(const T& new_data){//Complexity: O(n)
    	push_back(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_back(node *new_node){
		if(!head)
    		head=new_node;
        else{
        	node *temp=head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
        }
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
	node* pop_back(bool flag=false){//Complexity: O(n)
		if(!head)
        	return nullptr;
        node* popped=nullptr;
    	if (!head->next){
			if(flag)
				popped=head; 
			else 
				GC.push(head);
	        head=nullptr;
    	}
    	else{
		    node *temp=head;
        	for(;temp->next->next;temp=temp->next);
        	if(flag)
				popped=temp->next; 
			else
				GC.push(temp->next);
        	temp->next=nullptr;
		}
        --_size;
    	return popped;
    }
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){
		push_middle(GC.ptr?GC.pop(new_data...):new node(new_data...));
#else
	void push_middle(const T& new_data){
	    push_middle(GC.ptr?GC.pop(new_data):new node(new_data));
#endif
	}
	void push_middle(node *new_node){
		if(!head)
			head=new_node;
        else{
			node *slow_ptr=head,*fast_ptr=head->next;
    	    while(fast_ptr&&fast_ptr->next){
    	        fast_ptr=fast_ptr->next->next;
    	       	slow_ptr=slow_ptr->next;
    	    }
		    new_node->next=slow_ptr->next;
		    slow_ptr->next=new_node;
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
	        head=nullptr;
    	}
    	else{
		    node *slow_ptr=head,*fast_ptr=head,*prev;
	        while(fast_ptr&&fast_ptr->next){
	           	fast_ptr=fast_ptr->next->next;
	           	prev=slow_ptr;
	           	slow_ptr=slow_ptr->next;
	    	}
	        prev->next=slow_ptr->next;
	    	if(flag) 
				popped=slow_ptr;
			else
				GC.push(slow_ptr);
		}
    	--_size;
    	return popped;
	}
#if __cplusplus >= 201103L
	template<typename... _T>
	void insert(__int64 index,_T&&... new_data){
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
		temp->next->next=temp2;
		++_size;
	}
	node* erase(__int64 index,bool flag=false){
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
    	--_size;
    	return popped;
	}
	void swap_nodes(__uint64 posX,__uint64 posY){
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
	void swap_data(__uint64 posX,__uint64 posY){
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
	void remove_consecutive_duplicates(){
		if (head)//i.e. do nothing if size is 0
        	remove_consecutive_duplicates_recursively(head);
	}
	//TODO:
	//void remove_all_duplicates();
    
//	bool detect_loop(){//i.e. Floyd’s Cycle Algorithm (extra)
// 	   	node *slow_ptr=head,*fast_ptr=head;
//    	while (slow_ptr&&fast_ptr&&fast_ptr->next){
//    	    slow_ptr=slow_ptr->next;
//    	    fast_ptr=fast_ptr->next->next;
//    	    if (slow_ptr==fast_ptr)
//    	        return true;
//    	}
//    	return false;
//	}
	void reverse(){
		if(head)
			reverse_recursively(head);
		else
			cout<<"List is empty!"<<endl;
	}
    void traverse()const{
    	if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	node *temp=head;
		while(temp){
    		cout<<temp->data<<" ";
    		temp=temp->next;
		}
		cout<<endl;
	}
	void clear(){
		node* temp;
			while(head){
	   			temp=head->next;
	    		GC.push(head);
    			head=temp;	
			}
		_size=0;
	}
	
private: /*i.e. hidden recursive methods*/
	void remove_consecutive_duplicates_recursively(node* temp){//i.e. only for sorted data
    	if (temp->next){
        	if (temp->data==temp->next->data){
            	node* to_delete=temp->next;
        		temp->next=temp->next->next;
        		GC.push(to_delete);
        		--_size;
        		remove_consecutive_duplicates_recursively(temp);
        	}
        	else //i.e. advances only if no deletion
	            remove_consecutive_duplicates_recursively(temp->next); 
   	 	}
	}
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
	/*static methods (for two list based operations)*/
	static void swap(SLL &list1,SLL &list2){
	 	std::swap(list1,list2);
	}
	//TO-DO:
	//static void swap_nodes(SLL<T> &list1,int pos1,SLL<T> &list2,int pos2);
	
	static void merge(SLL &list1,SLL &list2,int pos){
		if(!list2.head||pos>list1._size)
			return;//i.e. do nothing if list2 have no nodes or size exceeds the given pos
		node *temp;
		if(!pos){//i.e. if pos is '0', then directly join head of list2 to head of list1
			temp=list1.head;
			list1.head=list2.head;
		}
		else{
			node *list1_temp=list1.head;
			for(int i=1;i<pos;++i)
				list1_temp=list1_temp->next;
			temp=list1_temp->next;
			list1_temp->next=list2.head;
		}
		while(list2.head->next)
			list2.head=list2.head->next;
		list2.head->next=temp;
		list2.head=nullptr;
		list1._size+=list2._size;
		list2._size=0;
	}
	
	/* Iterator */
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
	
	/* Garbage Collector Operations */
	static void clear_gc(){ GC.clear(); }//i.e. destroys all the preserved nodes in garbage_collector of 'T' type
	static void release_gc(){ GC.release(); }//i.e. destroys half of the total preserved nodes....
	
	~SLL(){ clear(); }//i.e. dtor
};
template<typename T>
typename SLL<T>::garbage_collector SLL<T>::GC;


class Fun{//i.e. for testing
	char c;
	int i;
	string s;
public:
	Fun(char c='\0',int i=0,string s=""):c(c),i(i),s(s){}
	
	friend ostream& operator<<(ostream& out,const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<endl;
		return out;
	}
};

void test_case_1(){
	#if __cplusplus >= 201103L
	SLL<int> list1={1,2,4,5},list2;
#else
    SLL<int> list1,list2;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(4);
	list1.push_back(5);
#endif
	cout<<"List1 (int):"<<endl;
    list1.traverse();
	list1.push_middle(3);
	list1.traverse();
	cout<<"List2 (int):"<<endl;
	for(short i=7;i<12;++i)
		list2.push_back(i);
	list2.traverse();
	
	cout<<"\nAfter Swapping Nodes (pos 2-> pos 5):-\nList1:"<<endl;
	list1.swap_nodes(2,5);
	list1.traverse();
	cout<<"\nAfter Swapping Data (val 7-> value 10):-\nList2:"<<endl;
	list2.swap_data(7,10);
	list2.traverse();
	
	SLL<int>::merge(list1,list2,2);
	cout<<"\nAfter Merge:-\nList1:"<<endl;
	list1.traverse();
	cout<<"List2:"<<endl;
	list2.traverse();
	
	cout<<"\nTrying all insert/delete operations:-\nList1:"<<endl;
    list1.pop_back();
    list1.traverse();
    list1.pop_front();
    list1.traverse();
    list1.pop_middle();
    list1.traverse();
    list1.push_front(0);
    list1.traverse();
    list1.push_back(9);
    list1.traverse();
    cout<<"List2:"<<endl;
	list2.push_back(9);
	list2.push_back(8);
	list2.traverse();
	
	SLL<int>::swap(list1,list2);
    cout<<"\nAfter Swap:-\nList1:"<<endl;
	list1.traverse();
	cout<<"List2:"<<endl;
    list2.traverse();
    
    cout<<"\nAfter Reverse:-\nList2:"<<endl;
	list2.reverse();
	list2.traverse();
	list2.push_front(9);
	list2.push_front(0);
	list2.traverse();
	
	cout<<"\nAfter BubbleSort (Ascending order):-\nList2:"<<endl;
	list2.sort();
	list2.traverse();
	cout<<"list2 size: "<<list2.size()<<endl;
	
	cout<<"\nAfter Removing Consecutive Duplicates:-\nList2:"<<endl;
	list2.remove_consecutive_duplicates();
	list2.traverse();
	cout<<"list2 size: "<<list2.size()<<endl;
	
    cout<<"\nAfter deleting all nodes:-\nList2:"<<endl;
    list2.clear();
    list2.traverse();
    for(short i=25;i>0;--i)
    	list2.push_front(i);
    list2.traverse();
    cout<<"list2 size: "<<list2.size()<<endl;
    
	cout<<"\nUsing copy ctor (list 2-> list 3):-"<<endl;
	SLL<int> list3=list2;
    cout<<"List2:"<<endl;
	list2.traverse();
	cout<<"List3 (int):"<<endl;
	list3.traverse();
	
	cout<<"\nUsing copy assignment func. (list 1-> list 2):-"<<endl; 
	list2=list1;
    cout<<"List1:"<<endl;
	list1.traverse();
    cout<<"List2:"<<endl;
	list2.traverse();
	
#if __cplusplus >= 201103L
	SLL<int> list4={55,66,77,88,99};
#else
    SLL<int> list4;
    for(int i=55;i<110;i+=11)
		list4.push_back(i);
#endif
	SLL<int>::merge(list4,list2,2);
	cout<<"\nAfter merging (list 2 -> list 4):-"<<endl; 
	cout<<"List2:"<<endl;
	list2.traverse();
    cout<<"List4 (int):"<<endl;
	list4.traverse();
	cout<<"After random delete at 5th position:\nList4:"<<endl;
	list4.erase(5);
	list4.traverse();
	cout<<"After random insert at 3rd position:\nList4:"<<endl;
	list4.insert(3,404);
	list4.traverse();
	
	list1.clear();
	list3.clear();
	list4.clear();
	SLL<int>::clear_gc();//i.e. releasing all nodes of int type
	
#if __cplusplus >= 201103L
	cout<<"\nUsing move ctor (list 6-> list 7):-"<<endl;
	SLL<string> list5={"aaa","bbb","ccc","ddd","eee","fff","ggg"},list6=std::move(list5);//{"1-0-1","2-0-2"}
	cout<<"list 6 (strings):"<<endl;
	list5.traverse();
	cout<<"list 7 (strings):"<<endl;
	list6.traverse();
	
	cout<<"\nUsing move assignment func. (list 7-> list 6):-"<<endl; 
	list5=std::move(list6);
    cout<<"List6:"<<endl;
	list5.traverse();
    cout<<"List7:"<<endl;
	list6.traverse();

	Fun obj1,obj2('1',2,"3");
	
	SLL<Fun> list8;
	list8.push_front(obj1);
	list8.push_back(obj2);
	list8.push_back('2',3,"4");//i.e. direct initialization
	list8.push_back('3',4);
	list8.push_back(Fun('4',5,"6"));//i.e. moving temporary obj
	list8.insert(1,'$',40404,"\"random-insert at pos 2\"");
	list8.erase(1);
	cout<<"\nList8 ('Fun' type objs):"<<endl;
	list8.traverse();
#endif
}

void test_case_2(){//i.e. C.R.U.D Operations on Stack
	SLL<int> list;
	short choice;
	while (true){
		cout<<"\nSELECT YOUR CHOICE:-\n"
			<<"\n1. Insert value (at front)"
			<<"\n2. Update Value (random)"
			<<"\n3. Delete value (at front)"
			<<"\n4. View List"
			<<"\n5. Exit\n\n";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		switch (choice){
		case 1:{
			int val;
			cout<<"Enter value: ";
			cin>>val;
			list.push_front(val);
			break;
		}
		case 2:{
			int val,n;
			cout<<"Enter index: ";
			cin>>n;
			if(n<list.size()){
				cout<<"Enter value: ";
				cin>>val;
				list[n]=val;
			}
			break;
		}
		case 3:
			list.pop_front();
			break;
		case 4:
			cout<<"List: ";
			list.traverse();
			break;
		case 5:
			return;
		}
	}
}


int main(){
//	test_case_1();//use of all operations
	test_case_2();//using SLL as stack (best-case)
    return 0;
}
