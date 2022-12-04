#include <iostream>

using std::cout;

/** Direct Recursion **/

/* part 'a': */
//given series_1: 1, 3, 6, 10, 15, 21, 28,... (size = 7)
//=> 0+1=1, 1+2=3, 3+3=6, 6+4=10, 10+5=15, 15+6=21, 21+7=28

/* part 'b': */
//given series_2: 1, 1, 2, 4, 7, 11, 16, 22,... (size = 8)
//=> 0+1=1, 1+1=2, 2+2=4, 4+3=7, 7+4=11, 11+5=16, 16+6=22

/* problem analysis & algorithm: */
//M#1=> add n+i upto i==size, where n=accumulator {starts with min. value} & i=forward_iterator
//M#2=> subtract n-i upto i==lower_limit, where n=accumulator {starts with max. value} & i=backward_iterator

void sequence_generator(int n,   //current_value
						int i,   //iterator
						const int tc){//terminating_condition
	if(i==tc) return;
	sequence_generator(n-i, i-1, tc);
	cout<<n<<' ';
}

int main(){
	cout<<"Direct Recursion:-"
		<<"\npart 'a' sequence: ";
	sequence_generator(28, 7, 0);//here: intial_series_value=28, series_size=7
	
	cout<<"\npart 'b' sequence: ";
	sequence_generator(22, 8-2, -2);//here: intial_series_value=22, series_size=8
	
	return 0;
}
