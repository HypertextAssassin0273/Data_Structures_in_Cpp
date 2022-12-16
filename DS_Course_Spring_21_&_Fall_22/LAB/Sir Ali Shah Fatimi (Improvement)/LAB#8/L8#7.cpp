#include "F_Stack.hpp"
using namespace std;

template<size_t N>
bool is_valid_parenthesis(const char (&str)[N]){
	F_Stack<char, N> s;
	for(char c: str){
		if(c=='(') s.push(')');
		else if(c=='{') s.push('}');
		else if(c=='[') s.push(']');
		else if(!s.empty()){
			if(s.peek()==c) s.pop();
			else return false;
        }
    }
    return s.empty();
}

template<size_t N>
void check_expression(const char (&expr)[N]){
	std::cout<<expr
			 <<(is_valid_parenthesis(expr)?" has valid parenthesis.":
										   " doesn't have valid parenthesis.");
}

int main(){
	/* test case 1: */
	check_expression("()[]{}");
	cout<<'\n';
	
	/* test case 2: */
	check_expression("([)]");
    
    return 0;
}
