#include<iostream>
using namespace std;
int GCD(int a,int b){
	if (a==b||!b)//i.e. b=0
		return a;
	if (!a)
		return b;
	if (a>b)
		return GCD(a%b,b);//Alternate: use 'a-b' instead of 'a%b'
	return GCD(a,b%a);//'b-a' -> 'b%a'
}
int main(){
	cout<<"GCD: "<<GCD(105,91);
	return 0;
}

