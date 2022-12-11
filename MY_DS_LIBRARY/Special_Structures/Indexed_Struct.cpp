#include"Indexed_Struct.hpp"
#include"../Contiguous_Structures/String.hpp"

using std::cout;

int main(){
	indexed_struct<int,String,double> obj1{123,"noice",123.123};
	//indexes:		0	 1		2
	indexed_struct<int,String,double,String,char> obj2{909,"zzzz",919.19,"multiple",'j'};
	//indexes:		0	 1		2	   3	 4
	
	int i=404; String s="4-0-4"; double d=404.404;
	obj2.set({3,0,2}, std::move(s),404,404.404);//works for all types of parameters (in any order)
	
	cout<<obj1<<'\n'<<obj2<<"\n\n";
	
//	cout<<*(String*)(obj1+1)<<'\n'<<*(double*)(obj2+2)<<"\n\n";//run-time single attribute access (generic, efficient)
	
	cout<<obj1.get<1>()<<'\n'<<obj1.get<2>()<<"\n\n";//compile-time single attribute access
	
	indexed_struct<short,char,String> map[]{
		{1,'o',"one"},{2,'t',"two"},{3,'t',"three"},{4,'f',"four"},{5,'f',"five"}
	};
	for(const auto& iter:map)
		cout<<iter<<'\n';
	
	return 0;
}
/*Important Notes/Uses:
	- can be used for making an array of different data-type objects
	- very good for temporarily holding heap objects (i.e. strings,graphs,linked-lists etc) in a group. which means that
	  this structure is good for transportation of various sets of objects from one (database) system to another.
	- should only be used for whole object operations, because some operations for accessing specific attributes cannot be
	  efficiently done.
*/
