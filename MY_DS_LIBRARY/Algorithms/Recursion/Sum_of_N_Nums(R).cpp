#include<iostream>
using namespace std;
int sum(int n){
	if(n==0)
		return 0;
	return sum(n-1)+n;
}
int Isum(int n){
	for(int s=0,i=1;i<=n;i++)
		s+=i;
	return s;
}
int main(){
	cout<<sum(5);
	return 0;
}
