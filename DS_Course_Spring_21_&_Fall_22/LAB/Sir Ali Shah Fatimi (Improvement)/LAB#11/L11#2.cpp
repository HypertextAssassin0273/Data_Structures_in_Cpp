#include "Hashing.hpp"
#include<cmath>
using namespace std;

template<>
int Hash_Map<int, 'M'>::hash(int key)const{ return (int)floor(modf(key*0.5, 0ul)*MAX_SIZE)%MAX_SIZE; }
template<>
int Hash_Map<int, 'S'>::hash(int key)const{ return (key*key)%MAX_SIZE; }
template<>
int Hash_Map<int, 'F'>::hash(int key)const{ return (key%10+(key/10)%10+(key/100)%10)%MAX_SIZE; }
template<>
int Hash_Map<int, 'R'>::hash(int key)const{ return (key/10)%MAX_SIZE; }


void test_case_1(){
	cout<<"Division Hashing\n";
	Hash_Map<int> ob1;
	
	for(int i=15;i<25;i++)
		ob1.insert(i+8, i);
	
	ob1.traverse();
	cout<<"Key Was Placed on "<<ob1.search(25)<<'\n';
	ob1.remove(32);
	cout<<"AFTER REMOVAL:\n";
	ob1.traverse();
}

void test_case_2(){
	cout<<"By Multiplication Hashing:\n";
	Hash_Map<int, 'M'> ob2;
	
	for(int i=15;i<25;i++)
		ob2.insert(i+8, i);
	
	ob2.traverse();
	cout<<"Key was placed on "<<ob2.search(25)<<'\n';
	ob2.remove(32);
	cout<<"AFTER REMOVAL:\n";
	ob2.traverse();

}

void test_case_3(){
	cout<<"By Mid Square Hashing:\n";
	Hash_Map<int, 'S'> ob3;
	
	for(int i=15;i<25;i++)
		ob3.insert(i+8, i);

	ob3.traverse();
	cout<<"Key was placed on "<<ob3.search(25)<<'\n';
	ob3.remove(32);
	cout<<"AFTER REMOVAL : "<<'\n';
	ob3.traverse();
}

void test_case_4(){
	cout<<"By Folding Hashing: "<<'\n';
	Hash_Map<int, 'F'> ob4;
	
	for(int i=15;i<25;i++)
		ob4.insert(i+8, i);
	
	ob4.traverse();
	cout<<"Key was placed on "<<ob4.search(25)<<'\n';
	ob4.remove(32);
	cout<<"AFTER REMOVAL:\n";
	ob4.traverse();

}

void test_case_5(){
	cout<<"By Radix Hashing:\n";
	Hash_Map<int, 'R'> ob5;
	
	for(int i=15;i<25;i++)
		ob5.insert(i+8, i);
	
	ob5.traverse();
	cout<<"Key was placed on "<<ob5.search(25)<<'\n';
	ob5.remove(32);
	cout<<"AFTER REMOVAL:\n";
	ob5.traverse();
}

int main(){
//	test_case_1();
	test_case_2();
//	test_case_3();
//	test_case_4();
//	test_case_5();
	
	return 0;
}

