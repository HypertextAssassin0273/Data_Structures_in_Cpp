#include<iostream>

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
	
		friend std::ostream& operator<<(std::ostream& out,const node& obj){
			out<<obj.data;
			return out;
		}
		friend std::istream& operator<<(std::istream& in,node& obj){
			in>>obj.data;
			return in;
		}
	};

	node *tail;
public:
	SCLL()noexcept:tail(nullptr){}//i.e. default ctor
	
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
    	if(this!=&other){//i.e. self-assignment protection
			clear();//1) clear existing resources
			if(!other.tail)
				return *this;
        	node *it=other.tail->next;
			do{
    			push_back(it->data);//2) copy other's data
    			it=it->next;
			}while(it!=other.tail->next);
    	}
		return *this;
    }
#if __cplusplus >= 201103L
 	SCLL(SCLL&& other)noexcept://i.e. move ctor (C++11 Construct)
  		tail(other.tail){//1) steal other's data
		other.tail=nullptr;//2) set other's ptr to null state
	}//Note: use "-fno-elide-constructors" flag to disable compiler optimization for move ctor (GCC Compilers)
 	
	SCLL& operator=(SCLL&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this!=&other){
			clear();//1) clear existing resources
  			tail=other.tail;//2) steal other's data
  			other.tail=nullptr;//3) set other to null state
  		}
	}
	SCLL(std::initializer_list<T> list)noexcept:tail(nullptr){//i.e.initializer_list based ctor
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
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
		node* new_node=new node(std::forward<_T>(new_data)...);
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
		node* new_node=new node(std::forward<_T>(new_data)...);
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
#if __cplusplus >= 201103L
	template<typename... _T>
	void push_middle(_T&&... new_data){
		if(!tail||tail->next==tail){
			push_back(std::forward<_T>(new_data)...);
			return;
		}
		node *new_node=new node(std::forward<_T>(new_data)...);
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
	    slow_ptr->next=new_node;
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
        prev->next=slow_ptr->next;
    	delete slow_ptr;
	}
    void traverse()const{
    	if(!tail){
       		std::cout<<"List is empty!"<<'\n';
        	return;
    	}
    	node *temp=tail->next;
    	do{
    		std::cout<<*temp<<' ';
    		temp=temp->next;
		}while(temp!=tail->next);
		std::cout<<'\n';
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
#if __cplusplus >= 201103L
	SCLL<int> list{1,2,3,4,5},list2;
#else
	SCLL<int> list;
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
	
	list.traverse();
//	list2.traverse();
    return 0;
}
