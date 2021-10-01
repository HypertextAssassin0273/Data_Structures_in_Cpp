#include"Indexed_Struct.hpp"
#include"../Contiguous_Structures/String.hpp"

using std::cout;

int main(){
	/*Note: 
		indexed_struct<true,...> -> optimized memory version
		indexed_struct<false,...> -> optimized performance version
	*/
	indexed_struct<true,int,String,double> obj1{4,"noice",44.444};
	indexed_struct<false,int,String,double,String,char> obj2{909,"zzzz",919.19,"multiple",'j'};
	cout<<obj1<<'\n'<<obj2<<"\n\n";
	
	indexed_struct<true,short,char,String> map[]{
		{1,'o',"one"},{2,'t',"two"},{3,'t',"three"},{4,'f',"four"},{5,'f',"five"}
	};
	for(const auto& iter:map)
		cout<<iter<<'\n';
	return 0;
}
