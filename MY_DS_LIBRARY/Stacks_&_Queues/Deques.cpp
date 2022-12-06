#include "F_Deque.hpp"
#include "Deque.hpp"
#include "../Contiguous_Structures/String.hpp"

using std::cout;

void test_case_1(){//fixed size deque implemented as circular array
#if __cplusplus >= 201103L
	F_Deque<String, 8> q({"lol", "great", "woah", "ddd", "404", "doctor", "dew"});
#else
	F_Deque<String, 8> q;
	
	q.push_back("lol");
	q.push_back("great");
	q.push_back("woah!");
	q.push_back("ddd");
	q.push_back("404");
	q.push_back("doctor");
	q.push_back("dew");
#endif
	
	q.pop_front();
	q.pop_front();
	
	q.push_back("taebak!");
	q.push_back("good!");
	q.push_back("chill!");
	
	q.pop_front();
	q.pop_front();
	
	q.push_back("awesome");
	q.push_back("wreck");
	q.push_back("extra");
	
	F_Deque<String, 8> q2=q;//copy construct
//	F_Deque<String, 8> q2=std::move(q);//move construct [C++11]
	
	cout<<"values: "<<q
		<<"\n1st value: "<<(q.empty()?"":q.front())
		<<"\n2nd last value: "<<(q.empty()?"":*(q-1))
		<<"\nsize: "<<q.size();
	
	cout<<"\n\nvalues: "<<q2
		<<"\n1st value: "<<(q2.empty()?"":q2.front())
		<<"\n2nd last value: "<<*(q2-1)
		<<"\nsize: "<<q2.size();
	
	cout<<"\n\ntraverse by queue iterator:\n";
//	for(auto& it:q) //C++11
//		cout<<it<<' ';
	for(F_Deque<String, 8>::iterator it=q.begin();it!=q.end();++it)
		cout<<*it<<' ';
	
	cout<<"\n\ntraverse by queue reverse_iterator:\n";
//	for(auto& it:q.r_iterator_adapter()) //C++11
//		cout<<it<<' ';
	for(F_Deque<String, 8>::r_iterator it=q.rbegin();it!=q.rend();++it)
		cout<<*it<<' ';
}

void test_case_2(){//fixed size deque implemented as circular array
	F_Deque<String, 14> q;

	for(int i=1;i<=8;++i)
		q.push_back(std::string()+(char)(48+i)+'a');
	//alternates: std::to_string(i)+'a', String({(char)(48+i), 'a', '\0'})
	
	for(int i=1;i<=4;++i)
		q.pop_back();
	
	for(int i=1;i<=3;++i)
		q.push_front(std::string()+(char)(48+i)+'b');
	
	for(int i=0;i<2;++i)
		q.pop_front();
	
	for(int i=1;i<=6;++i)
		q.push_back(std::string()+(char)(48+i)+'c');
	
	cout<<"values: "<<q
		<<"\nsize: "<<q.size()
		<<"\n\n";
	
	q.erase(6);
	
	q.insert("Nn", 4);
	
	cout<<"values: "<<q
		<<"\nsize: "<<q.size();
}


void test_case_3(){//dynamic size deque implemented as circular array
#if __cplusplus >= 201103L
	Deque<String> q({"lol", "great", "woah", "ddd", "404", "doctor", "dew"});
#else
	Deque<String> q;
	
	q.reserve(8);
	
	q.push_back("lol");
	q.push_back("great");
	q.push_back("woah!");
	q.push_back("ddd");
	q.push_back("404");
	q.push_back("doctor");
	q.push_back("dew");
#endif
	
	q.pop_front();
	q.pop_front();
	
	q.push_back("taebak!");
	q.push_back("good!");
	q.push_back("chill!");
	
	q.pop_front();
	q.pop_front();
	
	q.push_back("awesome");
	q.push_back("wreck");
	q.push_back("no_more_extra");
	
	Deque<String> q2=q;//copy construct
//	Deque<String> q2=std::move(q);//move construct [C++11]
	
	cout<<"values: "<<q
		<<"\n1st value: "<<(q.empty()?"":q.front())
		<<"\n2nd last value: "<<(q.empty()?"":*(q-1))
		<<"\nsize: "<<q.size()
		<<"\ncapacity: "<<q.capacity();
	
	cout<<"\n\nvalues: "<<q2
		<<"\n1st value: "<<(q2.empty()?"":q2.front())
		<<"\n2nd last value: "<<*(q2-1)
		<<"\nsize: "<<q2.size()
		<<"\ncapacity: "<<q2.capacity();
		
	cout<<"\n\ntraverse by deqeue iterator:\n";
//	for(auto& it:q2) //C++11
//		cout<<it<<' ';
	for(Deque<String>::iterator it=q2.begin();it!=q2.end();++it)
		cout<<*it<<' ';
	
	cout<<"\n\ntraverse by deqeue reverse_iterator:\n";
//	for(auto& it:q2.r_iterator_adapter()) //C++11
//		cout<<it<<' ';
	for(Deque<String>::r_iterator it=q2.rbegin();it!=q2.rend();++it)
		cout<<*it<<' ';
}

void test_case_4(){//dynamic size deque implemented as circular array
	Deque<String> q;
	
	q.reserve(14);
	
	for(int i=1;i<=8;++i)
		q.push_back(std::string()+(char)(48+i)+'a');
	//alternates: std::to_string(i)+'a', String({(char)(48+i), 'a', '\0'})
	
	for(int i=1;i<=4;++i)
		q.pop_back();
	
	for(int i=1;i<=3;++i)
		q.push_front(std::string()+(char)(48+i)+'b');
	
	for(int i=0;i<2;++i)
		q.pop_front();
	
	for(int i=1;i<=6;++i)
		q.push_back(std::string()+(char)(48+i)+'c');
	
	cout<<"values: "<<q
		<<"\nsize: "<<q.size()
		<<"\ncapacity: "<<q.capacity()
		<<"\n\n";
	
	q.erase(6);
	
	q.insert("Nn", 4);
	
	cout<<"values: "<<q
		<<"\nsize: "<<q.size()
		<<"\ncapacity: "<<q.capacity()
		<<"\n\n";
	
//	q.clear();

//	q.shrink_to_fit();
	
	q.resize(15, "ss");
	
	cout<<"values: "<<q
		<<"\nsize: "<<q.size()
		<<"\ncapacity: "<<q.capacity()
		<<"\n\n";
	
}


int main(){
	/* fixed deque operations */
//	test_case_1();
//	test_case_2();
	
	/* dynamic deque operations */
	test_case_3();
//	test_case_4();
	
	return 0;
}
