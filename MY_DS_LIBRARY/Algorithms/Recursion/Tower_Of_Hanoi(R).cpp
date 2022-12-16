#include<iostream>
using namespace std;
void TOH(int n,char src,char temp,char dest){//i.e. temporary/auxilary rod
	if (n>=1){
		TOH(n-1,src,dest,temp);
		cout<<src<<" to "<<dest<<endl;
		TOH(n-1,temp,src,dest);
	}
}
int main(){
	int n=4; // Number of disks
	TOH(n,'A','B','C'); // A, B and C are names of rods
	return 0;
}

