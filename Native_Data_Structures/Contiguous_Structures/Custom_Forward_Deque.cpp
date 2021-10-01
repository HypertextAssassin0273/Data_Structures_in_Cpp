#include"Forward_Deque.hpp"
#include"String.hpp"
#include"Sorts.hpp"

using std::cout;
using std::string;

void basic_operations(){
	const int CC=8; //i.e. chunk capacity
	Forward_Deque<int,CC> list;//i.e. default ctor
	Forward_Deque<int,CC> list2(33,444);//i.e. (emplaced) fill ctor
	Forward_Deque<int,CC> list3{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};//i.e. initializer-list ctor
	Forward_Deque<int,CC> list4(list);//i.e. copy ctor
	Forward_Deque<int,CC> list5(std::move(list));//i.e. move ctor
	
	cout<<std::boolalpha<<(list<list2)<<' '<<(list2==list3)<<'\n';//i.e. comparison operators
	
//	for(auto& it:list3)//range-based loop
//		cout<<it<<' ';
	for(Forward_Deque<int,CC>::iterator it=list3.begin();it!=list3.end();++it)//actual deduction for above range-based 'for' loop
		cout<<*it<<' ';
	cout<<'\n';
	
//	for(auto& it:list3.r_iterator())
//		cout<<it<<' ';
//	for(Forward_Deque<int,CC>::reverse_iterator it=list3.rbegin();it!=list3.rend();++it)
//		cout<<*it<<' ';
	
//	for(Forward_Deque<int,CC>::sf_iterator it=list3.sfbegin()+1;it<list3.sfend()-5;++it)//prints 2 to 15
//		cout<<*it<<' ';
	
//	cout<<list3.size()<<' '<<list3.capacity()<<'\n'
//		<<list3<<'\n';//i.e. uses stream operator
}

void pointer_invalidation_test(){// Vector vs Forward_Deque
	String *ptr;

//Note: To test both containers, uncomment & check below lines one at a time
//	Vector<String> string_list(5,"lol"); string_list.pop_back();	
	Forward_Deque<String,5> string_list(4,"lol");
	
	string_list.push_back("aabbccddeeff12345");
	ptr=&string_list.back();	
	
	cout<<ptr<<' '<<string_list+4<<" ==> "<<(ptr==string_list+4?"same":"different")
		<<", pointed string: "<<*ptr<<'\n';//i.e. before reallocation
	
	string_list.push_back("new string");
	
	cout<<ptr<<' '<<string_list+4<<" ==> "<<(ptr==string_list+4?"same":"different")
		<<", pointed string: "<<*ptr<<'\n';//i.e. after reallocation
	/*Result:
		After reallocation, we have null pointed string in Vector.
		Whereas in Forward_Deque, we have same pointed string.
		Hence, Forward_Deque doesn't invalidates pointer & Vector does.
	*/
}

void sort_by_iterators_test(){
	Forward_Deque<int> fd{2,-32,12,3,6,5,8,1,9,2,-67,45,401,901,99,111};
	//Note: try to avoid using initializer-list in bigger projects as it performs one extra copy of each element

	cout<<"BEFORE SORTING: "<<fd<<'\n';
	
	//NOTE: only special forward & reverse iterators will work here
	Sort::Bubble(fd.sfbegin(),fd.sfend());
//	Sort::Insertion(fd.sfbegin(),fd.sfend());
//	Sort::Selection(fd.sfbegin(),fd.sfend());
//	Sort::Quick(fd.sfbegin(),fd.sfend());

	cout<<"AFTER SORTING: "<<fd<<'\n';
}

void reallocation_speed_test(){// Vector vs STL::Deque vs Forward_Deque
	struct heavy{//i.e. local struct (C++11)
		char d1[2000];
		int d2[2000];
	};//Note: here, 1 heavy object == 10,000 bytes

	Forward_Deque<heavy,10000> x;
//	deque<heavy> x;//i.e. takes avg. 7.06 secs (NOTE: need to include deque header-file first for testing)
//	Vector<heavy> x;//i.e. takes avg. 27.56 secs
	
	for(int i=0;i<Vector<string>::max_capacity/3000;++i)
		x.push_back(heavy());
	cout<<x.size()*sizeof(heavy);//i.e. Forward_Deque allocates these bytes in avg 4.77 secs with 10,000 chunk_size
	
	/*WARNING:
	  	 I've performed this test according to my PC environment. you must have enough free RAM space,
		 otherwise system will crash (i.e. memory allocation is set for approx. 14GB RAM size)
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

