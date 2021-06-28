#include<iostream>
using namespace std;
class Employee{
	string Name;
	unsigned short Age,Experience;
    const unsigned int ID;
    float Working_Hrs,Hourly_Wage,Salary;
    
    static int Employee_Counter(bool val_flag=false,bool direction_flag=true){//i.e. safe static obj_counter
		static int Employee_No=0;
		if (val_flag)
			return Employee_No;
		if(direction_flag)
			return ++Employee_No;
		return --Employee_No;
	}
public:
    Employee():Name("N.I.L"),ID(40400+Employee_Counter()),Age(0),Experience(0),Working_Hrs(0),Salary(0),Hourly_Wage(0){}
    void Set_Data(){
    	cout<<"Enter Name: ";
        cin>>Name;
        cout<<"Enter Age (>22 years): ";
        cin>>Age;
        cout<<"Enter Experience (>1 years): ";
        cin>>Experience;
        cout<<"Enter Working Hours (>120 hours): ";
        cin>>Working_Hrs;
        cout<<endl;
	}
	void Display_Data(bool flag=true)const{
		cout<<"Employee ID: "<<ID<<endl
			<<"Name: "<<Name<<endl;
		if(flag){
			cout<<"Age: "<<Age<<" years"<<endl
				<<"Experience: "<<Experience<<" years"<<endl
				<<"Working Hours: "<<Working_Hrs<<endl
				<<"Hourly Wage: "<<Hourly_Wage<<endl
				<<"Salary: "<<Salary<<endl;
		}
		else
			cout<<"Invalid Parameters provided for Salary!\n\a";
		cout<<endl;
	}
	bool Set_Salary(){
        if(Age>50&&Experience>10&&Working_Hrs>240)
            Hourly_Wage=500;
        else if(Age>40&&Age<=50&&Experience>6&&Experience<=10&&Working_Hrs>200&&Working_Hrs<=240)
            Hourly_Wage=425;
        else if(Age>30&&Age<=40&&Experience>3&&Experience<=6&&Working_Hrs>160&&Working_Hrs<=200)
            Hourly_Wage=375;
        else if(Age>22&&Age<=30&&Experience>1&&Experience<=3&&Working_Hrs>120&&Working_Hrs<=160)
            Hourly_Wage=300;
        else
            return false;
        Salary=Hourly_Wage*Working_Hrs;
        return true;
    }
    static int Get_Employee_Count() { return Employee_Counter(1); }
    ~Employee(){ Employee_Counter(0,0); }
};
int main(){
	unsigned int size,i;
	cout<<"Enter No. of Employees u want: ";
	cin>>size;
    Employee** Emp_Ptr_Array=new Employee*[size],**iterator=Emp_Ptr_Array;
    while(Employee::Get_Employee_Count()<size)
    	*iterator++=new Employee;
	cout<<"\nINPUT DATA:-"<<endl;
	for (iterator=Emp_Ptr_Array,i=0;i<size;++i)
    	(*iterator++)->Set_Data();
    cout<<"DISPLAY DATA:-"<<endl;
    for (iterator=Emp_Ptr_Array,i=0;i<size;++i,++iterator)
    	(*iterator)->Display_Data((*iterator)->Set_Salary());
	cout<<"Total Employee Objs Present (before destruction): "<<Employee::Get_Employee_Count()<<endl;
	for (iterator=Emp_Ptr_Array;Employee::Get_Employee_Count()>0;)
		delete *iterator++;
	delete []Emp_Ptr_Array;
	cout<<"Total Employee Objs Present (after destruction): "<<Employee::Get_Employee_Count();
    return 0;
}
