#include<iostream>
using namespace std;
bool recursive_palindrome(int n,int num,int rev){
	if(rev==num)
		return true;
	if(n)
		return recursive_palindrome(n/10,num,rev*10+(n%10));
	return false;
}
bool iterative_palindrome(int num){
	int n=num,rev=0;
	do{
		rev=rev*10+(n%10);
		n/=10;
	}while(n);
	if (num==rev)
		return true;
	return false;
}
int main(){
	#define N 12345
	//if (iterative_palindrome(N))
	if (recursive_palindrome(N,N,0))
		cout<<"\nNote: your number is a palindrome";
	else
		cout<<"\nNote: your number is not a palindrome";
	return 0;
}

