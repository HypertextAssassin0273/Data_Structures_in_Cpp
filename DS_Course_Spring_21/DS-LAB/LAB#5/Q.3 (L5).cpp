#include<iostream>
using namespace std;

#if __cplusplus < 201103L
	const short nullptr=0L;
#endif

#define N 12

template<typename T>
class linked_list{
	struct node{
	    T data;
    	node *next;
    	
    	node(T data):data(data),next(nullptr){}//i.e. ctor

	}*head;
public:
	linked_list():head(nullptr){}//i.e. default ctor
	
	void add_node_at_back(const T& new_data){//Complexity: O(n)
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
	static void calc_avg_for_list2(const linked_list& list1,linked_list& list2){
		if(!list1.head){
       		cout<<"List is empty!"<<endl;
        	return;
    	}
    	node* temp1=list1.head;
    	for(int i=0;i<N/4;++i){
    		float sum=0;
    		for(int j=0;temp1&&j<4;++j){
				sum+=temp1->data;
				temp1=temp1->next;
			}
			list2.add_node_at_back(sum/4);
    	}
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
	linked_list<float> list1,list2;
	int val;
	cout<<"Enter "<<N<<" no.s: "<<endl;
	for(int i=0;i<N;++i){
		cin>>val;
		list1.add_node_at_back(val);
	}
	
	linked_list<float>::calc_avg_for_list2(list1,list2);
	cout<<"\nlist1 (user-input): "<<endl;
	list1.display_nodes();
	cout<<"\nlist2 (avg-list): "<<endl;
	list2.display_nodes();
	return 0;
}
