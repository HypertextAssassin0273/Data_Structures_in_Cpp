#ifndef GRAPH_GUARD
#define GRAPH_GUARD 1

#include <list>
#include "Vector.hpp"

class Graph{
	Vector<size_t>* adj;//adjacency matrix
	bool dir;//directed or not
	size_t size;
	
public:
	Graph(bool dir=false, size_t size=10)://default & parameterized ctor
		dir(dir), size(size), adj(new Vector<size_t>[size]){}
	
	void add_edge(size_t u, size_t v){
		adj[u].push_back(v);
		if(!dir) adj[v].push_back(u);
	}
	
	Vector<size_t>* search_node(size_t n){
		if(n<size){
			std::cout<<"[INFO] Node found!"<<'\n';
			return &adj[n];
		}else{
			std::cout<<"[WARNING] Node value not in graph!"<<'\n';
			return nullptr;
		}
	}
		
	void delete_node(size_t n){
		Vector<size_t> *toDelete=search_node(n);//using the search to get the node links
		if(toDelete){
			toDelete->clear();
			for(size_t i=0;i<size;i++){
				if(i==n) continue;
				
				//adding all links except the link to be deleted into a temporary Vector
				Vector<size_t> temp;
				for(size_t j=0;j<adj[i].size();++j)
					if(adj[i][j]!=n)
						temp.push_back(adj[i][j]);
				
				//then assigning that vector to the original vector, so that the selected link for deletion
				//is no longer present in other node links
				adj[i]=temp;
			}
			std::cout<<"[INFO] Node deleted!"<<'\n';	
		}
		else std::cout<<"[WARNING] Node does not exist!"<<'\n';
	}
	
	void BFS(__int64 s){
		bool visited[size]{};//this mark all vertices as not visited
		std::list<int> queue;//Create a queue for BFS
		
		visited[s]=true;//Mark current node as visited & enqueue it
		queue.push_back(s);
		
		std::cout<<"\n[INFO][BFS]: ";
		while(!queue.empty()){
			s=queue.front();//Dequeue a vertex from queue & print it
			std::cout<<s<<" ";
			queue.pop_front();
			
			// Get all adjacent vertices of the dequeued vertex s.
			//If an adjacent hasn't been visited, then mark it visited & enqueue it
			
			for(auto& adjacent:adj[s])
				if(!visited[adjacent]){
					visited[adjacent]=true;
					queue.push_back(adjacent);
				}
		}
	}
	
	void DFS_util(size_t v, bool visited[]){
		visited[v]=true;//current node v is visited
		std::cout<<v<<' ';
		for(auto& adjacent:adj[v])
			if(!visited[adjacent]) 
				DFS_util(adjacent, visited);//recursively process all  adjacent vertices of node
	}
	void DFS(__int64 s){
		std::cout<<"\n[INFO][DFS]: ";
		bool visited[size]{};	
		DFS_util(s, visited);
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Graph& self){//overloaded cin method
		for(size_t i=0;i<self.size;++i)
			out<<i<<": "<<self.adj[i]<<'\n';
		return out;
	}
};

#endif
