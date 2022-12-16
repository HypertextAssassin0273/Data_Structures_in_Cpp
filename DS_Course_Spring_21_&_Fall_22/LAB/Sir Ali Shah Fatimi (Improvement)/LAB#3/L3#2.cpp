#include <iostream>

using std::cout;

/** Indirect Recursion **/
//note: for problem description & analysis, see previous task#1 (i.e. L3#1.cpp)

void sequence_generator(int, int, const int);//forward_declaration

void __sequence_generator(int n, int i, const int tc){
	if(i==tc) return;
	sequence_generator(n-i, i-1, tc);
	cout<<n<<' ';
}

void sequence_generator(int n, int i, const int tc){
	if(i==tc) return;
	__sequence_generator(n-i, i-1, tc);
	cout<<n<<' ';
}

int main(){
	cout<<"Indirect Recursion:-"
		<<"\npart 'a' sequence: ";
	sequence_generator(28, 7, 0);//here: intial_series_value=28, series_size=7
	
	cout<<"\npart 'b' sequence: ";
	sequence_generator(22, 8-2, -2);//here: intial_series_value=22, series_size=8
	
	return 0;
}
