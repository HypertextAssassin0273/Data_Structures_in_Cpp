#include "../Utilities/Type_Convertors.hpp" //needs to be included before Forward_Deque
#include "../Algorithms/Sorts.hpp"
#include "Segmented_Vector.hpp"
#include "String.hpp"

using std::cout;
using std::string;

void ctor_and_iterator_versions(){
	constexpr int CC=8;//chunk capacity (can only be defined at compile time)
	typedef Segmented_Vector<int, CC> sv;
	
	sv list;//default ctor
	sv list2(33, 444);//(emplaced) fill ctor
	sv list3({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20});//initializer-list ctor
	sv list4(list);//copy ctor
	sv list5(std::move(list));//move ctor
	
	cout<<"comaparisons: "<<std::boolalpha
		<<(list<list2)<<' '<<(list2==list3)<<'\n';//using comparison operators
	
	cout<<"\ntraverse elements using sv::iterator:\n";
	for(auto& it:list3)//range-based loop
		cout<<it<<' ';
//	for(sv::iterator it=list3.begin();it!=list3.end();++it)//actual deduction for above range-based 'for' loop
//		cout<<*it<<' ';
	
	cout<<"\n\ntraverse elements using sv::reverse_iterator:\n";
	for(auto& it:list3.r_iterator_adapter())
		cout<<it<<' ';
//	for(sv::r_iterator it=list3.rbegin();it!=list3.rend();++it)
//		cout<<*it<<' ';
	
	cout<<"\n\ntraverse elements using cout overloaded method:\n";
	cout<<list3<<'\n'
		<<"size: "<<list3.size()<<", capacity: "<<list3.capacity();
}

void vector_like_operations(){
	/* testing push_backs & pop_backs affect: */
//	Segmented_Vector<int, 6> l;
//	
//	for(int i=1;i<=11;++i)
//		l.push_back(i);
//	
//	cout<<l<<"\nsize: "<<l.size()<<", capacity: "<<l.capacity()<<'\n';
//	
//	for(int i=0;i<5;++i)
//		l.pop_back();
//	
//	cout<<l<<"\nsize: "<<l.size()<<", capacity: "<<l.capacity();
	
	/* testing reserve & chunk modifiers: */
	Segmented_Vector<int, 6> l2({1,2,3,4,5,6,7,8,9,10,11,12,13});
	
	l2.reserve(18);
	
	cout<<l2<<"\nsize: "<<l2.size()<<", capacity: "<<l2.capacity()<<"\n\n";
	
	auto v=convert::to_Vector(l2.release_chunk(1));//releases middle chunk & converts it into vector
	v.pop_back();
	cout<<l2<<"\nsize: "<<l2.size()<<", capacity: "<<l2.capacity()
		<<"\nreleased vector: "<<v<<"(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\n\n";
	
	//WARNING: insert_chunk isn't ready for handling all cases yet
	l2.insert_chunk(HF_Stack<int, 6>({71,72,73,74,75,76}));//insert at front (note: chunk must be fully constructed)
	
	cout<<l2<<"\nsize: "<<l2.size()<<", capacity: "<<l2.capacity()<<"\n\n";
	
	l2.insert_chunk(convert::to_HF_Stack<6>(std::move(v)), 3);//re-insert converted vector at middle (not allowed since size == 5)
//	l2.insert_chunk(convert::to_HF_Stack<6>(std::move(v)), 2);//re-insert converted vector at last (allowed for chunk size < capacity)
	
	cout<<l2<<"\nsize: "<<l2.size()<<", capacity: "<<l2.capacity()
		<<"\ninserted vector: "<<v<<"(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<'\n';
	
	for(auto& it:l2)
		cout<<it<<' ';
	
	/* testing combine use of resize & shrink_to_fit modifier: */
//	Segmented_Vector<int, 6> l3({1,2,3,4,5,6,7,8,9,10,11});
//	cout<<l3<<"\nsize: "<<l3.size()<<", capacity: "<<l3.capacity()<<'\n';
//	
//	l3.resize(3);
//	
//	cout<<l3<<"\nsize: "<<l3.size()<<", capacity: "<<l3.capacity()<<'\n';
//	
//	l3.shrink_to_fit();
//	
//	cout<<l3<<"\nsize: "<<l3.size()<<", capacity: "<<l3.capacity()<<'\n';

	/* testing shift modifiers: */
//	Segmented_Vector<int, 4> l4({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18});
//	
//	cout<<l4<<"\nsize: "<<l4.size()<<", capacity: "<<l4.capacity()<<'\n';
//	
//	l4.insert(404);
////	l4.insert(404, 15);
//	
////	l4.erase();
////	l4.erase(15);
//	
//	cout<<l4<<"\nsize: "<<l4.size()<<", capacity: "<<l4.capacity()<<'\n';
}

