#include "List.hpp"
//#include <list>

using std::cout;

/* Doubly Linked List Merge Operation: */
int main(){
#if __cplusplus >= 201103L
	List<int> list({1,2,3,4,5,6,7,8,9}),
			  list2({99,88,77,66,55});
#else
	List<int> list, list2;
	for(int i=1;i<=9;++i)
		list.push_back(i);
	for(int i=99;i>=55;i-=11)
		list2.push_back(i);
#endif
	
	cout<<"BEFORE:-\n"
		<<"list1: "<<list<<" (front: "<<list.front()
					   <<", tail: "<<list.back()<<")\n"
		<<"list2: "<<list2<<" (front: "<<list2.front()
		                <<", tail: "<<list2.back()<<')';
	
	list.merge(list2, 2);
	
	cout<<"\nAFTER:-\n"
		<<"list1: "<<list<<" (front: "<<(list.front_node()?list.front():0)//for exception safety during test
					   <<", tail: "<<(list.back_node()?list.back():0)<<")\n"
		<<"list2: "<<list2<<" (front: "<<(list2.front_node()?list2.front():0)
						<<", tail: "<<(list2.back_node()?list2.back():0)<<')';
	
	return 0;
}
