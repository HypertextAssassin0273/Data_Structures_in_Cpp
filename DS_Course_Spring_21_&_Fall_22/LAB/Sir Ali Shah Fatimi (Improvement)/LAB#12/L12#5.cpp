#include "Weighted_Graph.hpp"
using namespace std;

int Weighted_Graph::hash(char x)const{ return (x=='s'?0 :x>='a'&&x<='e'?x+1-'a':-1); }
char Weighted_Graph::rev_hash(int x)const{ return (x==0?'s':x>=1&&x<=5?x-1+'a':'z'); }

void Weighted_Graph::add_edge(char u, char v, int w){
	int u_int=hash(u), v_int=hash(v);
	if(u_int<size&&v_int<size)
		adj[u_int][v_int]=w;
}

int Weighted_Graph::miniDist(int distance[], bool Tset[]){
	int minimum=INT_MAX, idx;
	for(int k=0;k<6;++k)
		if(Tset[k]==false&&distance[k]<=minimum){
			minimum=distance[k];
			idx=k;
		}
	return idx;
}
		
void Weighted_Graph::DijkstraAlgo(char s) {
	int src=hash(s);
	if(src==-1) return;
	
    int distance[6];//array to calculate the minimum distance for each node                             
    bool Tset[6]{};//boolean array to mark visited & unvisited for each node
    
    for(int k=0;k<6;++k)
        distance[k]=INT_MAX;
    
    distance[src]=0;//Source vertex distance is set 0               
    
    for(int i=0, k;i<6;++i){
        int m=miniDist(distance, Tset); 
        Tset[m]=true;
        for(k=0;k<6;++k){
            // updating the distance of neighbouring vertex
            if(!Tset[k] && adj[m][k] && distance[m]!=INT_MAX && distance[m]+adj[m][k]<distance[k])
                distance[k]=distance[m]+adj[m][k];
        }
    }
    cout<<"\n[INFO][DIJKSTRA'S ALGO]\n"
    	<<"Vertex\t\tDistance from source vertex\n";
    for(int k=0;k<6;k++){
        char str=rev_hash(k);
        cout<<"  "<<str<<"\t\t\t"<<distance[k]<<'\n';
    }
}

int main(){
	Weighted_Graph g(6);//directed graph of size 12
	
	g.add_edge('s', 'a', 1);
	g.add_edge('s', 'b', 5);
	g.add_edge('a', 'b', 2);
	g.add_edge('a', 'c', 2);
	g.add_edge('a', 'd', 1);
	g.add_edge('b', 'd', 2);
	g.add_edge('c', 'd', 3);
	g.add_edge('c', 'e', 1);
	g.add_edge('d', 'e', 2);

	
	cout<<g;
	g.DijkstraAlgo('s');
	
}
