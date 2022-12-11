#include<iostream>
using namespace std;

int primefactor(const int number, int div){
	if( (div == 1) ){
		cout<< endl<< "The following number is a prime number"<< endl;
		return 1;
	}
	else{
		if(number%div == 0){
			cout<< endl<< "The following number is not a prime number"<< endl;
			return 0;
		}	
		div-= 1;
		primefactor(number, div);
	}
}

int main(){
	int number;
	cin>> number;
	primefactor(number, number-1);
}


