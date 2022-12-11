#include<iostream>
using namespace std;

void binconversion(int num){
	if(num == 0)
		return;
	else
		binconversion(num/2);					//non-tail recursion

	if((num%2) == 0){
		cout<< "0";
	}
	else{
		cout<< "1";
	}
}

int main(){
	int dec;
	cout<< "DECIMAL NUMBER: ";
	cin>> dec;
	cout<< "BINARY EQUIVALENT: ";
	binconversion(dec);
	
	cout<< endl<< endl;
	system("PAUSE");
	return 0;
}
