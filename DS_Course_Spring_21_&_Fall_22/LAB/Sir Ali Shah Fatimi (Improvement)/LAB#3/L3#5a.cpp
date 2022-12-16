#if __cplusplus < 201103L
#include "warning.hpp"
#else
#include <iostream>
#include <vector>

using namespace std;

//renaming as short forms
typedef pair<int, int> int_pair;//specific form

template<typename T>
using vec_2d=vector<vector<T>>;//general form [C++11 construct]

//check if cell (x, y) is valid or not
bool isValidCell(int x, int y, int N){
	return !(x<0||y<0||x>=N||y>=N);
}

void countPaths(vec_2d<int> const &maze, int x, int y, int_pair &dest,
				vec_2d<bool> &visited, int& count, const int N){
	//if destination is found, increment the path count
	if (x==dest.first&&y==dest.second){
		++count;
		return;
	}
	//mark the current cell as visited
	visited[x][y]=true;
	//if the current cell is a valid and open cell
	if (isValidCell(x, y, N)&&maze[x][y]){
		if (x+1<N && !visited[x+1][y])//go down: (x, y) —> (x+1, y)
			countPaths(maze, x+1, y, dest, visited, count, N);
		if (x-1>=0 && !visited[x-1][y])//go up: (x, y) —> (x-1, y)
			countPaths(maze, x-1, y, dest, visited, count, N);
		if (y+1<N && !visited[x][y+1])//go right: (x, y) —> (x, y+1)
			countPaths(maze, x, y+1, dest, visited, count, N);
		if(y-1>=0 && !visited[x][y-1])//go left: (x, y) —> (x, y-1)
			countPaths(maze, x, y-1, dest, visited, count, N);
	}
	//backtrack from the current cell and remove it from the current path
	visited[x][y]=false;
}
 
//Wrapper over countPaths()
int find_count(vec_2d<int> const &maze, int_pair &src, int_pair &dest, const int N){
	//base case
	if (!(N&&maze[src.first][src.second]&&maze[dest.first][dest.second]))
		return 0;
	//stores number of unique paths from source to destination
	int count=0;
	//2D matrix to keep track of cells involved in the current path
	vec_2d<bool> visited(N, vector<bool>(N));//fill ctor: constructs sub-vectors as r-values
	//start from source cell
	countPaths(maze, src.first, src.second, dest, visited, count, N);
	
	return count;
}

int main(){
	//input matrix
    vec_2d<int> maze{//initializer-list ctor
/* test_case_1: */
		{1, 0, 0, 0},
		{1, 1, 0, 1},
		{0, 1, 0, 0},
		{1, 1, 1, 1}
/* test_case_2: */
//		{1, 1, 1, 1},
//		{1, 1, 0, 1},
//		{0, 1, 0, 1},
//		{1, 1, 1, 1}
	};
	
	//N*N matrix
	const int N=maze.size();
	
	//std::pairs for pointing starting & ending cells' coordinates (x, y)
	int_pair src=make_pair(0, 0), 	  //source cell
			 dest=make_pair(N-1, N-1);//destination cell
	
	cout<<"The total number of unique paths are: "<<find_count(maze, src, dest, N);
	
	return 0;
}
#endif
