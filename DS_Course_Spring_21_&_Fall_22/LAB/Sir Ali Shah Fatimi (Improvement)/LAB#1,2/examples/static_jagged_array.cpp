#include <iostream>

using std::cout;

void display_jagged_arrays(int** j_arrs,const int& rows,const int* cols){
	for(int i=0,j;i<rows;++i){
		for(j=0;j<cols[i];++j)
			cout<<j_arrs[i][j]<<' ';
		cout<<'\n';
	}
}

int main(){
	int r1[]{1,2,3,4},
		r2[]{5,6},
		r3[]{55,77,99};
	
	int* jagged_arrays[]{r1, r2, r3};
	//jagged arrays: array of pointers pointing static arrays of different sizes
	
	constexpr int rows=sizeof(jagged_arrays)/sizeof(int*)/* 8 bytes => ptr_type */,
				  cols[]{sizeof(r1)/sizeof(int)/* 4 bytes */,
						 sizeof(r2)/sizeof(int),
						 sizeof(r3)/sizeof(int)};
	
	display_jagged_arrays(jagged_arrays, rows, cols);
	
	return 0;
}
