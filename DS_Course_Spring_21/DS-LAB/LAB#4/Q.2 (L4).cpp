#include<iostream>
#include<cmath>
using namespace std;
void print_power_set_iteratively(char set[],int set_size,int limit){
	if(limit>set_size){
		cout<<"Limit is out of range!"<<endl;
		return;
	}
	unsigned int pow_set_size=pow(2,set_size);//i.e. power_set formula: 2^n 
	for(int counter=1;counter<pow_set_size;++counter){//i.e. neglecting null set by starting loop with 1
		string str;
		for(int i=0;i<set_size;++i)
			if(counter&(1<<i))
				str+=set[i];//i.e. checks if ith bit in the counter is set & then concatenates set_arr	
		if(str.size()==limit){//i.e. prints sets with 2 elements only in proper format
			cout<<'{';
			for(int k=0;k<limit;++k)
				cout<<str[k]<<',';
			cout<<"\b}"<<endl;
		}
	}
}
void print_power_set_recursively(const char set[],const int set_size,const int limit,int counter=1,int i=0,string str=""){
	if(limit>set_size){
		cout<<"Limit is out of range!"<<endl;
		return;
	}
	if(counter<pow(2,set_size)){
		if(i<set_size){
			if(counter&(1<<i))
				str+=set[i];
			print_power_set_recursively(set,set_size,limit,counter,i+1,str);
			return;
		}
		if(str.size()==limit){
			cout<<'{';
			for(int k=0;k<limit;++k)
				cout<<str[k]<<',';
			cout<<"\b}"<<endl;
		}
		print_power_set_recursively(set,set_size,limit,counter+1);
	}
}

int main(){
	char arr[]={'1','2','3','4'},arr2[]={'1','2','3'};
	int N=sizeof(arr)/sizeof(arr[0]),N2=sizeof(arr2)/sizeof(arr2[0]);
	cout<<"Possible Sets are:-\n\nIteratively Traversed:\n(set_size:"<<N<<", bound limit: 2)"<<endl;
	print_power_set_iteratively(arr,N,2);
	cout<<"(set_size:"<<N<<", bound limit: 3)"<<endl;
	print_power_set_iteratively(arr,N,3);
	cout<<"\nRecursively Traversed:\n(set_size:"<<N2<<", bound limit: 2)"<<endl;
	print_power_set_recursively(arr2,N2,2);
	cout<<"(set_size:"<<N2<<", bound limit: 3)"<<endl;
	print_power_set_recursively(arr2,N2,3);
	return 0;
}
