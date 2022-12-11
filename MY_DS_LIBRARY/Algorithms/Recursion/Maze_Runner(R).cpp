#include<iostream>
#include<array>
using namespace std;

#define N 5
typedef array<int,N> array_1d;
array<array_1d,N> sol,maze={ //i.e. final solution of the maze path is stored in 'sol'
	array_1d{1, 0, 0, 0, 0},
	array_1d{1, 1, 0, 1, 0},
	array_1d{1, 1, 1, 1, 0},
	array_1d{1, 0, 0, 1, 0},
	array_1d{1, 1, 1, 1, 1}
};

void Print_Path(){
   	for(const auto& i:sol){
    	for(const auto& j:i)
        	cout << j << " ";
    	cout<<endl;
    }
}

bool Is_Valid_Place(int x,int y){//i.e. func. to check place is inside the maze & have value 1
   	if(x>=0&&x<N&&y>=0&&y<N&&maze[x][y]==1)
    	return true;
    return false;
}

bool Solve_Rat_Maze(int x, int y){
   	if(x==N-1&&y==N-1){
   		sol[x][y]=1;
   		return true;
   	}
   	
   	if(Is_Valid_Place(x,y)){
   		sol[x][y]=1;
		if (Solve_Rat_Maze(x+1,y))    	//go downwards
   	     	return true;				
		if (Solve_Rat_Maze(x,y+1))    	//go rightwards
        	return true;
   	    
      	sol[x][y]=0; 		       		//if all are closed,then there is no path
      	return false;
	}
	return false;
}
int main(){
    if(!Solve_Rat_Maze(0,0)){
    	cout<<"There is no path";
    	return 0;
    }
	Print_Path();
	return 1;
}
