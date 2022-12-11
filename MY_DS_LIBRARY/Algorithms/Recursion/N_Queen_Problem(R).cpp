#include<iostream>
using namespace std;

class ChessBoard{
	//Note: Normal diagonal is growing towards the left side & reverse diagonal towards right side
	bool *col, *norm_diag, *rev_diag;			
	int *pos_row, squares;

	void disp_sol()const{
		for(int cnt = 0; cnt<squares; cnt++){
			for(int cnt2 = 0; cnt2<squares; cnt2++){
				if(cnt2 == pos_row[cnt])
					cout<< "& ";
				else
					cout<< "* ";
			}
			cout<< endl;
		}
		cout<< endl<< endl;
	}
	void init_board(){
		for(int cnt = 0; cnt<squares; cnt++){
			pos_row[cnt] = -1;
			col[cnt] = true;
		}
		for(int cnt = 0; cnt< (2*squares)-1; cnt++){
			norm_diag[cnt] = true;
			rev_diag[cnt] = true;
		}
	}
	void put_Queen(const int row){//recursive method
		for(int coln = 0; coln< squares; coln++){
			if(col[coln]&&norm_diag[row+coln]&&rev_diag[row-coln+(squares-1)]){
				pos_row[row] = coln;
				col[coln] = false;
				norm_diag[row+coln] = false;
				rev_diag[row-coln+(squares-1)] = false;
				if(row<squares-1)
					put_Queen(row+1);
				else
					disp_sol();		
					
				//will be executed after returning of the last call (backtracking):
				norm_diag[row+coln] = true;
				rev_diag[row-coln+(squares-1)] = true;
				col[coln] = true;
				//next iteration after these statements to find another position
				}
			}
		}
public:
		ChessBoard(int squares):
			squares(squares),pos_row(new int[squares]),col(new bool[squares]),
			norm_diag(new bool[(squares*2)-1]),rev_diag(new bool[(squares*2)-1]){ init_board(); }
		
		void findsolutions(){
			put_Queen(0);//0 for zeroth row and then the value of row would be incremented
		}
		~ChessBoard(){
			delete []pos_row,col,norm_diag,rev_diag;
		}
};

//scope of main:
int main(){
	int size;
	cout<< "ENTER SIZE OF THE BOARD: ";
	cin>> size;
	
	ChessBoard C1(size);	
	C1.findsolutions();
	
	system("PAUSE");
	return 0;
}

