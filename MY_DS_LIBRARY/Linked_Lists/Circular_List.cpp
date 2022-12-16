#include "Circular_List.hpp"

/* Circular Doubly Linked List Operations: */
int main(){
#if __cplusplus >= 201103L
	Circular_List<int> list({1,2,3,4,5}), list2({44,55,66});
#else
	Circular_List<int> list, list2;
	for(int i=1;i<=5;++i)
		list.push_back(i);
	for(int i=44;i<=66;i+=11)
		list2.push_back(i);
#endif
	
//	for(int i=1;i<=5;++i)
//		list.push_front(i);
	
//	list.pop_front();
//	list.pop_back();

//	list2=list;
//	list2=std::move(list);//C++11
	
//	list.push_middle(404);
//	list.pop_middle();
	
//	list.clear();
	
//	list.reverse();
	
//	list.insert(3, 404);
//	list.erase(3);
	
//	list.merge(list2, 5);//tail boundary case not handled!
	
	list.traverse_forward();
	list.traverse_backward();

//	list2.traverse_forward();
//	list2.traverse_backward();
	
	return 0;
}
