#include"Indexed_Struct.hpp"
#include"../Contiguous_Structures/String.hpp"

using std::cout;

int main(){
	indexed_struct<int,String,double> obj1{4,"noice",44.444};
	
	indexed_struct<int,String,double,String,char> obj2{909,"zzzz",919.19,"multiple",'j'};
	
	cout<<obj1<<'\n'<<obj2<<"\n\n";
	
	cout<<*(String*)(obj1+1)<<'\n'<<*(double*)(obj2+2)<<"\n\n";//i.e. directly accessing attributes
	
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
