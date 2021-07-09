#include<iostream>
using namespace std;

template<typename T>
class DSA final{//i.e. 'final' prevents further inheritance (C++11 Construct)
	typedef unsigned long long __uint64;
	__uint64 _size;
	T *data;
public:
	DSA(__uint64 n=1):data(new T[n]),_size(n){}
	~DSA(){ delete[] data; };
	DSA(const DSA& v):data(new T[v._size]),_size(v._size){//i.e. copy ctor
 		copy(v.data,v.data+_size,data);//Alternate: memcpy(data,v.data,_size*_sizeof(T));
	}
	DSA& operator=(const DSA& v){//i.e. copy assignment func
 		T* new_data=new T[v._size];
 		copy(v.data,v.data+v._size,new_data);
 		delete[] data;
 		data=new_data;
 		_size=v._size;
	 	return *this;
 	}
 	T& operator[](__uint64 n)const noexcept{//i.e. gives read & write access
		if (n>=_size){//i.e. parameter is of unsigned type, hence condition 'n<0' is excluded
			cout<<"\nError: Given Index is Out of Bound!\n";			
	 		throw false;
		}
		return data[n];
		/*Tip: Use 'noexcept' keyword to call std::terminate func. to handle exception.
		  Reason: Try-catch structure is quite expensive & it will slow-down your program's
				  execution/control-flow if you over-use it. */
	}
	T& operator*()const{ return *data; }
 	__uint64 size()const{ return _size; }
};
class Students{
	unsigned long ID;
	unsigned short Batch,Expected_Graduation_Year;
	string Discipline;
	DSA<string> *Current_Courses;
	/*Note: Pointer to member-pointer of Array class which further points to dynamic array 
				(i.e. makes 2D pointer)
	  Purpose: No. of courses needed to be determined by user */
public:
	Students():ID(0),Batch(0),Expected_Graduation_Year(0){} //i.e. initializing member_variables
	
	Students(const Students& other)://i.e. copy ctor
		ID(other.ID),Batch(other.Batch),
		Expected_Graduation_Year(other.Expected_Graduation_Year),
		Discipline(other.Discipline),
		Current_Courses((other.Current_Courses)?new DSA<string>(*other.Current_Courses):nullptr){}
		/*i.e. assign clone copy if any previous address for Current_Courses of 'other' is present
		Note: In ctor's Initializer-List, only tenary operator is used for decisions */

	Students& operator=(const Students& other){//i.e. copy assignment func
		ID=other.ID,Batch=other.Batch;
		Expected_Graduation_Year=other.Expected_Graduation_Year;
		Discipline=other.Discipline;
		if(Current_Courses)
			delete Current_Courses;
		if(other.Current_Courses)
			Current_Courses=new DSA<string>(*other.Current_Courses);//i.e. assign clone copy
	 	return *this;
 	}
	void Set_Data(){
		cout<<"Enter ID: ";
		cin>>ID;
		cout<<"Enter Batch: ";
		cin>>Batch;
		cout<<"Enter Expected Graduation Year: ";
		cin>>Expected_Graduation_Year;
		cout<<"Enter Discipline: ";
		cin>>Discipline;
		cout<<"Current Courses Count: ";
		unsigned short Current_Courses_Count;
		cin>>Current_Courses_Count;
		cout<<"Enter All Current Courses:"<<endl;
		Current_Courses=new DSA<string>(Current_Courses_Count);
		for(unsigned short i=0;i<Current_Courses_Count;++i)
			cin>>(*Current_Courses)[i];//Alternate: Current_Courses[0][i]
	}
	void Display_Data()const{
		cout<<"ID: "<<ID<<endl
			<<"Batch: "<<Batch<<endl
			<<"Expected Graduation Year: "<<Expected_Graduation_Year<<endl
			<<"Discipline: "<<Discipline<<endl
			<<"Current Courses: "<<endl;
		if(Current_Courses)
			for(unsigned short i=0;i<Current_Courses->size();++i)
				cout<<"\t"<<(*Current_Courses)[i]<<endl;
		else
			cout<<"\tN.I.L"<<endl;
	}
	~Students(){ delete Current_Courses; }
};
int main(){
	unsigned short arr_size;
	cout<<"Enter Size of Student Array (DSA): ";
	cin>>arr_size;
	DSA<Students> Arr(arr_size);
	Students obj;//i.e. defined outside to save compiler from extra overhead of deleting/creating obj
	for(unsigned short i=0;i<Arr.size();++i){
		cout<<"\nEnter Data for Student "<<i+1<<":"<<endl;
		obj.Set_Data();
		Arr[i]=obj; //i.e. triggers copy assignment func for student
	}
	cout<<"\nRESULT:"<<endl;
	for(unsigned short i=0;i<Arr.size();++i){
		cout<<"Student "<<i+1<<" Data:"<<endl;
		Arr[i].Display_Data();
		//cout<<Arr[i+1].Display_Data();//i.e. test-case for exception error
		cout<<endl;
	}
 	return 0;
}