void pointer_invalidation_test(){//Vector vs Segmented_Vector
	String *ptr;
	constexpr int total_elems=5;
	
/* Note: To test both containers, uncomment & check one at a time */
//	Vector<String> string_list;	
	Segmented_Vector<String, total_elems> string_list;
	
	string_list.reserve(total_elems);
	
	for(int i=0;i<total_elems;++i)
		string_list.push_back(String("Str_")+std::to_string(i+1));
	
	ptr=&string_list.back();
	
	cout<<ptr<<' '<<string_list+(total_elems-1)<<" ==> "<<(ptr==string_list+(total_elems-1)?"same":"different")
		<<", pointed string: "<<*ptr<<'\n';//before reallocation
	
	string_list.push_back("new string");
	
	cout<<ptr<<' '<<string_list+(total_elems-1)<<" ==> "<<(ptr==string_list+(total_elems-1)?"same":"different")
		<<", pointed string: "<<*ptr<<'\n';//after reallocation
	/*Result:
		After reallocation, we have null pointed string in Vector.
		Whereas in Segmented_Vector, we have same pointed string.
		Hence, Segmented_Vector doesn't invalidates pointer & Vector does.
	*/
}

void sort_by_iterators_test(){
	Segmented_Vector<int, 6> sv({2,-32,12,3,6,5,8,1,9,2,-67,45,401,901,99,111});
	//Note: try to avoid using initializer-list in bigger projects as it performs one extra copy of each element
	
	cout<<"BEFORE SORTING: "<<sv<<'\n';
	
//	sort::bubble(sv.begin(), sv.end());
//	sort::selection(sv.begin(), sv.end());
	sort::insertion<int>(sv.begin(), sv.end());
//	sort::quick(sv.begin(), sv.end());
	
	cout<<"AFTER SORTING: "<<sv<<'\n';
}

void reallocation_speed_test(){// Vector vs STL::Deque vs Segmented_Vector
	struct heavy{//local struct (C++11)
		char d1[2000];
		int d2[2000];
	};//Note: here, 1 heavy object == 10,000 bytes
	
	Segmented_Vector<heavy, 32> x;//takes avg. 6.17 secs
//	std::deque<heavy> x;//takes avg. 6.61 secs [NOTE: need to include deque header-file first for testing]
//	Vector<heavy> x;//takes avg. 7.46 secs
	
	for(int i=0;i<Vector<string>::max_capacity/5000;++i)
		x.push_back(heavy());
	cout<<x.size()*sizeof(heavy);
	//note: Segmented_Vector allocates these bytes in avg 2.96 secs with 512 chunk_size (ideal chunk factor)
	
	/*WARNING:
	  	 I've performed this test according to my PC environment. you must have enough free RAM space,
		 otherwise system will crash (memory allocation is set for approx. 14GB RAM size)
	  SIDE-NOTES:
	  1) STL::Deque has no template argument for taking chunk_size (due to some security rule).
		 Instead, it decides the size at compile-time by using some efficiency factor algorithm.
		 Anyways, here, the chunk_size of STL:::deque is 16 or 32. If we set same chunk_size of Segmented_Vector,
		 we'll still get slightly better results in Segmented_Vector than std::deque.
	  2) The time taken by these different containers varies on each system/machine, but the end-result is same.
	*/
}


int main(){
/*NOTE: you can use all use-cases of 'Vector' for 'Segmented_Vector' too, provided in 'Vector.cpp' file */
	
//	ctor_and_iterator_versions();
	vector_like_operations();
//	pointer_invalidation_test();
//	sort_by_iterators_test();
//	reallocation_speed_test();
	
 return 0;
}

