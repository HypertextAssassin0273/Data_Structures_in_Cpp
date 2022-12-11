#include<iostream>
using namespace std;

#if __cplusplus < 201103L
	const short nullptr=0L;
#define noexcept
#endif

class linked_list{//i.e. Singly Linked-List   
    struct node{
	    int data;
    	node *next;
    	
    	node(const int& data)noexcept:
			data(data),next(nullptr){}
	};
    typedef unsigned int __uint32;
    __uint32 _size;
	node *head;
public:
	linked_list()noexcept:head(nullptr),_size(0){}
	
	int size()const{ return _size; }
	
	void push_front(const int& val){
		node*new_node=new node(val);
		new_node->next=head;
		head=new_node;
		++_size;
	}
	void push_front(node* new_node){
		new_node->next=head;
		head=new_node;
		++_size;
	}
//	void push_back(const int& new_data){
//    	node *new_node=new node(new_data);
//		if(!head){
//    		head=new_node;
//    		return;
//		}
//        node *temp=head;
//        while(temp->next)
//        	temp=temp->next;
//		temp->next=new_node;
//	}
    void push_back(node* new_node){
		if(!head){
    		head=new_node;
    		return;
		}
        node *temp=head;
        while(temp->next)
        	temp=temp->next;
		temp->next=new_node;
		++_size;
	}
	node* pop_front(){
		if(!head)
			return nullptr;
		node *holder=head;
		head=head->next;
		--_size;
		holder->next=nullptr;
		return holder;
	}
//    node* pop_back(){
//    	if(!head)
//			return nullptr;
//		if(!head->next){
//			node *holder=head;
//			head=nullptr;
//			--_size;
//			return holder;
//		}
//		node *temp=head,*holder=nullptr;
//		for(;temp->next->next;temp=temp->next);
//		holder=temp->next;
//		temp->next=nullptr;
//		--_size;
//		return holder;
//	}
	node* pop_random(int val){
		if(head->data==val)
			return pop_front();
		node *temp=head;
		for(;temp->next&&temp->next->data!=val;temp=temp->next);
		if(!temp->next)
			return nullptr;
		node* temp2=temp->next->next,*holder=temp->next;
		temp->next=temp2;
		--_size;
		holder->next=nullptr;
		return holder;
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
			_size=0;
		}
	}
	~linked_list(){ clear(); }
};

struct orders{
	int query_no,index;
	orders(int query_no=0,int index=0):query_no(query_no),index(index){}
	
};

int main(){
	int n=7;
//	int n;
//	cout<<"Sample Input: "<<endl;
//	cin>>n;

	orders order[n]={{1,2},{1,5},{1,7},{1,9},{2,5},{2,7},{4,5}};
//	orders order[n];
//	cout<<"Input orders: "<<endl;
//	for (int i=0;i<n;++i)
//		cin>>order[i].query_no>>order[i].index;

	linked_list pending_section,delivered_section,cancel_section;
	
	for (int i=10;i>0;--i)//1-10
		pending_section.push_front(i);

	for (int i=0;i<n;++i)
		switch(order[i].query_no){
			case 1:
				delivered_section.push_back(pending_section.pop_random(order[i].index));
				break;
			case 2:
				cancel_section.push_back(delivered_section.pop_random(order[i].index));
				break;
			case 3:
				cancel_section.push_back(pending_section.pop_random(order[i].index));
				break;
			case 4:
				pending_section.push_back(cancel_section.pop_random(order[i].index));
				break;
		}
	cout<<"Output:"<<endl;
	pending_section.traverse();
	delivered_section.traverse();
	cancel_section.traverse();
	return 0;
}
