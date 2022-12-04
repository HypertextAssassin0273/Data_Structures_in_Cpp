#include<iostream>
using namespace std;
void fun(int n){
	if(n>0){
		cout<<n<<" ";
		fun(n-1);
		cout<<endl;//i.e. for testing
		fun(n-1);
	}
}
int main(){
	fun(4);
	return 0;
}
/* Time Complexity: O(2^n)
   Space Complexity: O(n)
*/
