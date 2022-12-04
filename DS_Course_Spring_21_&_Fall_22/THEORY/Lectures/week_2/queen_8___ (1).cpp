#include<iostream>
#define N 4 
using namespace std;
class A{
	public:
	void print_board(int board[N][N]){
		for (int i = 0; i < N; i++) { 
			for (int j = 0; j < N; j++) 
            	cout<< board[i][j]<<" "; 
        cout<<endl; 
    	} 
	}
	bool isSafe(int board[N][N], int row, int col) 
	{ 
	cout<<"issafe fun() row "<< row<<" col "<<col<<endl;
    	int i, j; 
  		/* Check this row on left side */
    	for (i = 0; i < col; i++) 
        	if (board[row][i]) 
            	return false; 
  		/* Check upper diagonal on left side */
    	for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
        	if (board[i][j]) 
            	return false; 
    	/* Check lower diagonal on left side */
    	for (i = row, j = col; j >= 0 && i < N; i++, j--) 
        	if (board[i][j]) 
            	return false; 
    	return true; 
	} 
	bool solveNQUtil(int board[N][N], int col){
		cout<<"solveNQUtil def() col "<< col<<endl;
		if (col >= N) return true;//base case
		else{
			for (int i = 0; i < N; i++) { 
        	/* Check if the queen can be placed on 
          		board[i][col] */
        		if (isSafe(board, i, col)) { 
        		cout<<"issafe call() col"<< col<<endl;
            		/* Place this queen in board[i][col] */
            		board[i][col] = 1; 
  
            	/* recur to place rest of the queens */
            	if (solveNQUtil(board, col + 1)) {
            		cout<<"solveNQUtil def() col+1 "<< col+1<<endl;
                	return true; 
                }
				cout<<endl;
				print_board(board);
				cout<<endl;  
            	/* If placing queen in board[i][col] 
               		doesn't lead to a solution, then 
               		remove queen from board[i][col] */
            	board[i][col] = 0; // BACKTRACK 
            	cout<<"After backtrack "<<endl;
            	print_board(board);
				cout<<endl;
        	} 
    	}
	}
  
    /* If the queen cannot be placed in any row in 
        this colum col  then return false */
    return false; 
	}
	
};
int main(){
	int chess_board[N][N]={0};
	A obj;
	obj.print_board(chess_board);
	if (obj.solveNQUtil(chess_board, 0) == false) { 
		cout<<"Solution does not exist"<<endl; 
    } 
    else
    	obj.print_board(chess_board);
}
