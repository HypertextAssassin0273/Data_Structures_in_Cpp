#include "String.hpp"

void test_case_1(){
		String s="abcd";

//	s.reserve(10);

	s.push_back('z');
//	s.pop_back();
	
	s.shrink_to_fit();
	
//	s.insert('z');
//	s.erase();
	
	s.insert('k', 2);
//	s.erase(2);
	
	s.resize(8, 'o');
	
	std::cout<<"string: "<<s
			 <<"\nsize: "<<s.size()
			 <<"\ncapacity: "<<s.capacity();
}

void test_case_2(){
	std::string s="AA",s2="AAbc";
//	String s="AA",s2="BB";
	
	std::cout<<("AAbc">=s?"true":"false");
//	std::cout<<(s2>=s?"true":"false");
}

int main(){
//	test_case_1();
	test_case_2();
		
	return 0;
}
