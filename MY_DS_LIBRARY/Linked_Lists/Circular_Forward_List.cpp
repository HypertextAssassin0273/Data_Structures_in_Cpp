#include "Circular_Forward_List.hpp"

/* Circular Singly Linked List Operations: */
int main(){
#if __cplusplus >= 201103L
	Circular_Forward_List<int> list({1,2,3,4,5}), list2;
#else
	Circular_Forward_List<int> list;
	for(int i=1;i<=5;++i)
		list.push_back(i);
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
	
//	list.insert(3, 404);
//	list.erase(3);
	
	list.traverse();
//	list2.traverse();
	
    return 0;
}
