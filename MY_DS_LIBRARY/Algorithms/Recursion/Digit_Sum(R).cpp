#include<iostream>
using namespace std;

int sumdig(int num, int dig){
	static int sum = 0;
	
	if(num <= 0 ){
		return 0;	
	}
	else{
		dig = num%10;
		num/= 10;
		sum = sum + dig;
		sumdig(num, dig);
	}
	cout<< sum;
	exit(1);
}

int main(){
	int num;
	
	cout<< endl<< "ENTER A NUMBER: ";
	cin>> num;
	
	int sum = sumdig(num, 0);
	cout<< "THE SUM OF THE DIGITS OF THE NUMBER YOU ENTERED IS: "<< sum<< endl;
	
	return 0;
}
