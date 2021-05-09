#include "List.hpp"

void test_case_1(){
	cout<<"test_case_1:"<<endl;
#if __cplusplus >= 201103L
	List<int> obj{1,2,2,3,3,3},obj2{99,88,77,66,55};
#else
	List<int> obj,obj2;
	for(int i=1;i<=9;++i)
		obj.push_back(i);
	for(int i=99;i>=55;i-=11)
		obj2.push_back(i);
#endif
	obj.traverse_forward();
	//	for(List<int>::iterator<false> it=obj.begin();it!=obj.end();++it)
	//		cout<<*it<<", ";
	
	obj.traverse_backward();
	//	for(List<int>::iterator<true> it=obj.rbegin();it!=obj.rend();++it)
	//		cout<<*it<<", ";
	
	obj.merge(obj2);
	
//	obj.unique();
	
//	obj.sort();
	
//	obj.sorted_insert(404);//i.e. works on sorted data
	
//	obj.erase(5);

//	obj.insert(4,404);

//	obj.push_middle(404);

//	obj.pop_middle();
	
//	for(int i=1;i<=5;++i)
//		obj.push_front(i);
		
//	for(int i=0;i<5;++i)
//		obj.pop_front();
	
//	for(int i=0;i<5;++i)
//		obj.pop_back();
	
	obj.traverse_forward();
	obj.traverse_backward();
}

void test_case_2(){
	List<char> s1={'2','0','1','6'},s2={'2','0','2','0'};

	cout<<"\nEquals to: "<<std::boolalpha<<(s1==s2)<<endl
		<<"Not equals to: "<<(s1!=s2)<<endl
		<<"Greater than: "<<(s1>s2)<<endl
		<<"Less than: "<<(s1<s2)<<endl
		<<"Greater than & equals to: "<<(s1>=s2)<<endl
		<<"Less than & equals to: "<<(s1<=s2)<<endl;
}

void test_case_3(){
	cout<<"\ntest_case_2:"<<endl;
	List<int> mylist;
	
	for (int i=1;i<10;++i)
		mylist.push_back(i);
	
	mylist.resize(5);
 	mylist.resize(8,100);
	mylist.resize(12);
	
#if __cplusplus >= 201103L
	for(const auto& it:mylist)
		cout<<it<<' ';
#else
	for (List<int>::iterator it=mylist.begin();it!=mylist.end();++it)
    	cout<<*it<<' ';
#endif
	cout<<endl;
}

#if __cplusplus >= 201103L
void test_case_4(){
	cout<<"\ntest_case_3:"<<endl;
	List<List<int>> obj{{1,2,3,4,5},{6,7,8,9,10}},obj2;
	
	obj.push_back(11,12,13,14,15);
	obj.push_front(-5,-4,-3,-2,-1);
	
	cout<<"---------------"<<endl;
	for(const auto& _it:obj){
		for(const auto& it:_it.data)
			cout<<it<<" ";
		cout<<endl;
	}
	cout<<"---------------"<<endl;
	for(const auto& _it:obj.reverse_iterator()){
		for(const auto& it:_it.data.reverse_iterator())
			cout<<it<<" ";
		cout<<endl;
	}
//	obj2=obj; 
	obj2=move(obj);//i.e. same as swap
//	obj.swap(obj2);

	cout<<"---------------"<<endl;
	for(const auto& it:obj2)
		it.data.traverse_forward();
	cout<<"---------------"<<endl;
	for(const auto& it:obj2.reverse_iterator())
		it.data.traverse_backward();
	cout<<"---------------"<<endl;
}
#endif

void test_case_5(){//i.e. C.R.U.D Operations on Double-ended Queue
	List<int> list;
	short choice=9; int value=0;
	while(true){
		cout<<"\nSELECT YOUR CHOICE:-"
			<<"\n1. Insert value (at front)"
			<<"\n2. Insert value (at back)"
			<<"\n3. Update Value (at front)"
			<<"\n4. Update Value (at back)"
			<<"\n5. Delete value (at front)"
			<<"\n6. Delete value (at back)"
			<<"\n7. View List (ascending order)"
			<<"\n8. View List (descending order)"
			<<"\n9. Exit\n==> ";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		try{
			switch (choice){
				case 1:
					cout<<"Enter value: ";
					cin>>value;
					list.push_front(value);//i.e. enqueue-front
					break;
				case 2:
					cout<<"Enter value: ";
					cin>>value;
					list.push_back(value);//i.e. enqueue-back
					break;
				case 3:
					cout<<"Enter value: ";
					cin>>list.front();
					break;
				case 4:
					cout<<"Enter value: ";
					cin>>list.back();
					break;
				case 5:
					list.pop_front();//i.e. dequeue-front
					break;
				case 6:
					list.pop_back();//i.e. dequeue-back
					break;
				case 7:
					cout<<"List: ";
					list.traverse_forward();
					break;
				case 8:
					cout<<"List: ";
					list.traverse_backward();
					break;
				case 9:
					return;
			}
		}
		catch(bool){}
	}
}


int main(){
//	test_case_1();//use of all operations
//	test_case_2();//use of comparison operators
//	test_case_3();//use of resize modifier
//	test_case_4();//nested 2D List testing (C++11)
	test_case_5();//using List as double-ended queue
	return 0;
}
