#include<iostream>
using namespace std;

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
class SCLL{//i.e. Singly Circular Linked-List
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
public:
	SCLL()noexcept:tail(nullptr){}//i.e. default ctor
	
#if __cplusplus >= 201103L  
	//i.e.initializer_list based ctor
	SCLL(initializer_list<T> list)noexcept:tail(nullptr){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	SCLL(const SCLL &other)noexcept:tail(nullptr){//i.e. copy ctor
		if(!other.tail)
			return;
		node *it=other.tail->next;
		do{
    		push_back(it->data);//1) copy other's data
    		it=it->next;
		}while(it!=other.tail->next);
    }
    SCLL& operator=(const SCLL &other)noexcept{//i.e. copy assignment func.
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
 	SCLL(SCLL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		tail(other.tail){//1) steal other's data
		other.tail=nullptr;//2) set other's ptr to null state
	}
 	
	SCLL& operator=(SCLL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();//1) clear existing resources
  		tail=other.tail;//2) steal other's data
  		other.tail=nullptr;//3) set other to null state
  		return *this;
	}
#endif
	/* accessors */
	T& back()const{
		if (tail)
			return tail->data;
		throw false;
	}
	T& front()const{
		if (tail)
			return tail->next->data;
		throw false;
	}
	
	/* modifiers */
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_front(_T&&... new_data){//i.e. direct initialization is also possible
		node* new_node=new node(new_data...);
#else
    void push_front(const T& new_data){//Complexity: O(1)
		node* new_node=new node(new_data);
#endif
		if(!tail){
			tail=new_node;
			tail->next=tail;
		}
		else{
			new_node->next=tail->next;
        	tail->next=new_node;
		}
    }
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_back(_T&&... new_data){
		node* new_node=new node(new_data...);
#else
    void push_back(const T& new_data){//Complexity: O(1)
    	node* new_node=new node(new_data);
#endif
		if(!tail){
			tail=new_node;
			tail->next=tail;
		}
		else{
			new_node->next=tail->next;
     		tail->next=new_node;
    	    tail=new_node;
		}
	}
	void pop_front(){//Complexity: O(1)
		if(!tail)
        	return;
    	if (tail->next==tail){
	        delete tail;
	        tail=nullptr;
	        return;
    	}
    	node *temp=tail->next->next;
    	delete tail->next;
    	tail->next=temp;
    }
    void pop_back(){//Complexity:O(n)
    	if(!tail)
    	    return;
    	if (tail->next==tail){
	        delete tail;
	        tail=nullptr;
	        return;
    	}
    	node* head=tail->next,*temp=head;
        while(temp->next!=tail)
        	temp=temp->next;
        delete tail;
        tail=temp;
        tail->next=head;//i.e. converting to circular again by joining link
	}
    void traverse()const{
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
	
	~SCLL(){ clear(); }//i.e. dtor
};

int main(){
	SCLL<int> circular_list;
	circular_list.push_back(5);
	circular_list.push_back(2);
	circular_list.push_back(3);
	circular_list.push_back(4);
	circular_list.push_back(1);
	circular_list.push_back(6);
	
	cout<<"1 router & its 6 end devices: ";
	circular_list.traverse();
	return 0;
}
