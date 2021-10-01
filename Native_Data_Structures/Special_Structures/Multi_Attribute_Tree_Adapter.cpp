#include"Multi_Attribute_Tree_Adapter.hpp"
#include"../Contiguous_Structures/String.hpp"
//#include"../Contiguous_Structures/Vector.hpp" //Note: need special comparator for single value

template<typename T>
void print_type(){ std::cout<<__PRETTY_FUNCTION__<<'\n'; }//i.e. for debugging

using std::cout;


typedef multi_attribute_tree_adapter<bool,int,String,double,char,String> tree_adapter_type;

tree_adapter_type construct_obj_method_1(){
	tree_adapter_type MATA;
	
	MATA.insert(true,123,"Great Work!",77.11,'f',"hamza");//i.e. emplace record in O(M*logN) time
	MATA.insert(true,919,"noice",444.444,'c',"ali");
	MATA.insert(true,919,"hello",444.444,'z',"asad");
	MATA.insert(false,191,"hello",919.19,'d',"subhan");
	MATA.insert(false,403,"cOXO",555.555,'F',"haris");
	MATA.insert(false,332,"right",345.1,'e',"taha");
	MATA.insert(false,404,"left",345.1,'q',"shahzaib");
	MATA.insert(true,321,"stranded",0.1,'f',"sufiyan");
	MATA.insert(true,404,"OXO",555.555,'f',"zaidan");
	MATA.insert(false,404,"OXO",111.111,'C',"shariq");
	MATA.insert(false,404,"OXO",111.111,'f',"hamza");
	
	{//i.e. local-scope
		int i=393; String s{"copied"};
		MATA.insert(true,i,s,555.555,'f',String{"shahzaib"});
		//i.e. both local/left/l-values & register/right/r-values can be passed efficiently & simultaneously
	}
	return std::move(MATA);
}

tree_adapter_type construct_obj_method_2(){
	int i=393; String s{"copied"};
	
	return tree_adapter_type{//i.e. using initializer_list ctor
		{true,123,"Great Work!",77.11,'f',"hamza"},
		{true,919,"noice",444.444,'c',"ali"},
		{true,919,"hello",444.444,'z',"asad"},
		{false,191,"hello",919.19,'d',"subhan"},
		{true,404,"OXO",555.555,'f',"zaidan"},
		{false,404,"OXO",111.111,'C',"shariq"},
		{false,404,"OXO",111.111,'f',"hamza"},
		{true,i,s,555.555,'f',"shahzaib"}, //i.e.l-values can also be passed
		{true,111,"z",7,'x',"hamza"},
		{true,111,"z",7,'x',"c"},
		{true,402,"coco",1.5,'f',"zaidan"},
		{true,494,"OXO",23.8,'f',"zaidan"},
		{false,404,"moco",555.555,'f',"umair"},
		{true,401,"OXO",555.555,'f',"altaf"},
		{false,393,"copied",555.555,'f',"shahzaib"},
		{true,303,"coco",56.56,'f',"shahzoo"},
		{false,404,"OXO",555.555,'f',"farhan"},
		{false,191,"left",555.555,'f',"mannan"},
		{true,404,"OXO",555.555,'f',"zaidan"},
		{true,404,"OXO",555.555,'f',"altaf"}
	};
	//NOTE: this approach is very costly as compare to direct/emplaced insert method, since it forms 1 extra copy
}

tree_adapter_type construct_obj_method_3(){
	return tree_adapter_type("df_2.txt");//i.e. using input_file_stream ctor
	//Note: pass 'true' in 2nd parameter if file is .csv
}

void basic_operations(tree_adapter_type& MATA){
	cout<<"\n-----\nSearch all 'f' after removing all 77.11 :-\n";
	MATA.remove(3,77.11);//i.e. remove any record by any attribute in O(logN+M*logN) time
	MATA.search(4,'f');//i.e. search record by any attribute in O(logN) time
//	double x=555.555; int INDEX=3;
//	MATA.search(INDEX,x,'F');//i.e. l-values can be safely passed in any parameter (no compile-time variables needed)
	
	cout<<"\n-----\nSearch all \"OXO\" after removing {\"OXO\",111.111,'C'} :-\n";
	MATA.remove(2,String{"OXO"},111.111,'C');//i.e. remove specific records by providing multiple attributes
	MATA.search(2,String{"OXO"});//i.e. displays all respective matched records of provided key
	
	cout<<"\n-----\nSearch all \"hello\" & all 'true' after removing {\"hello\",444.444} :-\n";
	MATA.remove(2,String{"hello"},444.444);
	MATA.search(2,String{"hello"});
	MATA.search(0,true);
	
	cout<<"\n-----\nSearch by {321,\"stranded\"} after inserting {true,321,\"hello\",345.1,'c',\"n.i.l\"} :-\n";
	MATA.insert(true,321,String{"hello"},345.1,'c',String{"n.i.l"});
	MATA.search(1,321,String{"stranded"});
	
//	MATA.clear();
}

void file_operations(tree_adapter_type& MATA){
	MATA.fread("df_1.txt");// reads data without clearing previous records in system
	MATA.fwrite("df_3.csv",1);//i.e. overwrites df_3.csv file if exists
}

void traverse_data(tree_adapter_type& MATA){
	cout<<"RECORDS:\nList-View:\n";
	MATA.traverse_by_records();
	cout<<"\nTrees-View:"<<'\n';//Note: always prefer to use '\n' over std::endl
	MATA.traverse_by_attributes();
}


int main(){
//	auto MATA=construct_obj_method_1();//i.e. by multiple emplaced_inserts
//	auto MATA=construct_obj_method_2();//i.e. by initializer_list
	auto MATA=construct_obj_method_3();//i.e. by file-stream
	
//	traverse_data(MATA);
	
//	basic_operations(MATA);
	
	file_operations(MATA);
	
	traverse_data(MATA);
	
	cout<<'\n';
	system("pause");
	return 0;
}
