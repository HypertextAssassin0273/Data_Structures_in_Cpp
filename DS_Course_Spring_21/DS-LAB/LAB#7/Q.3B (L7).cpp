#include<iostream>
using namespace std;

//Note: include "Doubly_Linked_List.hpp" after including iostream & using namespace std
#include"Doubly_Linked_List.hpp"

int main(){
#if __cplusplus >= 201103L
	DLL<int> list{3,-1,7,5,4};
#else
	DLL<int> list;
	list.push_back(3);
	list.push_back(-1);
	list.push_back(7);
	list.push_back(5);
	list.push_back(4);
#endif
	cout<<"Before Sort:"<<endl;
	list.traverse_forward();
	list.traverse_backward();
	list.sort();//i.e. using alternate to insertion-sort in ascending order
//	list.sorted_insert(2);//extra
	cout<<"After Sort:"<<endl;
	list.traverse_forward();
	list.traverse_backward();
	return 0;
}
