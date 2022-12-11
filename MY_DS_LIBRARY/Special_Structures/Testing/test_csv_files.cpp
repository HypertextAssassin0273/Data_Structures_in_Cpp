#include "../Optimized_Multi_Attribute_AVL_Tree_Adapter.hpp"
#include "D:/FAST DATA/SEM-III/Data Structures/MY_DS_LIBRARY/Utilities/Date.hpp"
#include "D:/FAST DATA/SEM-III/Data Structures/MY_DS_LIBRARY/Contiguous_Structures/String.hpp"

using std::cout;

//typedef MAATA_O<bool,int,String,double,char,String,double> tree_adapter_type;//df_4.csv

typedef MAATA_O<Date,String,int> tree_adapter_type;//sales_target.csv

//tree_adapter_type get_obj_m1(){
//	int i=393; String s{"copied"};
//	
//	return tree_adapter_type({//using move initializer_list ctor
//		{true,123,"Great Work!",77.11,'f',"hamza"},
//		{true,919,"noice",444.444,'c',"ali"},
//		{true,919,"hello",444.444,'z',"asad"},
//		{false,191,"hello",919.19,'d',"subhan"},
//		{true,404,"OXO",555.555,'f',"zaidan"},
//		{false,404,"OXO",111.111,'C',"shariq"},
//		{true,i,s,555.555,'f',"shahzaib"}, //l-values can also be passed
//		{true,111,"z",7,'x',"hamza"},
//		{true,111,"z",7,'x',"c"},
//		{true,402,"coco",1.5,'f',"zaidan"},
//		{true,494,"OXO",23.8,'f',"zaidan"},
//		{false,404,"moco",555.555,'f',"umair"},
//		{true,401,"OXO",555.555,'f',"altaf"},
//		{true,303,"coco",56.56,'f',"shahzoo"},
//		{false,404,"OXO",555.555,'f',"farhan"},
//		{false,191,"left",555.555,'f',"mannan"},
//		{true,404,"OXO",555.555,'f',"zaidan"},
//		{true,404,"OXO",555.555,'f',"altaf"}
//	});
//}

tree_adapter_type get_obj_m2(){
	return tree_adapter_type("sales_target.csv", true, 50);//using input_file_stream ctor
	//Note: pass 'true' in 2nd parameter if file is .csv
}

void basic_operations(tree_adapter_type& obj){
//data-types: bool,int,String,double,char,String
//indexes:	   0    1    2      3     4     5
	
//	cout<<"\n-----\nSearch all 'f' after removing all 77.11 :-\n";
//	obj.remove({3}, 77.11);//remove any record by any attribute in O(logN+M*logN) time
//	obj.search({4}, 'f');//search record by any attribute in O(logN) time
	
//	cout<<"\n-----\nSearch by l-values {403, 555.555}:-\n";
//	int i=403; double d=555.555;
//	int indexes[]{1, 3}; obj.search(indexes, i,d);
//	obj.search({1, 3}, i,d);//l-values can be safely passed in any parameter (no compile-time variables needed)
//	
//	cout<<"\n-----\nSearch all \"OXO\" after removing {\"OXO\",111.111,'C'} :-\n";
//	obj.remove({2,3,4}, String{"OXO"},111.111,'C');//remove specific records by providing multiple attributes
//	obj.search({2}, String{"OXO"});//displays all respective matched records of provided key
//	
//	cout<<"\n-----\nSearch all \"hello\" & all 'true' after removing {\"hello\",444.444} :-\n";
////	obj.remove({3, 5}, 444.444, String{"stranded"});
////	obj.remove({2, 3}, String{"hello"},444.444);
//	obj.remove({3, 2}, 444.444, String{"hello"});//can be used in any order
//	obj.search({2}, String{"hello"});
//	obj.search({0}, true);
//	
//	cout<<"\n-----\nSearch by {321,\"stranded\"} after inserting {true,321,\"hello\",345.1,'c',\"n.i.l\"} :-\n";
//	obj.insert(true,321,String{"hello"},345.1,'c',String{"n.i.l"});
//	for(auto& it:obj.search(true, {1,2}, 321,String{"stranded"}))//display results (i.e. duplicate records)
//		cout<<it->data.second<<'\n';
	
	cout<<"\nData Sorted by Atrribute: {int: 1}\n";
//	int index=1; obj.sort(index);//run-time
	obj.sort<1>();//compile time
	
//	cout<<"\n-----\nUpdate all {321,\"stranded\"}:-\n";
//	auto dfl=obj.search(true, {1,2}, 321,String{"stranded"});
//	for(auto& it:dfl) cout<<it->data.second<<'\n';
//	obj.update(std::move(dfl), {3,2}, 789.76,String{"yowza!"});
	
//	cout<<"\n-----\nSearch Indexes by {321,\"stranded\"}:-\n";
//	for(auto& it:obj.search({}, {1,2}, 321,String{"stranded"})) cout<<it->data.second<<'\n';
	
//	obj.clear();
}

void traverse_data(tree_adapter_type& obj){
	cout<<"RECORDS:\nList-View:\n";
	obj.traverse_by_records(true);//bool version available for indexer view
	cout<<"\nTrees-View:"<<'\n';//Note: always prefer to use '\n' over std::endl
	obj.traverse_by_attributes();
}

int main(){
//	auto obj=get_obj_m1();//by initializer_list
	auto obj=get_obj_m2();//by file-stream
	
//	basic_operations(obj);
	
	traverse_data(obj);
	
	return 0;
}
