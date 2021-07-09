#include<iostream>
using namespace std;

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
    	
    #if __cplusplus < 201103L
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr){}
    #else
    	template<typename... _T>
		node(_T&&... data)noexcept://i.e. emplaced ctor
			data{std::forward<_T>(data)...},next(nullptr){}
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
	node* new_node(_T&&... new_data)const{ return new node(new_data...); }
#else
	node* new_node(const T& new_data)const{ return new node(new_data); }
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
		push_front(new node(new_data...));
#else
    void push_front(const T& new_data){//Complexity: O(1)
		push_front(new node(new_data));
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
		push_back(new node(new_data...));
#else
    void push_back(const T& new_data){//Complexity: O(n)
    	push_back(new node(new_data));
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
			delete head;
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
				delete head;
	        head=nullptr;
    	}
    	else{
		    node *temp=head;
        	for(;temp->next->next;temp=temp->next);
        	if(flag)
				popped=temp->next; 
			else
				delete temp->next;
        	temp->next=nullptr;
		}
        --_size;
    	return popped;
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
	T find(int index){//i.e. GetNth
		if(index>=0){
    		node* temp=head;
    		for(int i=0;temp;++i,temp=temp->next)
    	    	if (i==index)
    	    		return temp->data;
		}
		return T();
	}
	void clear(){
		node* temp;
			while(head){
	   			temp=head->next;
	    		delete head;
    			head=temp;	
			}
		_size=0;
	}
	
	~SLL(){ clear(); }//i.e. dtor
};


int main(){
	SLL<int> list;
	list.push_front(40);
	list.push_front(30);
	list.push_front(20);
	list.push_front(10);

	cout<<"List contains: ";
	list.traverse();
	
	int index;
	cout<<"\nEnter the index no. : ";
	cin>>index;
	
	cout<<"The element at index "<<index<<" is: "<<list.find(index);
	return 0;
}
