//#include "../Multi_Attribute_AVL_Tree_Adapter.hpp"
#include "../Optimized_Multi_Attribute_AVL_Tree_Adapter.hpp"
#include "D:/FAST DATA/SEM-III/Data Structures/MY_DS_LIBRARY/Utilities/Date.hpp"
#include "D:/FAST DATA/SEM-III/Data Structures/MY_DS_LIBRARY/Contiguous_Structures/String.hpp"

using std::cout;

//typedef MAATA_O<bool,int,String,double,char,String,double> tree_adapter_type;//df_4.csv

typedef MAATA_O<Date,String,int> tree_adapter_type;//sales_target.csv

tree_adapter_type get_obj(){
	return tree_adapter_type("sales_target.csv", true, 50);//using input_file_stream ctor
	//Note: pass 'true' in 2nd parameter if file is .csv
}

void basic_operations(tree_adapter_type& obj){//for df_4.csv right now
//data-types: bool,int,String,double,char,String
//indexes:	   0    1    2      3     4     5
	
//	cout<<"\n-----\nSearch all 'f' after removing all 77.11 :-\n";
//	obj.remove({3}, 77.11);//remove any record by any attribute in O(logN+M*logN) time
//	obj.view_filtered_records(obj.search({4}, 'f'));//search record by any attribute in O(logN) time
	
	cout<<"\nData Sorted by Atrribute: {int: 1}\n";
//	int index=1; obj.sort(index);//run-time
	obj.sort<1>();//compile time
	
//	obj.clear();
}

void traverse_data(tree_adapter_type& obj){
	cout<<"RECORDS:-\nList-View:\n";
	obj.view_records(true);//bool version available for indexer view
	cout<<"\nTrees-View:"<<'\n';//Note: always prefer to use '\n' over std::endl
	obj.view_by_trees();
}

int main(){
	auto obj=get_obj();//by file-stream
	
//	basic_operations(obj);
	
	traverse_data(obj);
	
	return 0;
}
