#include <iostream>

using std::cout;

//method#1: using (automatic/stack-based) 2d arrays as matrix

template<int N, int M>
void display(bool (*arr)[N]){ //paramater: pointer (that can only point) to array of N size
	cout<<"student course relation matrix:\n";
	for(int i=0,j;i<N;++i){
		for(j=0;j<M;++j)
			cout<<arr[i][j]<<' ';
		cout<<'\n';
	}
}

template<int N, int M>
void check_common_course_mates(bool (*arr)[N], int i, int j){
	cout<<'\n'<<i<<" & "<<j<<" have: ";
	bool flag=false;
	for(int k=0;k<M;++k){
		if (arr[i][k] && arr[i][k] == arr[j][k]){
			cout<<k<<", ";
			flag=true;
		}
	}
	cout<<(flag?"as":"no")<<" common courses\n";
}

int main(){
	constexpr int N=5, //rows
				  M=5; //colomns
	
	bool arr[N][M]{//2D array initialization
				{0,1,0,1,1},
				{1,0,1,0,1},
				{0,1,0,0,0},
				{1,0,0,0,1},
				{1,1,0,1,0}
	};//here: 1 -> true, 0 -> false
	
	display<N, M>(arr);
	
//	check_common_course_mates<N, M>(arr, 1, 2); //case-1: no common courses
//	check_common_course_mates<N, M>(arr, 0, 1); //case-2: one common course only
	check_common_course_mates<N, M>(arr, 0, 4); //case-3: multiple common courses
	
	return 0;
}
/* side-notes:
	1) we can also use 'bool *ptr = arr[0];' & then treat/traverse it as a linear 1d array, 
	   since memory allocation of 'N*M bools' is sequential/contiguous
	 
	2) or we can pass base/starting address of 2D array in 'check_common_course_mates'
	   function as 1D ptr & still treat it as 2D array inside function,
	   since we can identify no. of colomns by 'M' size.
*/
