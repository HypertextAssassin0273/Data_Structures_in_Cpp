#include<iostream>
using namespace std;

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename T>
struct node{
	T data;
    node *next;  	
    
    node(const T& data=T())noexcept:
		data(data),next(nullptr){}

	static node* intersection(node* head1,node* head2){
		if (!head1||!head2)
			return nullptr;
		node *temp1=head1,*temp2=head2;
		while(temp1!=temp2){
			temp1=temp1->next; 
			temp2=temp2->next;
			if(temp1==temp2)
				return temp1;
			if (!temp1)
            temp1=head2;
        	if (!temp2)
            temp2=head1;
		}
		return temp1;
	}
};

template<typename T>
struct stack{
	node<T> *head;

	stack()noexcept:
		head(nullptr){}
	
	void push_front(node<T> *new_node){
		new_node->next=head;
		head=new_node;
	}
	void push_back(node<T> *new_node){
		if(!head)
    		head=new_node;
        else{
        	node<T> *temp=head;
        	while(temp->next)
        		temp=temp->next;
			temp->next=new_node;
        }
	}
	friend ostream& operator<<(ostream& out,const stack& self){
		for(node<T>* temp=self.head;temp;temp=temp->next)
			out<<temp->data<<" ";
		return out;
	}
};

int main(){
	stack<int> stack1;
	stack1.push_front(new node<int>(30));
	node<int>* temp=new node<int>(15);
	stack1.push_front(temp);
	stack1.push_front(new node<int>(9));
	stack1.push_front(new node<int>(6));
	stack1.push_front(new node<int>(3));
	
	stack<int> stack2;
	stack2.push_back(temp);//Note: can't use push_front for more than 1 node
	stack2.push_front(new node<int>(10)); 
	
	cout<<"Stack1: "<<stack1<<endl;
	cout<<"Stack2: "<<stack2<<endl;
	
	temp=node<int>::intersection(stack1.head,stack2.head);
	cout<<"Intersecting Node: ";
	if(temp)
		cout<<temp->data;
	else
		cout<<"N.I.L";
	return 0;
}
