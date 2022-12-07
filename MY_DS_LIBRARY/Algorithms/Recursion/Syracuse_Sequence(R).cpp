/*Write a recursive method to print a Syracuse sequence that begins with a number n0
and each element ni

of the sequence is ni-1 /2 if ni-1 is even and 3ni-1 + 1 otherwise.

The sequence ends with 1.*/

#include<iostream>
using namespace std;

class Syracuse{
	int elem;						//n0 = elem;
	
	public:
		Syracuse(const int elem):elem(elem){}
				
		void print(int num){
			if(num == 1){
				cout<< num;
				return;
			}
			cout<< num<< " ";
			if(num%2 == 0)
				num/= 2;
			else
				num = (3*num)+1;
			
			print(num);
		}
};

int main(){
	Syracuse S1(65);
	S1.print(65);
	return 0;
}
