#include "F_Stack.hpp"
#include "HF_Stack.hpp"
#include "../Contiguous_Structures/String.hpp"

using std::cout;
using std::cin;

void Fixed_Size_Array_Stack_Operations(){
	const int cc=5;//chunk capacity

#if __cplusplus >= 201103L
	F_Stack<String, cc> s({"lol", "great", "woah!"});
#else
	F_Stack<String, cc> s;
	
	s.push("lol");
	s.push("great");
	s.push("woah!");
#endif
	
	s.pop();
	
	s.push("taebak!");
	
	s.erase(1);
	
	s.insert("ss1");
	
	s.insert("ss2", 1);
	
	F_Stack<String, cc> s2=s;//copy construction
	
	cout<<"values: "<<s2
		<<"\ntop value: "<<(s2.empty()?"":s2.peek())
		<<"\n2nd value: "<<s2[2-1]
		<<"\nsize: "<<s2.size();
	
	cout<<"\n\nupdating exsiting "<<s.size()<<" values of 's' F_Stack:-\n";
	cin>>s;
	
	cout<<"\nvalues: "<<s
		<<"\ntop value: "<<(s.empty()?"":s.peek());
}

#if __cplusplus >= 201103L
void Heap_based_Fixed_Size_Array_Stack_Operations(){
	const int cc=5;//chunk capacity
	
	HF_Stack<String, cc> s({"lol", "great", "woah!"});
//	HF_Stack<String, cc> s; s.push("lol"); s.push("great"); s.push("woah!");
	
	s.pop();
	
	s.push("taebak!");
	
	s.erase(1);
	
	s.insert("ss1");
	
	s.insert("ss2", 1);
	
	HF_Stack<String, cc> s2=s;//copy construction
	
	cout<<"values: "<<s2
		<<"\ntop value: "<<(s2.empty()?"":s2.peek())
		<<"\n2nd value: "<<s2[2-1]
		<<"\nsize: "<<s2.size();
	
	cout<<"\n\nupdating exsiting "<<s.size()<<" values of 's' HF_Stack:-\n";
	cin>>s;
	
	cout<<"\nvalues: "<<s
		<<"\ntop value: "<<(s.empty()?"":s.peek());
}
#endif

int main(){
	Fixed_Size_Array_Stack_Operations();
//	Heap_based_Fixed_Size_Array_Stack_Operations();
	
	return 0;
}
