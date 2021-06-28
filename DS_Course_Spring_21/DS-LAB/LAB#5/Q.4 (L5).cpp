#include<iostream>
using namespace std;

#if __cplusplus < 201103L
	const short nullptr=0L;
#endif

class linked_list{
	struct node{
	    int data;
    	node *next;
    	
    	node(int data):data(data),next(nullptr){}//i.e. ctor

	}*head;
public:
	linked_list():head(nullptr){}//i.e. default ctor
#if __cplusplus >= 201103L
	linked_list(initializer_list<int> list):head(nullptr){
		for(const auto& it:list)//i.e. traversing nodes through iterator
        	add_node_at_back(it);
	}
#endif
	void add_node_at_back(const int& new_data){//Complexity: O(n)
    	if(!head)
    		head=new node(new_data);
        else{
        	node *temp=head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new node(new_data);
        }
	}
	void display_nodes()const{
    	if(!head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	node *temp=head;
		while(temp){
    		cout<<temp->data<<", ";
    		temp=temp->next;
		}
		cout<<endl;
	}
	void swap_1st_odd_with_last_even(){
		if(!head)
        	return;
        
    	node* odd=head;
    	while(odd&&!(odd->data%2))//i.e. finding 1st odd node
    		odd=odd->next;
		if(!odd)
			return;
		
		node *even=find_last_even_node_recursively(head);//i.e. finding last even node
		if(!even)
			return;
		
		int temp=even->data;//i.e. swap data
		even->data=odd->data;
		odd->data=temp;
	}
	~linked_list(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
	}
private:
	node* find_last_even_node_recursively(node *temp)const{
    	static node* even=nullptr;
		if(temp){
    	    find_last_even_node_recursively(temp->next);
    	    if(!even&&!(temp->data%2))
    	     	even=temp;
		}
		return even;
	}
};

int main(){
#if __cplusplus >= 201103L
	linked_list list={4,3,5,2,3};//i.e. test-case 1
//	linked_list list={2,6,8,2};//i.e. test-case 2
#else
	linked_list list;
	//i.e. test-case 1
	list.add_node_at_back(4);
	list.add_node_at_back(3);
	list.add_node_at_back(5);
	list.add_node_at_back(2);
	list.add_node_at_back(3);
	//i.e. test-case 2
//	list.add_node_at_back(2);
//	list.add_node_at_back(6);
//	list.add_node_at_back(8);
//	list.add_node_at_back(2);
#endif
	cout<<"Input: ";
	list.display_nodes();
	list.swap_1st_odd_with_last_even();
	cout<<"Output: ";
	list.display_nodes();
	return 0;
}
