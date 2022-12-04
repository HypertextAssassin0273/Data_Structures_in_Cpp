#include"Vector.hpp"
#include"String.hpp"
#include"DLL.hpp"

class Enrolled_Course{
	String course;
	int section,credits;
public:
#if __cplusplus >= 201103L
	Enrolled_Course(String&& course={},int section=0,int credits=0):
		course(move(course)),section(section),credits(credits){}
	
	Enrolled_Course(const Enrolled_Course& other)noexcept://i.e. copy ctor
  		course(other.course),section(other.section),credits(other.credits){}
	Enrolled_Course(Enrolled_Course&& other)noexcept://i.e. move ctor
  		course(move(other.course)),section(other.section),credits(other.credits){}
  	
  	Enrolled_Course& operator=(const Enrolled_Course& other)noexcept{//i.e. copy assignment func
  		course=other.course; section=other.section; credits=other.credits;
		return *this;
	}
	Enrolled_Course& operator=(Enrolled_Course&& other)noexcept{//i.e. move assignment func
  		course=move(other.course); section=other.section; credits=other.credits;
		return *this;
	}
#else
	Enrolled_Course(const String& course=String(),int section=0,int credits=0):
		course(course),section(section),credits(credits){}
#endif
	
	friend ostream& operator<<(ostream& out,const Enrolled_Course& self){
		out<<"\tCourse: "<<self.course<<", Section: "<<self.section<<", Credits: "<<self.credits<<endl;
		return out;
	}
	friend istream& operator>>(istream& in,Enrolled_Course& self){
		in.sync();
		in>>self.course>>self.section>>self.credits;
		return in;
	}
};
typedef Enrolled_Course EC;

struct Student{
	int ID;
	DLL<EC> Enrolled_Courses;
	
#if __cplusplus >= 201103L
	Student(int&& ID=0,DLL<EC>&& Enrolled_Courses=DLL<EC>())://i.e. default ctor
		ID(ID),Enrolled_Courses(move(Enrolled_Courses)){}
	
	Student(const Student&other)noexcept://i.e. copy ctor
  		ID(other.ID),Enrolled_Courses(other.Enrolled_Courses){}
	Student(Student&& other)noexcept://i.e. move ctor
  		ID(other.ID),Enrolled_Courses(move(other.Enrolled_Courses)){}
#else
	Student(const int& ID=0,const DLL<EC>& Enrolled_Courses=DLL<EC>()):
		ID(ID),Enrolled_Courses(Enrolled_Courses){}
#endif
	
	friend ostream& operator<<(ostream& out,const Student& self){
		out<<"ID: "<<self.ID<<"\nEnrolled Courses:\n";
		if(self.Enrolled_Courses.empty())
			out<<"\tN.I.L\n";
		else
			out<<self.Enrolled_Courses;
		return out;
	}
};

#if __cplusplus >= 201103L
void test_case(){//i.e. hard coded test-case
	Vector<Student> student_list;
	
	student_list.reserve(3);
	
	//i.e. direct obj initialization of Student through emplace_back (C++11)
	student_list.emplace_back(1111,DLL<EC>{EC("CIS120",1,3),EC("HIS001",2,4)});
	student_list.emplace_back(1234);
	student_list.emplace_back(1357,DLL<EC>(1,EC("CIS120",2,3)));
	
	for(int i=0;i<student_list.size();++i)
		cout<<"student "<<i+1<<":-\n"<<student_list[i]<<endl;	
}
#endif

void main_case(){
	Vector<Student> student_list;
	
	short choice;
	while (true){
		cout<<"\nSELECT YOUR CHOICE:-\n"
			<<"\n1. Add Student"
			<<"\n2. Update Student Info"
			<<"\n3. View Student Records"
			<<"\n4. Exit\n\n";
		cin>>choice;
		fflush(stdin);
		cin.clear();
		system("cls");
		switch (choice){
		case 1:{
			Student obj;
			cout<<"Enter ID: ";
			cin>>obj.ID;
		//Note: Enrolled_Courses can be later updated through case '2'
		#if __cplusplus >= 201103L
			student_list.push_back(move(obj));
		#else
			student_list.push_back(obj);
		#endif
			break;
		}
		case 2:{
			int index;
			cout<<"Enter Student Index: ";
			cin>>index;
			if(index<student_list.size()){
				cout<<"\nSELECT YOUR CHOICE:-\n"
					<<"\n1. Update ID"
					<<"\n2. Add Course"
					<<"\n3. Drop Course\n";
				cin>>choice;
				switch (choice){
					case 1:{
						cout<<"Enter new ID: ";
						cin>>student_list[index].ID;
						break;
					}
					case 2:{
						cout<<"Enter new Enrolled Course Details:\n";
						EC obj;
						cin>>obj;
					#if __cplusplus >= 201103L
						student_list[index].Enrolled_Courses.push_back(move(obj));
					#else
						student_list[index].Enrolled_Courses.push_back(obj);
					#endif
						break;
					}
					case 3:{
						cout<<"Enter Enrolled Course Index: ";
						cin>>choice;
						if(choice<student_list[index].Enrolled_Courses.size()){
							student_list[index].Enrolled_Courses.erase(choice);
							cout<<"Course Dropped!"<<endl;
						}
						break;
					}
				}
			}
			break;
		}
		case 3:
			if(student_list.size())
				for(int i=0;i<student_list.size();++i)
					cout<<"student "<<i+1<<":-\n"<<student_list[i]<<endl;
			else
				cout<<"No Records Found!"<<endl;
			break;
		case 4:
			return;
		}
	}
}

int main(){
//	test_case();
	main_case();
	return 0;
}
