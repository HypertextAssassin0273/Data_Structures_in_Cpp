#include "Graph.hpp"
using std::cout;

int main(){
	// Adding Nodes as follows:
	/*
	0 -> 1
	1 -> 2 and 3
	2 -> 4 and 5
	3 -> 6 and 7
	4 -> 8 and 9
	5 -> 10 and 11
	11 -> 1
	*/
	Graph g(true, 12); // directed graph of size 12
	
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(1, 3);
	g.add_edge(2, 4);
	g.add_edge(2, 5);
	g.add_edge(3, 6);
	g.add_edge(3, 7);
	g.add_edge(4, 8);
	g.add_edge(4, 9);
	g.add_edge(5, 10);
	g.add_edge(5, 11);
	g.add_edge(11, 1);
	
	cout<<g<<'\n';
	
	g.BFS(0);
	
	return 0;
}
