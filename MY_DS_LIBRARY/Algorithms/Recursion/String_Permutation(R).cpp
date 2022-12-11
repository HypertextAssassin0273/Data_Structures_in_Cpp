#include<iostream>
using namespace std;
template<typename T>
void Swap(T* x,T* y){
	T temp=*x;
	*x=*y;
	*y=temp;
}
void Permutation(char* str,int i,int n){
	static int count=0;
	if(i==n)
		cout<<++count<<") "<<str<<endl;
	else
		for(int j=i;j<=n;++j){
			Swap(str+i,str+j);
			Permutation(str,i+1,n);
			Swap(str+i,str+j);
		}
}
int main(){
	char str[]="ABC";
	# define size sizeof(str)/sizeof(str[0])-1
	Permutation(str,0,size-1);
	return 0;
}

