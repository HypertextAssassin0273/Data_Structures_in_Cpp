#include "Graph.hpp"
using std::cout;

void un_directed_graph(Graph& gu){
	cout<<"[INFO] UNDIRECTED GRAPH\n\n"<<gu;// printing graph
	
	Vector<size_t> *searched=gu.search_node(2);//returns the address of searched node
	
	if(searched){
		cout<<"[INFO] Found Node ("<<2<<"): ";
		for(auto& element:*searched)
			cout<<element<<' ';
		cout<<'\n';
	}
	
	gu.delete_node(2);
	cout<<gu;//printing the graph after deleting Node 2
}

void directed_graph(Graph& gd){
	cout<<"\n[INFO] DIRECTED GRAPH\n\n";
	cout<<gd;//printing graph
	
	Vector<size_t> *searched=gd.search_node(2);//returns the address of searched node
	
	if(searched){
		cout<<"[INFO] Found Node (" << 2 << "): ";
		for(auto& element:*searched)
			cout<<element<<' ';
		cout<<'\n';
	}
	
	gd.delete_node(2);
	cout<<gd;//printing the graph after deleting Node 2
}

int main(){
	int S=5;
	Graph gu(S); // UN-directed graph
	Graph gd(true, S); // directed graph
	
	// adding random graph links
	for(int i=0, N1, N2;i<15;i++){
		N1=rand()%S; N2=rand()%S;
		
		//there should not be any loops for now
		if(N1!=N2){
			gu.add_edge(N1, N2);
			gd.add_edge(N1, N2);
		}
	}
	
	un_directed_graph(gu);
//	directed_graph(gd);	
	
	return 0;
}
