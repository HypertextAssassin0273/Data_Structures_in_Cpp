#include<iostream>
using namespace std;
void Bin(char arr[],int n){
	static int count=0;
	if (n<1)
		cout<<++count<<") "<<arr<<endl;
	else{
		arr[n-1]='0';//i.e. initializes the array with '0'
		Bin(arr,n-1);
		arr[n-1]='1';
		Bin(arr,n-1);
	}
}
int main(){
	# define size 10
	char arr[size];
	Bin(arr,size);
	return 0;
}
