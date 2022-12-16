#ifndef WEIGHTED_GRAPH_GUARD
#define WEIGHTED_GRAPH_GUARD 1

#include <iostream>

class Weighted_Graph{
	int **adj;// adjacency matrix
	int size;

public:
	Weighted_Graph(int size=10)://default 7 parametized ctor
		size(size), adj(new int*[size]){
		for(int i=0;i<size;++i)
			adj[i]=new int[size]{};//initializes with zero
	}
		
	int hash(char x)const;
	char rev_hash(int x)const;
	
	void add_edge(char, char, int);//u is first edge, v is second connected edge, last w is weight
	
	void print_MST(int[])const;
	void print_MST();
	
	int miniDist(int[], bool[]);
	void DijkstraAlgo(char);
		
	friend std::ostream& operator<<(std::ostream& out, const Weighted_Graph& self){//overloaded cin method
		for(size_t i=0, j;i<self.size;++i){
			out<<"[INFO][PRINT] ("<<self.rev_hash(i)<<")\t";
			for(j=0;j<self.size;++j)
				if(self.adj[i][j])
					out<<self.rev_hash(j)<<" ("<<self.adj[i][j]<<")\t";
			out<<'\n';
		}
		return out;
	}
		
};

#endif
