#include<iostream>
using namespace std;

#if __cplusplus < 201103L
	const short nullptr=0L;
#endif

class linked_list{
protected:
	struct node{
	    int data;
    	node *next;
    	
    	node(int data):data(data),next(nullptr){}//i.e. ctor
    	
    	static void swap_data(node &xp,node &yp){//i.e. swaps current data
			int temp=xp.data;
	 		xp.data=yp.data;
			yp.data=temp;
		}
	}*head;
public:
	linked_list():head(nullptr){}//i.e. default ctor
    
    void insert_at_front(int new_data){//Order: LIFO -> stack/descending order, Best-Case: O(1) Complexity
        node *new_node=new node(new_data);
        new_node->next=head;
		//i.e. join previous nodes (pointed by head_ptr) to newly created node's next_ptr
        head=new_node;
		//i.e.  assign address of newly created node (alongwith all nodes) to head_ptr
		cout<<"Element Inserted Successfully!"<<endl;
    }
    void insert_at_back(int new_data){//Order: FIFO -> queue/ascending order, Worst-Case: O(n) Complexity
        if(!head)
            head=new node(new_data);
        else{
        	node *temp=head;
        	while(temp->next)
        		temp=temp->next;
        	//i.e. traversing the temp_ptr to reach last position (by checking 'nullptr' in next_ptr)
			temp->next=new node(new_data);
			//i.e. inserting new_node at end of list
        }
        cout<<"Element Inserted Successfully!"<<endl;
	}
    void delete_first(){//Order: FIFO -> queue order, Best-Case: O(1) Complexity
    	if(!head){
    	    cout<<"List is empty!"<<endl;
    	    return;
    	}
    	node *temp=head->next;
		delete head;
    	head=temp;
    	cout<<"Element deleted Successfully!"<<endl;
	}
	void delete_end(){//Order: LIFO -> stack order, Worst-Case: O(n) Complexity
		if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	if (!head->next){
	        delete head;
	        head=nullptr;
    	}
    	else{
			node *temp=head;
        	while(temp->next->next)
        		temp=temp->next;
        	delete temp->next;
        	temp->next=nullptr;//Error if removed!
		}
        cout<<"Element Deleted Successfully!"<<endl;
    }
	void insert_at_position(int pos,int new_data){
		if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	if(pos<2){
    		insert_at_front(new_data);
    		return;
    	}
    	int count=0;
		node *temp=head;
		while(temp){
    		++count;
    		temp=temp->next;
		}
		if(pos>count){
			insert_at_back(new_data);
			return;
		}
		temp=head;
		for(int i=0;i<pos-2;++i)
    		temp=temp->next;
    	node* temp2=temp->next;
    	temp->next=new node(new_data);
    	temp->next->next=temp2;
    	cout<<"Element Inserted Successfully!"<<endl;
	}
	void delete_at_position(int pos){
		if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	if(pos<2){
    		delete_first();
    		return;
    	}
    	int count=0;
		node *temp=head;
		while(temp){
    		++count;
    		temp=temp->next;
		}
		if(pos>count){
			delete_end();
			return;
		}
		temp=head;
		for(int i=0;i<pos-2;++i)
    		temp=temp->next;
    	node* temp2=temp->next->next;
    	delete temp->next;
    	temp->next=temp2;
    	cout<<"Element Deleted Successfully!"<<endl;
	}
	void sort(){//i.e. improved bubble sort, using data-swap
    	if (!head||!head->next){//i.e. do nothing if size is 0 or 1
    	    cout<<"List is either empty or has only 1 element!"<<endl;
			return;
		}
		for(node *ptr,*lptr=nullptr;true;lptr=ptr){
	        bool swapped=false;
	        for (ptr=head;ptr->next!=lptr;ptr=ptr->next)
            	if (ptr->data>ptr->next->data){//i.e. ascending order
 	    	    	node::swap_data(*ptr,*ptr->next);
    	            swapped=true;
            	}
        	if(!swapped)
        		break;
    	}
    	cout<<"Elements Sorted Successfully!"<<endl;
	}
	void reverse_list(){
		if(head){
			reverse_node_order(head);
			cout<<"Elements Reversed Successfully!"<<endl;
		}
		else
			cout<<"List is empty!"<<endl;
	}
	void mean(){
		if(!head){
			cout<<"List is empty!"<<endl;
			return;
		}
		float avg=0,count=0;
		node *temp=head;
		while(temp){
			++count;
    		avg+=temp->data;
    		temp=temp->next;	
		}
		cout<<"mean: "<<avg/count<<endl;
	}
	void maximum(){
		if(!head){
			cout<<"List is empty!"<<endl;
			return;
		}
		node *temp=head;
		int max=temp->data;
		while(temp){
    		if(temp->data>max)
    			max=temp->data;
    		temp=temp->next;	
		}
		cout<<"maximum: "<<max<<endl;
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
	~linked_list(){//i.e. dtor
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
	}
	
private:
	node* reverse_node_order(node *temp){//i.e. worst-case: O(n)
		if(!temp->next)
			head=temp;
		else{
			reverse_node_order(temp->next)->next=temp;//i.e. direct assigning to returned ptr's next_ptr
			temp->next=nullptr;
		}
		return temp;
	}
};

int main(){
	unsigned int choice,value,pos;
	linked_list list;
	while(true){
		cout<<"\n    !!! MENU !!!"
			<<"\n ^^^^^^^^^^^^^^^^^^\n"
			  " 1) Traverse List\n"
			  " 2) Insert at Front\n"
		  	  " 3) Insert at End\n"
			  " 4) Insert at Position\n"
		  	  " 5) Delete at Position\n"
		  	  " 6) Delete First\n"
		  	  " 7) Delete End\n"
		  	  " 8) Find Maximum\n"
		      " 9) Find Mean\n"
		  	  "10) Sort List\n"
		  	  "11) Reverse List\n"
		  	  "12) Exit\n"
		  	  "==> ";
		cin>>choice;
		system("cls");
		switch (choice){
			case 1:
				list.traverse();
				break;
			case 2:
				cout<<"Enter value: ";
				cin>>value;
				list.insert_at_front(value);
				break;
			case 3:
				cout<<"Enter value: ";
				cin>>value;
				list.insert_at_back(value);
				break;
			case 4:
				cout<<"Enter value: ";
				cin>>value;
				cout<<"Enter position: ";
				cin>>pos;
				list.insert_at_position(pos,value);
				break;
			case 5:
				cout<<"Enter position: ";
				cin>>pos;
				list.delete_at_position(pos);
				break;
			case 6:
				list.delete_first();
				break;
			case 7:
				list.delete_end();
				break;
			case 8:
				list.maximum();
				break;
			case 9:
				list.mean();
				break;
			case 10:
				list.sort();
				break;
			case 11:
				list.reverse_list();
				break;
			case 12:
				return 0;
		}
		//i.e. clears input buffer if user inputs something wrong
		fflush(stdin);
		cin.clear();
	}
    return 0;
}
