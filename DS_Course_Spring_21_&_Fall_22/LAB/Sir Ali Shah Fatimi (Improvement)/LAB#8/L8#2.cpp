#include "D_Stack.hpp"
using std::cout;

int main(){
	D_Stack<int> s({1,2,3,4,5,6,7,8,9,10});//step 1: similar to push 10 times
	
	s.pop();//step 3
	
	//step 2:
	cout<<s<<'\n';//stack values in orginal/descending order
	s.reverse_traverse();//stack values in reverse/ascending order
	
	return 0;
}
