#include<iostream>
using namespace std;

void print_natural_nos(int n){//ascending order
	if(!n) return;
	print_natural_nos(n-1);//non-tail recursion
	cout<<n<<' ';
}
void print_natural_nos(int n, bool){//descending order
	if(!n) return;
	cout<<n<<' ';
	print_natural_nos(n-1, true);//tail recursion
}

int sum_natural_nos(int n){
	if(!n) return 0;
	return n+sum_natural_nos(n-1);
}

int fib(int n){
	if(!n||n==1) return n;
	return fib(n-1)+fib(n-2);
}

int count_digits(size_t n, bool){//iterative method
	int count=0;
	while(n){
		n/=10;
		++count;
	}
	return count;
}
int count_digits(size_t n, int count=0){//recursive method
	if(!n) return count;
	return count_digits(n/10, count+1);
}

int sum_digits(size_t n, bool){//iterative method
	int sum=0;
	while(n){
		sum+=n%10;
		n/=10;
	}
	return sum;
}
int sum_digits(size_t n){//recursive method
	if(!n) return 0;
	return n%10+sum_digits(n/10);
}

int main(){
//	print_natural_nos(50); //task#1a
//	print_natural_nos(50, true); //task#1b
	
//	cout<<"sum: "<<sum_natural_nos(10); //task#2
	
//	cout<<"fibbonacci series: ";
//	for(int i=1;i<=50;++i)
//		cout<<fib(i)<<' '; //task#3
	
//	cout<<"digit count: "<<count_digits(101424); //task#4a
//	cout<<"digit count: "<<count_digits(101424, true); //task#4b
	
//	cout<<"sum of digits: "<<sum_digits(101424); //task#5a
//	cout<<"sum of digits: "<<sum_digits(101424, true); //task#5b
	
	return 0;
}
