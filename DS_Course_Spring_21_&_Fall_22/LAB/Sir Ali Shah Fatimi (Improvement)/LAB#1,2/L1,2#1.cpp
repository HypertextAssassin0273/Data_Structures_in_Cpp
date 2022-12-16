#include <iostream>
#include <time.h>
#include <stdlib.h>

using std::cout;
using std::string;

class Animal{
	int ID, age;
	string name;
	
public:	
	Animal(int ID=0,int age=0,string name="")://default & parameterized ctor
		ID(ID),age(age),name(name){}
	
	/* setters */
	void set_ID(int ID){ this->ID=ID; }
	void set_age(int age){ this->age=age; }
	void set_name(string name){ this->name=name; }
	
	/* getters */
	int get_ID()const{ return ID; }
	int get_age()const{ return age; }
	string get_name()const{ return name; }
	
	/* extras */
	void eat()const{ cout<<name<<"is eating!"; }
	void sleep()const{ cout<<name<<"is sleep!"; }
	void display_attributes()const{ cout<<ID<<", "<<age<<", "<<name<<'\n'; }
	
	
	static void sort_ids(Animal *arr,int size){
		int i,j;  //iterators
		bool swap_flag;
		for(i=0;i<size-1;++i){
			swap_flag=true;
			for(j=0;j<(size-1)-i;++j)
				if(arr[j+1].ID<arr[j].ID){
					std::swap(arr[j+1],arr[j]);
					swap_flag=false;
				}
			//optimization flag
			if(swap_flag) return;
		}
	}
};

int main(){
	srand(time(NULL));
	
	constexpr int N=5; //size of dynamic object array
	Animal *animals=new Animal[N];
	
	for(int i=0;i<N;++i){
		animals[i].set_ID(rand()%10000);
		animals[i].set_age(20+i);
		animals[i].set_name(string("A")+std::to_string(i+1));
	}
	
	cout<<"original:\n";
	for(int i=0;i<N;++i)
		animals[i].display_attributes();
	
	Animal::sort_ids(animals, N);
	
	cout<<"\nafter sorting:\n";
	for(int i=0;i<N;++i)
		animals[i].display_attributes();
	
	delete[] animals; //destroys all objects & deallocates the array block
	
	return 0;
}
