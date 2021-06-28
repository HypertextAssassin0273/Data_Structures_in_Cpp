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
	int count_duplicates(int search_for){
		if(!head){
       		cout<<"List is empty!"<<endl;
        	return 0;
    	}
    	node *temp=head;
    	int counter=0;
		while(temp){
    		if(temp->data==search_for)
				++counter;
    		temp=temp->next;
		}
		return counter;
	}
	~linked_list(){
		node* temp;
		while(head){
	   		temp=head->next;
	    	delete head;
    		head=temp;	
		}
	}
};

int main(){
#if __cplusplus >= 201103L
	linked_list my_list={1,2,3};
#else
	linked_list my_list;
	my_list.add_node_at_back(1);
	my_list.add_node_at_back(2);
	my_list.add_node_at_back(3);
#endif
	cout<<"Total Duplicates of 2: "<<my_list.count_duplicates(2);
	return 0;
}
