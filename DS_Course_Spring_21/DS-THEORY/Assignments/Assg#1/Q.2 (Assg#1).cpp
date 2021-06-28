#include<iostream>
using namespace std;

class sudoku_solver{
	int N,size;
	int** grid;//i.e. actual grid_size=size*size
public:
	sudoku_solver(int N):N(N),size(N*N),grid(new int*[size]){//i.e. ctor
		for(int i=0;i<size;++i)
			grid[i]=new int[size]();//i.e. allocating & initializing as empty 1D_grids (filling with 0s)
	}
	~sudoku_solver(){
		for(int i=0;i<size;++i)//i.e. deallocation of grid
			delete grid[i];
		delete []grid;
	}
private:
	//i.e. checks whether num is present in col or not
	bool is_present_in_col(int col,int num){
   		for (int row=0;row<size;++row)
    	  	if (grid[row][col]==num)
    	     	return true;
   		return false;
	}
	//i.e. checks whether num is present in row or not
	bool is_present_in_row(int row,int num){
	   	for (int col=0;col<size;++col)
    		if (grid[row][col]==num)
    	    	return true;
   		return false;
	}
	//i.e. checks whether num is present in 'N x N' box or not
	bool is_present_in_box(int box_start_row,int box_start_col,int num){
	   	for (int row=0;row<N;++row)
    	  	for (int col=0;col<N;++col)
        	 	if (grid[row+box_start_row][col+box_start_col]==num)
            		return true;
   		return false;
	}
	//i.e. returns true if num is not present in col, row and current 'NxN' box
	bool is_valid_place(int row,int col,int num){
	   	return !is_present_in_row(row,num)&&
   			   !is_present_in_col(col,num)&&
			   !is_present_in_box(row-row%N,col-col%N,num);
	}
	//i.e. returns true if any cell is empty and also updates row and column for 'solve' func
	bool find_empty_place(int& row,int& col){
	   	for (row=0;row<size;++row)
	      	for (col=0;col<size;col++)
    	     	if (!grid[row][col])
    	        	return true;
   		return false;
	}
public:
	//i.e. solves sudoku grid & returns false if no solution exists
	bool solve(){
   		int row,col;
   		if (!find_empty_place(row,col))//i.e. return true if all cells are filled in grid
    		return true;
		
   		for (int num=1;num<=size;++num){//i.e. valid numbers are 1 - size
    	  	if (is_valid_place(row,col,num)){//i.e. check validation, if yes, put the number in the grid
    	     	grid[row][col]=num;
    	    	if (solve())//i.e. recursively go for other cells in the grid
        	    	return true;
        		grid[row][col]=0;//i.e. re-assign cell as empty when conditions aren't satisfied
      		}
   		}
   		return false;
	}
	//i.e. prints sudoku grid (with lines)
	void print_grid(){
   		for (int i=0;i<size;++i){
    	  	for (int j=0;j<size;++j){
      			for (int k=0;k<size;k+=N)
        	 		if(j==N+k)
        	    		cout<<"| ";
         		cout<<grid[i][j]<<" ";
      		}
      		for (int k=0;k<size-N;k+=N)
			  	if(i==N-1+k){
        	 		cout<<endl;
         			for(int j=0;j<size-1;++j)
            			cout<<"---";
            	}
      		cout<<endl;
   		}
	}
};

int main(){
	sudoku_solver sudoku(2);
	if(sudoku.solve())
    	sudoku.print_grid();
    else
    	cout<<"No solution Exist!";
    return 0;
}
