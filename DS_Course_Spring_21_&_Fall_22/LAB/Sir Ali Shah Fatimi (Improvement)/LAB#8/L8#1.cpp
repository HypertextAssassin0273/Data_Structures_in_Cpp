#include "F_Stack.hpp"
using std::cout;

int main(){
	const int N=10;//Stack Limit
	F_Stack<int, N> s;
	
	for(int i=1;i<=N;++i){//step 1
		if(s.full()){//step 2
			cout<<"Stack overflow!";
			break;
		}
		s.push(i);
	}
	
	s.clear();//step 3: similar to 'N' pops
	if(s.empty())
		cout<<"Stack is empty!";
	
	return 0;
}
