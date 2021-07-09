#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#endif

template<typename T>
class DLL{//i.e. Doubly Linked-List
	typedef unsigned int __uint32;
	
	struct node{
	    T data;
    	node *next,*prev;
    	
    	node(const T& data=T())noexcept://i.e. default ctor
			data(data),next(nullptr),prev(nullptr){}
	};
	
    node *head,*tail;
    __uint32 _size;
public:
	DLL()noexcept:head(nullptr),tail(nullptr),_size(0){}//i.e. default ctor
	
#if __cplusplus >= 201103L
	//i.e.initializer_list based ctor
	DLL(initializer_list<T> list)noexcept:head(nullptr),tail(nullptr),_size(0){
		for(const auto& it:list)//i.e. traversing list through iterator
        	push_back(it);
	}
#endif
	__uint32 size()const{ return _size; }
	
    void push_back(const T& new_data){//Complexity: O(1)
		if(!tail)//i.e. anyone of them can be used to check
    		head=tail=new node(new_data);
        else{
        	node *new_node=new node(new_data);
			new_node->prev=tail;
			tail->next=new_node;
			tail=new_node;
        }
        ++_size;
	}
private:
	void ascending_sorted_insert(node* new_node){
	    if (!head){
	    	head=tail=new_node;
	    	return;
		}
  		if(new_node->data<head->data){
    	    head->prev=new_node;
    	    new_node->next=head;
    	    head=new_node;
    	    return;
    	}
		if(new_node->data>tail->data){
        	new_node->prev=tail;
        	tail->next=new_node;
        	tail=new_node;
        	return;
    	}
    	node *temp=head->next;
    	while (temp->data<new_node->data)
    		temp=temp->next;
    	temp->prev->next=new_node;
    	new_node->prev=temp->prev;
    	temp->prev=new_node;
    	new_node->next=temp;
	}
	void descending_sorted_insert(node* new_node){
	    if (!head){
	    	head=tail=new_node;
	    	return;
		}
  		if(new_node->data>head->data){
    	    head->prev=new_node;
    	    new_node->next=head;
    	    head=new_node;
    	    return;
    	}
		if(new_node->data<tail->data){
        	new_node->prev=tail;
        	tail->next=new_node;
        	tail=new_node;
        	return;
    	}
    	node *temp=tail->prev;
    	while (temp->data<new_node->data)
    		temp=temp->prev;
    	temp->next->prev=new_node;
    	new_node->next=temp->next;
    	temp->next=new_node;
    	new_node->prev=temp;
	}
public:
	void sorted_insert(const T& new_data,bool direction_flag=true){
		if(direction_flag)
			ascending_sorted_insert(new node(new_data));
		else
			descending_sorted_insert(new node(new_data));
		++_size;
	}
	void sort(bool direction_flag=true){//i.e. slightly improved insertion-sort
    	node* current=head;
    	head=tail=nullptr;//i.e. disconnecting links to 'current' list
    	while (current){
        	node* temp=current->next;
        	current->prev=current->next=nullptr;//i.e. disconnecting links to 'current' list
        	if(direction_flag)
				ascending_sorted_insert(current);
			else
				descending_sorted_insert(current);
        	current=temp;
    	}
	}
    void traverse_forward()const{
    	if(!head){
        	return;
    	}
		for(node *it=head;it;it=it->next)
    		cout<<it->data<<" ";
		cout<<endl;
	}
	void traverse_backward()const{
    	if(!tail){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
		for(node *it=tail;it;it=it->prev)
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
		tail=nullptr;
		_size=0;
	}
	~DLL(){ clear(); }//i.e. dtor
};
