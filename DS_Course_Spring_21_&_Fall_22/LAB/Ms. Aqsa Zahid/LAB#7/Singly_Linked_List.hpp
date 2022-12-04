#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#endif

template<typename T>
class SLL{//i.e. Singly Linked-List   
    struct node{
	    T data;
    	node *next;
    	
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr){}
		
    	static void swap_data(node &xp,node &yp){//i.e. swaps current data
			T temp=xp.data;
	 		xp.data=yp.data;
			yp.data=temp;
		}
	};
    
	node *head;
public:
	SLL()noexcept:head(nullptr){}//i.e. default ctor
	
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	SLL(initializer_list<T> list)noexcept:head(nullptr){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	void sort(bool=true);
	
    void push_back(const T& new_data){//Complexity: O(n)
    	node *new_node=new node(new_data);
		if(!head){
    		head=new_node;
    		return;
		}
        node *temp=head;
        while(temp->next)
        	temp=temp->next;
		temp->next=new_node;
	}
    void traverse()const{
    	if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		cout<<it->data<<" ";
		cout<<endl;
	}
	void clear(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
	}
	~SLL(){ clear(); }//i.e. dtor
};
