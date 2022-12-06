#include<iostream>
using namespace std;
int Fact(int n){
	if(n==0)
		return 1;
	return Fact(n-1)*n;
}
int Ifact(int n){
	int i=1,f=1;
	for(;i<=n;++i)
		f*=i;
	return f;
}

int main(){
	short n=6;
	cout<<"Factorial of "<<n<<" is: "<<Fact(n);
	return 0;
}
