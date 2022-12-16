#include "SLL.hpp"

//task#7:
//1) even numbers appear before all the odd numbers
//2) keep the order of even and odd numbers same

template<>
void SLL<int>::rearrange_even_nos_at_beginning(){
	if(!(head&&head->next)) return;//if elements > 2, only then continue
	
	node *odd_head=nullptr,*even_head=nullptr,//temporary even_list
		 *odd_tail=nullptr,*even_tail=nullptr;//temporary odd_list
	
	bool flag=head->data%2;//saves previous element's state (odd->1,even->0) w.r.t 'current' node ptr
	node *prev=head,*cur=head->next;
	while(cur){
		if(flag){//odd list operations
			while(cur&&cur->data%2){//traverse odd_list till an even element appears
				cur=cur->next;
				prev=prev->next;
			}
			
			if(!odd_head)//set head for odd_list (one time only)
				odd_head=head;
			
			if(odd_tail)//join previous odd_list (if present) with new odd_list
				odd_tail->next=head;
			
			odd_tail=prev;//reset odd_tail to newly appended odd_list's tail
			
			flag=false;//even_list turn
		}
		else{//even list operations
			while(cur&&!(cur->data%2)){//traverse even_list till an odd element appears
				cur=cur->next;
				prev=prev->next;
			}
			
			if(!even_head)//set head for even_list (one time only)
				even_head=head;
			
			if(even_tail)//join previous even_list (if present) with new even_list
				even_tail->next=head;
			
			even_tail=prev;//reset even_tail to newly appended even_list's tail
			
			flag=true;//odd_list turn
		}
		
		head=cur;//set head for the start of next temporary (even/odd) list
	}
	
	//joining connections (3 cases)
	if(even_head){//case 1: even_list is present
		head=even_head;
		if(odd_tail){//case 2: odd_list is also present alongwith even
			even_tail->next=odd_head;
			odd_tail->next=nullptr;
		}
	}
	else//case 3: only odd_list is present
		head=odd_head;
}

int main(){
#if __cplusplus >= 201103L
	/* test_case_1 (mixed, general): */
//	SLL<int> list({17,15,8,12,10,5,4,1,7,6});//ascending order: push_backs => O(N^2)
	SLL<int> list({6,7,1,4,5,10,12,8,15,17},true);//descending order: push_fronts => O(N)
	/*tip: if possible, insert data in descending order to reduce complexity in SLL*/
	
	/* test_case_2 (all even): */
//	SLL<int> list({8,12,10});
	
	/* test_case_3 (all odd): */
//	SLL<int> list({1,3,5,7});
#else
	SLL<int> list;
	/* test_case_1 (mixed, general): */
	list.push_back(17); list.push_back(15); list.push_back(8);
	list.push_back(12); list.push_back(10); list.push_back(5);
	list.push_back(4); list.push_back(1); list.push_back(7);
	list.push_back(6);
	
	/* test_case_2 (all even): */
//	list.push_back(8); list.push_back(12); list.push_back(10);
	
	/* test_case_3 (all odd): */
//	list.push_back(1); list.push_back(3); list.push_back(5);
//	list.push_back(7);
#endif
	
	std::cout<<"before: "<<list;//traverses in list order
	
	list.rearrange_even_nos_at_beginning();
	
	std::cout<<"\n\nafter: "<<list;
    
	return 0;
}
