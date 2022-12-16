#include "F_Stack.hpp"
using namespace std;

bool isOperator(char c){
	return (c=='+'||c=='-'||c=='*'||c=='/'||c=='^');
}

int precedence(char c){
	return c=='^'?3: c=='*'||c=='/'?2: c=='+'||c=='-'?1: -1;
}

template<size_t N>
string InfixToPostfix(const char (&infix)[N]){
	F_Stack<char, N> stack;
	string postfix;
	
	for(int i=0;i<N;i++){
		if((infix[i]>='a'&&infix[i]<='z')||(infix[i]>='A'&&infix[i]<='Z'))
			postfix+=infix[i];
		else if(infix[i] == '(')
			stack.push(infix[i]);
		else if(infix[i] == ')'){
			while(stack.peek()!='(' && !stack.empty()){
				char temp=stack.peek();
				postfix+=temp;
				stack.pop();
			}
			if(stack.peek()=='(')
				stack.pop();
		}
		else if(isOperator(infix[i])){
			if(stack.empty())
				stack.push(infix[i]);
			else{
				if(precedence(infix[i])>precedence(stack.peek()))
					stack.push(infix[i]);	
				else if(precedence(infix[i])==precedence(stack.peek()) && infix[i]=='^')
					stack.push(infix[i]);
				else{
					while(!stack.empty() && precedence(infix[i])<=precedence(stack.peek())){
						postfix+=stack.peek();
						stack.pop();
					}
					stack.push(infix[i]);
				}
			}
		}
	}
	while(!stack.empty()){
		postfix+=stack.peek();
		stack.pop();
	}
	
	return postfix;
}

int main(){
  	cout<<"POSTFIX EXPRESSION: "
	  	<<InfixToPostfix("a+b*(c^d-e)^(f+g*h)-i");
	
	return 0;
}
