#include "Weighted_Graph.hpp"
using namespace std;

int min_key(int key[], bool mst_set[], size_t size){
	int min=INT_MAX, min_index;//Initialize min value
	for(int i=0;i<size;++i)
	    if(mst_set[i]==false&&key[i]<min)
		   	min=key[i], min_index=i;
	return min_index;
}

int Weighted_Graph::hash(char x)const{ return (x>='a'&&x<='g'?x-'a':-1); }
char Weighted_Graph::rev_hash(int x)const{ return (x>=0&&x<=6?x+'a':'z'); }

void Weighted_Graph::add_edge(char u, char v, int w){
	int u_int=hash(u), v_int=hash(v);
	if(u_int<size&&v_int<size){
		adj[u_int][v_int]=w;
		adj[v_int][u_int]=w;
	}
}

void Weighted_Graph::print_MST(int parent[])const{
	std::cout<<"\n[INFO][PRIM'S MINIMUM SPANNING TREE]\n"
	    	 <<"EDGE \tWEIGHT\n";
	for(int i=1;i<size;i++)
	    std::cout<<rev_hash(parent[i])<<" - "<<rev_hash(i)<<" \t"
	        	 <<adj[i][parent[i]]<<" \n";
}
		
//constructs & print MST for a graph represented using adjacency matrix representation
void Weighted_Graph::print_MST(){
    int parent[size],//Array to store constructed MST
    	key[size];//Key values used to pick minimum weight edge in cut
    
    bool mstSet[size]{};//To represent set of vertices included in MST
	
    for(int i=0;i<size;++i)//Initialize all keys as INFINITE
        key[i]=INT_MAX;
 
    // Always include first 1st vertex in MST.
    // Make key 0 so that this vertex is picked as first vertex.
	key[0]=0;
	parent[0]=-1;//First node is always root of MST
	 
	//The MST will have V vertices
	for(int count=0;count<size-1;++count){
	    // Pick the minimum key vertex from the set of vertices not yet included in MST
		int u=min_key(key, mstSet, size);
		
		mstSet[u]=true;//Add the picked vertex to the MST Set
			
		// Update key value and parent index of the adjacent vertices of the picked vertex.
		// Consider only those vertices which are not yet included in MST
		for(int i=0;i<size;i++)
		    if(adj[u][i] && mstSet[i]==false && adj[u][i]<key[i])
		        parent[i]=u, key[i]=adj[u][i];
		// adj[u][v] is non zero only for adjacent vertices of m mstSet[v] is false for vertices
		// not yet included in MST Update the key only if adj[u][v] is smaller than key[v]
	}
	print_MST(parent);//print the constructed MST
}

int main(){
	Weighted_Graph g(7); // undirected graph of size 12
	
	g.add_edge('a', 'b', 1);
	g.add_edge('a', 'c', 5);
	g.add_edge('b', 'c', 4);
	g.add_edge('b', 'd', 8);
	g.add_edge('b', 'e', 7);
	g.add_edge('c', 'd', 6);
	g.add_edge('c', 'f', 2);
	g.add_edge('d', 'e', 11);
	g.add_edge('d', 'f', 9);
	g.add_edge('e', 'f', 3);
	g.add_edge('e', 'g', 10);
	g.add_edge('f', 'g', 12);

	
	cout<<g;
	g.print_MST();
	
	return 0;
	
}
