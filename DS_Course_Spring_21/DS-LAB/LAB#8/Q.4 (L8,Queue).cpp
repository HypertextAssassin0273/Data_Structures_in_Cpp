#include<iostream>
#include <conio.h>
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
    	
    #if __cplusplus < 201103L
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
		if(n==_size-1)
			return tail->data;
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
	
	/*Method for calculating the tour for petrol_pump class*/
	int calculate_tour();
	
	~DCLL(){ clear(); }//i.e. dtor
};

struct petrol_pump{
    int petrol,distance;
    
	petrol_pump(int petrol=0,int distance=0)noexcept:
		petrol(petrol),distance(distance){}
	
	friend ostream& operator<<(ostream& out,const petrol_pump& self){
		out<<'{'<<self.petrol<<","<<self.distance<<'}';
		return out;
	}
};

template<>
int DCLL<petrol_pump>::calculate_tour(){
	if(!tail)
		return -1;
    node *start=tail->next,*end=tail->next->next;//i.e. tail->next = head
    int index=0,curr_petrol=start->data.petrol-start->data.distance;
    while(start!=end||curr_petrol<0){
        while(curr_petrol<0&&start!=end){
             curr_petrol-=start->data.petrol-start->data.distance;
        	start=start->next;
        	index=(index+1)%_size;
            if (!start)
            	return -1;
        }
    	curr_petrol+=end->data.petrol-end->data.distance;
 		end=end->next;
    }
    return index;
}

int main(){
#if __cplusplus >= 201103L
	DCLL<petrol_pump> list={{4,6},{6,5},{7,3},{4,5}};
#else
	DCLL<petrol_pump> list;
	list.push_back(petrol_pump(4,6));
	list.push_back(petrol_pump(6,5));
	list.push_back(petrol_pump(7,3));
	list.push_back(petrol_pump(4,5));
#endif
	cout<<"Set of Petrol Pumps: ";
	list.traverse_forward();
	cout<<"Start: "<<list.calculate_tour();
	return 0;
}
