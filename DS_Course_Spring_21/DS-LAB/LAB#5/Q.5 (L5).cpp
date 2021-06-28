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
		for(const auto& it:list)
        	add_node_at_back(it);
	}
#endif
	void add_node_at_back(const int& new_data){
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
	static float mean_of_odd_fibonacci_nos(const linked_list& list1,int range=20){
		linked_list odd_fib_list;
		node *temp=list1.head;
		while(temp){
			for(int i=1;i<=range;++i)
    			if(temp->data==get_fibonacci_no(i)){
    				odd_fib_list.add_node_at_back(temp->data);
    				break;
    			}
    		temp=temp->next;
		}
		
		temp=odd_fib_list.head;
		int counter=0; float sum=0;
		while(temp){
			if(temp->data%2){
				sum+=temp->data;
				++counter;
			}
			temp=temp->next;
		}
		return sum/counter;
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
	static int get_fibonacci_no(int N){
		if (N==1||N==2)
			return 1;
		return (get_fibonacci_no(N-1)+get_fibonacci_no(N-2));
	}
};

int main(){
#if __cplusplus >= 201103L
	linked_list list={5,21,8,12,3,13,144,6};
#else
	linked_list list;
	list.add_node_at_back(5);
	list.add_node_at_back(21);
	list.add_node_at_back(8);
	list.add_node_at_back(12);
	list.add_node_at_back(3);
	list.add_node_at_back(13);
	list.add_node_at_back(144);
	list.add_node_at_back(6);
#endif
	cout<<"Input: ";
	list.display_nodes();
	cout<<"Output: "<<linked_list::mean_of_odd_fibonacci_nos(list);
	return 0;
}
