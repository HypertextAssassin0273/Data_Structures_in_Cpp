#include"Forward_List.hpp"

using std::string;
using std::cin;

class Fun{//i.e. for testing
	char c;
	int i;
	string s;
public:
	Fun(char c='\0',int i=0,string s=""):c(c),i(i),s(s){}
	
	friend std::ostream& operator<<(std::ostream& out,const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<'\n';
		return out;
	}
};

void test_case_1(){
	#if __cplusplus >= 201103L
	Forward_List<int> list1={1,2,4,5},list2;
#else
    Forward_List<int> list1,list2;
	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(4);
	list1.push_back(5);
#endif
	cout<<"List1 (int):"<<'\n';
    list1.traverse();
	list1.push_middle(3);
	list1.traverse();
	cout<<"List2 (int):"<<'\n';
	for(short i=7;i<12;++i)
		list2.push_back(i);
	list2.traverse();
	
	cout<<"\nAfter Swapping Nodes (pos 2-> pos 5):-\nList1:"<<'\n';
	list1.swap_nodes(2,5);
	list1.traverse();
	cout<<"\nAfter Swapping Data (val 7-> value 10):-\nList2:"<<'\n';
	list2.swap_data(7,10);
	list2.traverse();
	
	list1.merge(list2,2);
	cout<<"\nAfter Merge:-\nList1:"<<'\n';
	list1.traverse();
	cout<<"List2:"<<'\n';
	list2.traverse();
	
	cout<<"\nTrying all insert/delete operations:-\nList1:"<<'\n';
    list1.pop_back();
    list1.traverse();
    list1.pop_front();
    list1.traverse();
    list1.pop_middle();
    list1.traverse();
    list1.push_front(0);
    list1.traverse();
    list1.push_back(9);
    list1.traverse();
    cout<<"List2:"<<'\n';
	list2.push_back(9);
	list2.push_back(8);
	list2.traverse();
	
	std::swap(list1,list2);
    cout<<"\nAfter Swap:-\nList1:"<<'\n';
	list1.traverse();
	cout<<"List2:"<<'\n';
    list2.traverse();
    
    cout<<"\nAfter Reverse:-\nList2:"<<'\n';
	list2.reverse();
	list2.traverse();
	list2.push_front(9);
	list2.push_front(0);
	list2.traverse();
	
	cout<<"\nAfter BubbleSort (Ascending order):-\nList2:"<<'\n';
	list2.sort();
	list2.traverse();
	cout<<"list2 size: "<<list2.size()<<'\n';
	
	cout<<"\nAfter Removing Consecutive Duplicates:-\nList2:"<<'\n';
	list2.remove_consecutive_duplicates();
	list2.traverse();
	cout<<"list2 size: "<<list2.size()<<'\n';
	
    cout<<"\nAfter deleting all nodes:-\nList2:"<<'\n';
    list2.clear();
    list2.traverse();
    for(short i=25;i>0;--i)
    	list2.push_front(i);
    list2.traverse();
    cout<<"list2 size: "<<list2.size()<<'\n';
    
	cout<<"\nUsing copy ctor (list 2-> list 3):-"<<'\n';
	Forward_List<int> list3=list2;
    cout<<"List2:"<<'\n';
	list2.traverse();
	cout<<"List3 (int):"<<'\n';
	list3.traverse();
	
	cout<<"\nUsing copy assignment func. (list 1-> list 2):-"<<'\n'; 
	list2=list1;
    cout<<"List1:"<<'\n';
	list1.traverse();
    cout<<"List2:"<<'\n';
	list2.traverse();
	
#if __cplusplus >= 201103L
	Forward_List<int> list4={55,66,77,88,99};
#else
    Forward_List<int> list4;
    for(int i=55;i<110;i+=11)
		list4.push_back(i);
#endif
	list4.merge(list2,2);
	cout<<"\nAfter merging (list 2 -> list 4):-"<<'\n'; 
	cout<<"List2:"<<'\n';
	list2.traverse();
    cout<<"List4 (int):"<<'\n';
	list4.traverse();
	cout<<"After random delete at 5th position:\nList4:"<<'\n';
	list4.erase(5);
	list4.traverse();
	cout<<"After random insert at 3rd position:\nList4:"<<'\n';
	list4.insert(3,404);
	list4.traverse();
	
	list1.clear();
	list3.clear();
	list4.clear();
	Forward_List<int>::clear_gc();//i.e. releasing all nodes of int type
	
#if __cplusplus >= 201103L
	cout<<"\nUsing move ctor (list 6-> list 7):-"<<'\n';
	Forward_List<string> list5={"aaa","bbb","ccc","ddd","eee","fff","ggg"},list6=std::move(list5);//{"1-0-1","2-0-2"}
	cout<<"list 6 (strings):"<<'\n';
	list5.traverse();
	cout<<"list 7 (strings):"<<'\n';
	list6.traverse();
	
	cout<<"\nUsing move assignment func. (list 7-> list 6):-"<<'\n'; 
	list5=std::move(list6);
    cout<<"List6:"<<'\n';
	list5.traverse();
    cout<<"List7:"<<'\n';
	list6.traverse();

	Fun obj1,obj2('1',2,"3");
	
	Forward_List<Fun> list8;
	list8.push_front(obj1);
	list8.push_back(obj2);
	list8.push_back('2',3,"4");//i.e. direct initialization
	list8.push_back('3',4);
	list8.push_back(Fun('4',5,"6"));//i.e. moving temporary obj
	list8.insert(1,'$',40404,"\"random-insert at pos 2\"");
	list8.erase(1);
	cout<<"\nList8 ('Fun' type objs):"<<'\n';
	list8.traverse();
#endif
}

void test_case_2(){//i.e. C.R.U.D Operations on Stack
	Forward_List<int> list;
	short choice;
	while (true){
		cout<<"\nSELECT YOUR CHOICE:-\n"
			<<"\n1. Insert value (at front)"
			<<"\n2. Update Value (random)"
			<<"\n3. Delete value (at front)"
			<<"\n4. View List"
			<<"\n5. Exit\n\n";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		switch (choice){
		case 1:{
			int val;
			cout<<"Enter value: ";
			cin>>val;
			list.push_front(val);
			break;
		}
		case 2:{
			int val,n;
			cout<<"Enter index: ";
			cin>>n;
			if(n<list.size()){
				cout<<"Enter value: ";
				cin>>val;
				list[n]=val;
			}
			break;
		}
		case 3:
			list.pop_front();
			break;
		case 4:
			cout<<"List: ";
			list.traverse();
			break;
		case 5:
			return;
		}
	}
}


int main(){
//	test_case_1();//use of all operations
	test_case_2();//using Forward_List as stack with LIFO order (best-case)
    return 0;
}
