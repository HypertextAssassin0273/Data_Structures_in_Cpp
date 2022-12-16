#include <iostream>
 
/* Nested Recursion */ 
//A recursive function passing parameter as a 
//recursive call or recursion inside the recursion
int fun(int n){ return (n>100)?n-10:fun(fun(n+11)); }

int main(){
	int r=fun(95);
	
	std::cout<<r;
	
    return 0;
}

/* Output Dry Run (rough stack_activation_record) */
//100: main() => int r=fun(95) {waiting for '200' => returns 91}
//200: fun(95) => int n=95, condition faLse: fun(fun(95+11)) {waiting for '400' => returns 91}

//300: fun(95+11) => int n=106, condition true: returns 106-10=96
//400: fun(fun(95+11)) => int n=96, condition faLse: fun(fun(96+11)) {waiting for '600' => returns 91}

//500: fun(96+11) => int n=107, condition true: returns 107-10=97
//600: fun(fun(96+11)) => int n=97, condition faLse: fun(fun(97+11)) {waiting for '800' => returns 91}

//700: fun(97+11) => int n=108, condition true: returns 108-10=98
//800: fun(fun(97+11)) => int n=98, condition faLse: fun(fun(98+11)) {waiting for '1000' => returns 91}

//900: fun(98+11) => int n=109, condition true: returns 109-10=99
//1000: fun(fun(98+11)) => int n=99, condition faLse: fun(fun(99+11)) {waiting for '1200' => returns 91}

//1100: fun(99+11) => int n=110, condition true: returns 110-10=100
//1200: fun(fun(99+11)) => int n=100, condition faLse: fun(fun(100+11)) {waiting for '1400' => returns 91}

//1300: fun(99+11) => int n=110, condition true: returns 110-10=100
//1400: fun(fun(99+11)) => int n=100, condition faLse: fun(fun(100+11)) {waiting for '1600' => returns 91}

//1500: fun(99+11) => int n=111, condition true: returns 111-10=101
//1600: fun(fun(99+11)) => int n=101, condition true: returns 101-10=91

//Note: for more understanding, see 'L#3#4_stack_activation_record.jpg'
