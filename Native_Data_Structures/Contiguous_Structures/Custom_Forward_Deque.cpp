#include"Forward_Deque.hpp"
#include"Sorts.hpp"

void basic_operations(){
	Forward_Deque<int,8> list,//i.e. default ctor
						 list2(33,444);//i.e. (emplaced) fill ctor
	Forward_Deque<int,8> list3{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};//i.e. initializer-list ctor (C++11)
	Forward_Deque<int,8> list4(list);//i.e. copy ctor
//	Forward_Deque<int,8> list5(move(list));//i.e. move ctor (C++11)
	
	cout<<boolalpha<<(list<list2)<<' '<<(list==list2)<<'\n';//i.e. comparison operators
	
//	for(auto& it:list3)//C++11
//		cout<<it<<' ';
	for(Forward_Deque<int,8>::iterator it=list.begin();it!=list.end();++it)//for both versions
		cout<<*it<<' ';
	cout<<'\n';
	
	for(auto& it:list3.r_iterator())//C++11
		cout<<it<<' ';
//	for(Forward_Deque<int,8>::reverse_iterator it=list2.rbegin();it!=list2.rend();++it)
//		cout<<*it<<' ';
	
//	for(Forward_Deque<int,8>::sf_iterator it=list3.sfbegin()+1;it<list3.sfend()-5;++it)//prints 2 to 15
//		cout<<*it<<' ';
	
//	cout<<list2.size()<<' '<<list2.capacity()<<'\n'
//		<<list2<<'\n';//i.e. uses stream operator
}

void pointer_invalidation_test(){// Vector vs Forward_Deque
//	Vector<string> s1(5,"lol");//i.e. invalidates pointers to elements
	Forward_Deque<string,4> s1(5,"lol");//i.e. doesn't invalidate pointers
	string* ptr=s1+3;
	cout<<*ptr;
	s1.push_back("haha");
	cout<<*ptr;//i.e. gives error for pointing previously pointed element in Vector<string> container
}

void sort_by_iterators_test(){
#if __cplusplus >= 201103L
	Forward_Deque<int> fd{2,-32,12,3,6,5,8,1,9,2,-67,45,401,901,99,111};
	//Note: try to avoid using initializer-list in projects as it performs one extra copy of each element
#else
	Forward_Deque<int> fd;
	fd.reserve(7);
	fd.push_back(2); fd.push_back(-32);
	fd.push_back(12); fd.push_back(3);
	fd.push_back(6); fd.push_back(5);
	fd.push_back(8); fd.push_back(1);
	fd.push_back(9); fd.push_back(2);
	fd.push_back(-67); fd.push_back(45);
	fd.push_back(401); fd.push_back(901);
	fd.push_back(99); fd.push_back(111);
#endif
	
	cout<<"BEFORE SORTING: "<<fd<<endl;
	
	//NOTE: only special forward & reverse iterators will work here
	Sort::Bubble(fd.sfbegin(),fd.sfend());
//	Sort::Insertion(fd.sfbegin(),fd.sfend());
//	Sort::Selection(fd.sfbegin(),fd.sfend());
//	Sort::Quick(fd.sfbegin(),fd.sfend());

	cout<<"AFTER SORTING: "<<fd<<endl;
}

struct heavy{//i.e. 1 heavy object == 10,000 bytes
	char d1[2000];
	int d2[2000];
};
void reallocation_speed_test(){// Vector vs STL::Deque vs Forward_Deque
	Forward_Deque<heavy,10000> x;
//	deque<heavy> x;//i.e. takes avg. 7.06 secs (NOTE: need to include deque header-file first for testing)
//	Vector<heavy> x;//i.e. takes avg. 27.56 secs
	
	for(int i=0;i<Vector<string>::max_capacity/3000;++i)
		x.push_back(heavy());
	cout<<x.size()*sizeof(heavy);//i.e. Forward_Deque allocates these bytes in avg 4.77 secs with 10,000 chunk_size
	
	/*WARNING:
	  	 I've performed this test according to my PC environment. you must have enough free RAM space,
		 otherwise system will crash (i.e. memory allocation is set for 14GB RAM size)
	  SIDE-NOTES:
	  1) STL::Deque has no template argument for taking chunk_size (due to some security rule).
		 Instead, it decides the size at compile-time by comparing the type-size with some constant values.
		 Anyways, here, the chunk_size of STL:::deque is 16 or 32. If we set same chunk_size of Forward_Deque,
		 we'll get almost same results.
	  2) The time taken by these different containers varies on each system/machine, but the end-result is same.
	*/
}


int main(){
/*NOTE: you can use all use-cases of 'Vector' for 'Forward_Deque' provided in 'Custom_Vector_and_String.cpp' file */
	
	basic_operations();
//	sort_by_iterators_test();
//	pointer_invalidation_test();
//	reallocation_speed_test();
	return 0;
}

