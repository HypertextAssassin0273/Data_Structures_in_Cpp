#include<iostream>
using namespace std;
class Student{
	string Name;
	
	struct Roll_No{
		unsigned short initial,final;
		unsigned char middle;
		
		Roll_No():initial(),middle(),final(){} //i.e. initializing variables
		friend ostream& operator <<(ostream& out,Roll_No const &obj){
			out<<obj.initial<<obj.middle<<"-"<<obj.final;
			return out;
		}
		friend istream& operator >>(istream& in,Roll_No &obj){
			cout<<"\tinitial: ";
			in>>obj.initial;
			cout<<"\tmiddle: ";
			in>>obj.middle;
			cout<<"\tfinal: ";
			in>>obj.final;
			return in;
		}
	}Roll_No;
	
	template<typename T>
	static void Swap(T *xp, T *yp){  
	    T temp=*xp;
	    *xp=*yp;
	    *yp=temp;
	}
public:
	Student():Name("N.I.L"){}
	friend ostream& operator <<(ostream& out,Student const &obj){
		out<<"Name: "<<obj.Name<<endl
		   <<"Roll-No: "<<obj.Roll_No<<endl<<endl;
		return out;
	}
	friend istream& operator >>(istream& in,Student &obj){
		cout<<"Enter Name: ";
		in>>obj.Name;
		cout<<"Enter Roll-No: "<<endl;
		in>>obj.Roll_No;
		cout<<endl;
		return in;
	}
	static void Sort_by_Names(Student* obj_arr,int size,bool direction_flag=false){
		for (int i=0;i<size-1;++i)
	    	for (int j=0;j<size-i-1;++j){
  	    		if(direction_flag){
					if(obj_arr[j].Name>obj_arr[j+1].Name)//i.e. ascending 
        		    	Swap(&obj_arr[j],&obj_arr[j+1]);
				}
        		else{
					if (obj_arr[j].Name<obj_arr[j+1].Name)//i.e. descending (by default) 
    	    		    Swap(&obj_arr[j],&obj_arr[j+1]);
				}
			}
	}
};
int main(){
	#define N 5
	Student *obj_arr=new Student[N];
	cout<<"INPUT DATA:-"<<endl;
	for(int i=0;i<N;++i){
		cout<<"(Student "<<i+1<<")"<<endl;
		cin>>obj_arr[i];
	}
	cout<<"DISPLAY DATA:-"<<endl;
	for(int i=0;i<N;++i)
		cout<<"(Student "<<i+1<<")"
			<<endl<<obj_arr[i];
	Student::Sort_by_Names(obj_arr,N);
	cout<<"DISPLAY DATA IN DESCENDING ORDER:-"<<endl;
	for(int i=0;i<N;++i)
		cout<<"(Student "<<i+1<<")"
			<<endl<<obj_arr[i];
	delete[] obj_arr;
	return 0;
}
