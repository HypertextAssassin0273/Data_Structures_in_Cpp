#include<iostream>
using namespace std;

//-404 = element not found
#define STACKSIZE 10	//to give the size of our stack

class Stack{
	int top;
	int elem_stack[STACKSIZE];
	
	public:
		Stack(){
			top = -1;	//when the stack is empty
		}
		
		bool isstack_empty(){
			return (top == -1);	
		}
		
		bool isstack_full(){
			return (top == (STACKSIZE-1) );
		}
		
		bool push_stack(const int elem){
			if(!isstack_full()){
				top++;
				elem_stack[top] = elem;
				return true;
			}
			return false;
		}
		
		int pop_stack(){
			if(!isstack_empty()){
				int elem = elem_stack[top];
				top--;
				return elem;
			}
			return -404;
		}
		
		void disp(){
			cout<< endl;
			if(!isstack_empty()){
				while(1){
					int elem = pop_stack();
					if(elem != -404)					
						cout<< elem<< " ";	
					else
						break;
				}
			}
		}
};

//scope of main:
int main(){
	Stack Stack_arr;
	int elem;
	
	while(1){
		cout<< endl<< "ELEMENT: ";
		cin>> elem;
		if(elem == 0)
			break;
		bool chk = Stack_arr.push_stack(elem);
		if(chk == false)
			cout<< endl<< "Stack Overflow!"<< endl;
		fflush(stdin);
	}
	
	while(1){
		cout<< endl<< "Y/N (1/0): ";
		cin>> elem;
		if(elem == 0)
			break;
		int popped = Stack_arr.pop_stack();
		if(popped == -404)
			cout<< endl<< "Stack Underflow!"<< endl;
		else
			cout<< endl<< popped<< " has been popped!"<< endl;
		fflush(stdin);
	}
	
	Stack_arr.disp();
	
	system("PAUSE");
	return 0;
}
