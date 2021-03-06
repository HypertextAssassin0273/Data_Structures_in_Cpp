#include"Vector.hpp"
#include"String.hpp"
#include"Sorts.hpp"

typedef unsigned long long __uint64;
typedef unsigned int __uint32;
typedef unsigned short __uint16;

#if __cplusplus < 201103L
typedef String _string;
typedef Vector<String> string_V1;
typedef Vector<int> int_V1;
typedef Vector<int_V1> int_V2;

#define override
#else
#include"instance_counter.hpp"
/*i.e. defining specialized templates to get their typename at run-time*/
REGISTER_PARSE_TYPE(String);
typedef counted<String> _string;
REGISTER_PARSE_TYPE(Vector<String>);//Alternate: Vector<_string>
typedef counted<Vector<String>> string_V1;
REGISTER_PARSE_TYPE(Vector<int>);
typedef counted<Vector<int>> int_V1;
REGISTER_PARSE_TYPE(Vector<int_V1>);
typedef counted<Vector<int_V1>> int_V2;
REGISTER_PARSE_TYPE(Vector<Vector<Vector<int>>>);
//Note: Here, macro replaces the specialized template struct alongwith its static member initialization

using std::move;
#endif
using std::cout;
using std::cin;
using std::istream;
using std::ostream;

template<typename T>
void print_type(){ std::cout<<__PRETTY_FUNCTION__<<'\n'; }//i.e. for debugging

test_case_1(){
	int_V1 vec,	   	   		//i.e. just declaration, no allocation
	       vec1(10),	   	//i.e. allocate size with 1st arg & initialize the whole vector with 0/""/''
	   	   vec2(5,123);   	//i.e. allocate size with 1st arg & initialize the whole vector with 2nd arg
//	int_V1 vec4{99,88,77};	//i.e. allocate with brace enclosed initializer_list ctor(C++11)

	cout<<"\nvec:"<<'\n'
		<<"size: "<<vec.size()<<'\n'
		<<"capacity: "<<vec.capacity()<<'\n';
	vec.push_back(2);
	vec.push_back(4);
	cout<<"(after 2 push_back)"<<'\n'
		<<"size: "<<vec.size()<<'\n'
		<<"capacity: "<<vec.capacity()<<'\n'
		<<"elements: ";
	for(int i=0;i<vec.size();++i)
		cout<<vec[i]<<' ';
	
	cout<<"\n\nvec1:\nelements: "<<vec1
		<<"\nsize: "<<vec1.size()<<'\n'
		<<"capacity: "<<vec1.capacity()<<'\n';
	vec1.push_back(4);
	cout<<"(after push_back)"<<'\n'
		<<"size: "<<vec1.size()<<'\n'
		<<"capacity: "<<vec1.capacity()<<'\n';
	
	cout<<"\nvec2:\nelements: "<<vec2
		<<"\nsize: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';
	vec2.pop_back();
	cout<<"(after pop_back)"<<'\n'
		<<"size: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';
	vec2.reserve(10);
	cout<<"(after reserve)"<<'\n'
		<<"size: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';
	vec2.shrink_to_fit();
	cout<<"(after shrink_to_fit)"<<'\n'
		<<"size: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n'
		<<"elements: "<<vec2<<'\n';
}

test_case_2(){
	{//i.e. destroying vector v
		int_V1 v;
		cout<<"\nInt data_type (vector v):\nvector v is: ";
    	for(int i=5;i<13;++i)
		    v.push_back(i);
    	cout<<"After push_back: ";
    	for(int i=0;i<v.size();++i)
			cout<<v[i]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\nv[2]: "<<v[2]<<'\n';
 		v.pop_back();
   		cout<<"After pop back: ";
		for(int i=0;i<v.size();++i)
			cout<<v[i]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<'\n';
    	v.clear();
    	cout<<"After clear: "
    		<< "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<'\n'
    		<<"After 3 push_back: ";
		for(int i=1;i<=3;++i)
		    v.push_back(i),cout<<v[i-1]<<", ";
    	cout << "(size: "<<v.size()<<", capacity: "<<v.capacity()<<')'<<'\n';
  	}
    _string c;
    for(char i='a';i<'i';++i)
	    c.push_back(i);
	cout<<"\nChar data_type (vector c):\nAfter push_back: ";
    for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
    cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<")\nc[2]: "<<c[2]<<'\n';
    c.pop_back();
    cout<<"After pop back: ";
    for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<'\n'
		<<"After reserve: ";
	c.reserve(15);
	for(int i=0;i<c.size();++i)
		cout<<c[i]<<", ";
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<'\n'
		<<"After resize: ";
		c.resize(10,'z');
		for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
		cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<')'<<'\n';
	
	cout<<"\nString data_type\nElement in vector a: ";
#if __cplusplus >= 201103L
	string_V1 a={"asad","ali","usman"}; //C++11
#else
	string_V1 a;
	a.push_back("asad"),a.push_back("ali"),a.push_back("usman");
#endif
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<')'<<'\n'
		<<"After resize: ";
	a.resize(8);
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<')'<<'\n';
}

void test_case_3(){
	cout<<"\n\nDeclaring Nested Array without Initializer-List & Index-based Accessing:-"<<'\n';
	Vector<int_V2> vec_3d;//i.e. 3D(l x m x n); l=3,m=10,n=10
	vec_3d.reserve(3);
	{//i.e. destroys 2d arr
		int_V2 vec_2d;
		vec_2d.reserve(10);
		{//i.e. destroys 1d arr
			int_V1 vec_1d;
			vec_1d.reserve(10);
			for (short i=0;i<vec_1d.capacity();++i)
 				vec_1d.push_back(i+10);//i.e. assigning values (1-10)
			for(short i=0;i<vec_2d.capacity();++i)
				vec_2d.push_back(vec_1d);//i.e. assigning 1d vec address to 2d vec
		}
		for(short i=0;i<vec_3d.capacity();++i)
			vec_3d.push_back(vec_2d);//i.e. assigning 2d vec address to 3d vec
	}
	Vector<int_V2> vec_x,vec_y=vec_x=vec_3d;
	/*Note: copy assignment (3d to x), copy ctor (x to y)
	  For Testing: Replace 'vec_x' with others in below loop */
	for(short i=0;i<vec_x.size();++i){
		cout<<"\n2D Vector "<<i+1<<":"<<'\n';
		for(short j=0;j<vec_x[0].size();++j){
			for(short k=0;k<vec_x[0][0].size();++k)
				cout<<vec_x[i][j][k]+(i*10)<<" ";
			cout<<'\n';
		}
	}
	cout<<"\nTotal Size Occupied: "<<vec_3d.size()*vec_3d[0].size()*vec_3d[0][0].size();
}

/*i.e. Abstract/Interface Class (for test-case 4) */
class Items{
	__uint64 ID;
	__uint16 Quantity;//i.e. 0-65535
	float Price;
	_string Name,Brand,Category;
public:
	Items():ID(ID_Generator()),Price(0),Quantity(1){}//i.e. default ctor
	
	Items(const _string& Category):ID(ID_Generator()),Price(0),Quantity(1),Category(Category){}//i.e. copies resources
#if __cplusplus >= 201103L
	Items(_string&& Category):ID(ID_Generator()),Price(0),Quantity(1),Category(move(Category)){}//i.e. moves resources
#endif
	Items(float Price,const _string& Name,const _string& Brand,const _string& Category):
		ID(ID_Generator()),Price(Price),Name(Name),Brand(Brand),Quantity(1),Category(Category){}
#if __cplusplus >= 201103L
	Items(float Price,_string&& Name,_string&& Brand,_string&& Category):
		ID(ID_Generator()),Price(Price),Name(move(Name)),Brand(move(Brand)),Quantity(1),Category(move(Category)){}
#endif
	static __uint64 ID_Generator(const bool Reset_Flag=false){//i.e. can produce upto 20 digit no.
		static __uint64 _ID=40400;
		if(Reset_Flag){
			_ID=40400;
			return _ID;
		}
		return ++_ID;
	}
	virtual void Input_Data(istream&)=0;//i.e. pure virtual func, acts like hooker for below friend '>>' operator func
	friend istream& operator>>(istream& in,Items &obj){
		cout<<"	Enter Product Name: ";
		in.sync();//i.e. neglects remaining buffer
		in>>obj.Name;
		cout<<"	Enter Brand Name: ";
		in.sync();
		in>>obj.Brand;
		in.sync();
		cout<<"	Enter Price: ";
		in>>obj.Price;
		cout<<"	Enter Quantity: ";
		in>>obj.Quantity;
		obj.Input_Data(in);
		return in;
	}
	virtual void Display_Data(ostream&)const=0;
	friend ostream& operator<<(ostream& out,const Items &obj){
		out<<") Category: "<<obj.Category<<", Name: "<<obj.Name<<", Brand: "<<obj.Brand
		   <<", ID: "<<obj.ID<<", Price: "<<obj.Price<<", Quantity: "<<obj.Quantity;
		obj.Display_Data(out);
		return out;
	}
	virtual ~Items(){}//i.e. virtual dtor -> to destruct in correct order
};

test_case_4(){
	/* Local Derived Classes for Abstract objs */
	class Beverages:public Items{
		_string Unit; __uint32 Unit_Size;
	public:
		Beverages(const _string& Unit,__uint32 Unit_Size=0)://i.e. copies resources
			Unit(Unit),Unit_Size(Unit_Size),Items("Beverages"){}
	#if __cplusplus >= 201103L
		Beverages(_string&& Unit=_string(),unsigned short Unit_Size=0)://i.e. moves resources
			Unit(move(Unit)),Unit_Size(Unit_Size),Items("Beverages"){}
	#endif
		Beverages(float Price,const _string& Name=_string(),const _string& Brand=_string(),const _string& Unit=_string(),__uint32 Unit_Size=0):
			Unit(Unit),Unit_Size(Unit_Size),Items(Price,Name,Brand,"Beverages"){}
	#if __cplusplus >= 201103L
		Beverages(float Price,_string&& Name=_string(),_string&& Brand=_string(),_string&& Unit=_string(),__uint32 Unit_Size=0):
			Unit(move(Unit)),Unit_Size(Unit_Size),Items(Price,move(Name),move(Brand),"Beverages"){}
	#endif
		void Input_Data(istream& in)override{
			cout<<"	Enter Unit: "; in>>Unit; cout<<"	Enter Unit Size (",Unit,"): "; in>>Unit_Size;
		}
		void Display_Data(ostream& out)const override{ out<<", Unit Size: "<<Unit_Size<<" ("<<Unit<<")"; }
		~Beverages(){ cout<<"Beverages dtor\n"; }
		//i.e. explicitly defined to display the indication of destruction, else no need
	};
	
	class Bakery_Items:public Items{
		float Weight;
	public:
		Bakery_Items(float Weight=0):
			Weight(Weight),Items("Bakery_Items"){}
		
		Bakery_Items(float Price,const _string& Name=_string(),const _string& Brand=_string(),float Weight=0):
			Weight(Weight),Items(Price,Name,Brand,"Baking_Items"){}
	#if __cplusplus >= 201103L
		Bakery_Items(float Price,_string&& Name=_string(),_string&& Brand=_string(),float Weight=0):
			Weight(Weight),Items(Price,move(Name),move(Brand),"Baking_Items"){}
	#endif
		void Input_Data(istream& in)override{ cout<<"	Enter Weight: "; in>>Weight; }
		void Display_Data(ostream& out)const override{ out<<", Weight: "<<Weight; } 
		~Bakery_Items(){ cout<<"Bakery_Items dtor\n"; }
	};
	
	class Baking_Items:public Items{
	public:
		Baking_Items():Items("Baking_Items"){}
		
		Baking_Items(float Price,const _string& Name=_string(),const _string& Brand=_string()):
			Items(Price,Name,Brand,"Baking_Items"){}
	#if __cplusplus >= 201103L
		Baking_Items(float Price,_string&& Name=_string(),_string&& Brand=_string()):
			Items(Price,move(Name),move(Brand),"Baking_Items"){}
	#endif
		void Input_Data(istream& in)override{}
		void Display_Data(ostream& out)const override{}
		~Baking_Items(){ cout<<"Baking_Items dtor\n"; }
	};
	
	Vector<Items*> items_list;//i.e. initializing Vector of Items* as double-ptr for pointing dynamic abstract objs
	items_list.push_back(new Beverages(111,"pepsi","pepsico","ml",500));
	items_list.push_back(new Bakery_Items(222,"sandwitch","home-made"));
	items_list.push_back(new Baking_Items);
	
	cout<<"\nItems List (Abstract Objs):"<<'\n';
	for(int i=0;i<items_list.size();++i)
		cout<<i+1<<*items_list[i]<<'\n';
	
	cout<<"\nClearing Items List:"<<'\n';
	for(int i=0;i<items_list.size();++i)
		delete items_list[i];
}

void test_case_5(){
#if __cplusplus >= 201103L
	Vector<int> v={2,-32,12,3,6,5,8};
#else
	Vector<int> v;
	v.reserve(7);
	v.push_back(2);
	v.push_back(-32);
	v.push_back(12);
	v.push_back(3);
	v.push_back(6);
	v.push_back(5);
	v.push_back(8);
#endif
	cout<<"Before:"<<'\n';
#if __cplusplus >= 201103L
	for(const auto& it:v) 										//i.e. efficient alternate to below method (C++11)
		cout<<it<<" ";
#else
	for(Iterator<int> it=v.begin();it!=v.end();++it) 			//i.e. 1) forward direction/ ascending order
		cout<<*it<<" ";
#endif
//#if __cplusplus >= 201103L
//	for(const auto& it:v.reverse_iterator()) 					//i.e. efficient alternate to below method (C++11)
//		cout<<it<<" ";
//#else
//	for(Reverse_Iterator<int> it=v.rbegin();it!=v.rend();++it) 	//i.e. 2) reverse direction/ descending order
//		cout<<*it<<" ";
//#endif
	cout<<'\n';
	
//	Sort::Bubble(v.begin(),v.end());							//i.e. un-comment any of the following sort
//	Sort::Insertion(v.begin(),v.end());							//	   to see its' working at a time
//	Sort::Selection(v.begin(),v.end());
	Sort::Quick(v.begin(),v.end());

	cout<<"After:"<<'\n';
	for(Vector<int>::r_iterator it=v.rend()-1;it!=v.rbegin()-1;--it)    //i.e. 1) forward direction/ ascending order
		cout<<*it<<" ";
//	for(const Vector<int>::iterator& it=v.end()-1;it!=v.begin()-1;--it) //i.e. 2) reverse direction/ descending order
//		cout<<*it<<" ";
	cout<<'\n';
}

#if __cplusplus >= 201103L
test_case_6(){
	cout<<"\nJagged Vector Demonstration:-";
	//i.e. passing 'Vector<int>' in 'counted' to get track/summary of its resources
	int_V1 obj={123,321};//i.e. lvalue obj
	//i.e. using as Jagged Array
	Vector<int_V2> vec_3d={
						int_V2{	
							int_V1{1,2,3,4},
					   		int_V1{11,22,33},
							int_V1{111,222,333,444},
						 	std::move(obj)							
					    },
					   	int_V2{	
						   	int_V1{5,6,7,8},
						  	int_V1{55,66,77,88},
						  	int_V1{555,666,777,888}
					  	}
					};//i.e. size (3Dx2Dx1D): 2x(3,4)x4
	
	for(const auto &__it:vec_3d){
		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<":"<<'\n';
		for(const auto &_it:__it){
			for(const auto &it:_it)
				cout<<it<<" ";
			cout<<'\n';
		}
	}
	
	cout<<"\nMoved obj: ";
	if(!obj.size())
		cout<<"yes";
	else
		cout<<"no";
	cout<<"\nRe-assigning rvalue obj to lvalue holder (invokes move assignment func):"<<'\n';
	obj=int_V1(5,404); 
	for(const auto &it:obj)
		cout<<it<<" ";

	cout<<"\n-------------\n";
	cout<<"clearing row 2 of vector 1 & row 1 of vector 2:";
	vec_3d[0][1].clear();
	vec_3d[1][0].clear();
	for(short i=0;i<vec_3d.size();++i){
		cout<<"\n2D Vector "<<i+1<<":"<<'\n';
		for(short j=0;j<vec_3d[i].size();++j){
			for(short k=0;k<vec_3d[i][j].size();++k)
				cout<<vec_3d[i][j][k]<<" ";
			cout<<'\n';
		}
	}
	cout<<"\n------------\n";
	cout<<"clearing vector 1:";
	vec_3d[0].clear();
	for(const auto &__it:vec_3d){
		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<":"<<'\n';
		for(const auto &_it:__it){
			for(const auto &it:_it)
				cout<<it<<" ";
			cout<<'\n';
		}
	}
}

class Fun{//i.e. for test-case 6
	char c;
	int i;
	_string s;
public:
	Fun(char c,int i,_string& s):c(c),i(i),s(s){}
	Fun(char c='\0',int i=0,_string&& s=_string()):c(c),i(i),s(move(s)){}
	
	friend ostream& operator<<(ostream& out,const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<'\n';
		return out;
	}
	friend istream& operator>>(istream& in,Fun& obj){
		in>>obj.c>>obj.i>>obj.s;
		return in;
	}
};
REGISTER_PARSE_TYPE(Fun);//i.e. defining specialized template for 'Fun' type to get its name for 'Summary'

test_case_7(){
	{//i.e. destroys vec obj
		Vector<counted<Fun>> vec;
		cout<<"\nEmplaced-back objs:"<<'\n';
		counted<Fun> obj('1',22,"333");
		vec.emplace_back(obj);//i.e. here, works same as push_back (passing const reference)
		vec.emplace_back(counted<Fun>('2',33,"444"));//i.e. pasing temporary (rvalue) obj of 'Fun' type
		vec.emplace_back('2',33,"444");
		vec.emplace_back('3',44,"555");//i.e. direct initialization (same as initializing any obj)
		{
			counted<Fun> temp_obj('4',55,"666");
			vec.emplace_back(move(temp_obj));//i.e. moving/stealing temp_obj (passing rvalue reference)
		}
		for(const auto& it:vec)
		 	cout<<it;
	}
}

void test_case_8(){
	cout<<"\nVector working as Container for Student Class/"
		  "Declaring Vector<String> inside Student Class:-"<<'\n';
	
	class Students{//i.e. local class
		unsigned long ID;
		short Batch,Expected_Graduation_Year;
		String Discipline;
		Vector<_string> Current_Courses;
	public:
		Students():
			ID(),Batch(),Expected_Graduation_Year(){}
		//i.e. no need to initialize string & its vector type as their default ctor gets invoked automatically
		
		/*i.e. ctor for direct assigning objs with values to Vector*/
		Students(unsigned long ID,short Batch,short EGY,_string Discp,const std::initializer_list<_string>& list):
			ID(ID),Batch(Batch),Expected_Graduation_Year(EGY),Discipline(Discp),Current_Courses(list){}
		
		void Set_Data(){
			cout<<"Enter ID: ";
			cin>>ID;
			cout<<"Enter Batch: ";
			cin>>Batch;
			cout<<"Enter Expected Graduation Year: ";
			cin>>Expected_Graduation_Year;
			cout<<"Enter Discipline: ";
			cin.sync();
			cin>>Discipline;
			cout<<"Current Courses Count: ";
			unsigned short Current_Courses_Count;
			cin>>Current_Courses_Count;
			Current_Courses.reserve(Current_Courses_Count);
			cout<<"Enter All Current Courses:"<<'\n';
			cin>>Current_Courses;
		}
		void Display_Data()const{
			cout<<"ID: "<<ID<<'\n'
				<<"Batch: "<<Batch<<'\n'
				<<"Expected Graduation Year: "<<Expected_Graduation_Year<<'\n'
				<<"Discipline: "<<Discipline<<'\n'
				<<"Current Courses: "<<'\n'<<"\t";
			for(const auto& it:Current_Courses)
				cout<<it<<" ";
		}
	};
	
	cout<<"\nAssignment of Student Obj to Vector through brace enclosed initializer-list:"<<'\n';
	{
		Students obj(190273,2019,2023,"BS (CS)",{"Data-Structures","NC","TOA","Prob & Stats","Socio"}),
				 obj2(obj),obj3;
		Vector<Students> temp_vec,Vec={obj,obj2,obj3,Students(99,99,99,"99",{"AAAaaa","123321"}),
							   Students(3,2,1,"0",{}),Students()};
		temp_vec=Vec; //i.e.copy assignment
		cout<<"\nAFTER COPY ASSIGNMENT: (temp_vec)\n";
		for(auto& it:temp_vec)
			cout<<"Student "<<(&it-&temp_vec[0])+1<<" Data:"<<'\n',
			it.Display_Data(),cout<<'\n';
			/*Note: You can run multiple commands with one ';' provided that they are seperated with comma
					& end with semicolon */
		
		Vector<Students> temp={Students(1,1,1,"1",{"1"}),Students(2,2,2,"2",{"2","2"}),Students(3,3,3,"3",{"3","3","3"})};
		Swap(Vec,temp);
		cout<<"\nAFTER SWAP:\nVec:"<<'\n';
		for(const auto& it:Vec)
			cout<<"Student "<<(&it-&Vec[0])+1<<" Data:"<<'\n',
			it.Display_Data(),cout<<'\n';
		cout<<"temp:"<<'\n';
		for(const auto& it:temp)
			cout<<"Student "<<(&it-&temp[0])+1<<" Data:"<<'\n',
			it.Display_Data(),cout<<'\n';
	}

	cout<<"\nAssignment of Student Obj to Vector through '[]' operator:"<<'\n';
	unsigned short vec_size;
	cout<<"\nEnter Size of Student Vector (DSA): ";
	cin>>vec_size;
	Vector<Students> Vec;
	Vec.reserve(vec_size);
	Students obj;
	for(unsigned short i=0;i<vec_size;++i){
		cout<<"\nEnter Data for Student "<<i+1<<":"<<'\n';
		obj.Set_Data();
		Vec.push_back(obj);//i.e. triggers copy assignment func for student
	}
	cout<<"\nRESULT:"<<'\n';
	for(const auto& it:Vec){
		cout<<"Student "<<(&it-&Vec[0])+1<<" Data:"<<'\n';
		it.Display_Data();
		//Vec[i+1].Display_Data();//i.e. test-case for exception error
		cout<<'\n';
	}
}

void test_case_9(){
//	counted<String> vec[]{"foo","bar","baz"};//Raw Array Method (suprisingly, compilers do optimize the raw arrays)
	
//	Vector<counted<String>> vec;//{"asad","user","ali"};//Method#1
//	vec.reserve(3);
//	vec.emplace_back("asad");
//	vec.emplace_back("user");
//	vec.emplace_back("ali");
	
	auto vec=make_vector<counted<String>>("asad","umer","ali");//Method#2
	//i.e. optimized method as compare to initializer_list ctor (especially for r-values)
	
//	vector<counted<string>> vec{"foo","bar","baz"};//i.e. initializer_list Method
	
	/*NOTE: 
		all above methods give 3 direct constructions only
		except the initializer_list method, which gives us extra 3 copies. 
	*/
}
#endif

/*  Test Cases:
	1) covers the basic operations (use of modifiers)
	2) covers the basic operations (use of modifiers)
	3) demonstration of copy assingment & construction in nested Vector while safely using/storing
	   same objs inside Vector
	4) using Vector as container for local abstract objs of Items class by utilizing the concept
	   of polymorphism (i.e. not ideal, use handler-class specially dedicated for pointer-types)
	5) using sorting algorithms with different formats of iterators
	6) direct initialization of 3d jagged vector & understanding move-semantics, while utilizing
	   instance_counter to keep track of vector's constructions & destructions
	7) focus on best use of emplace_back (as it directly pushes another class objs)
	8) using Vector<String> inside a local class & testing copy asignments with it
	9) methods to initialize Vector in optimized way (i.e. perfect use of make_vector function)
*/

int main(){	
	test_case_1();
//	test_case_2();
//	test_case_3();
//	test_case_4();
//	test_case_5();
	/*Note: Enable C++11 in order to see the working of following test-cases */
//	test_case_6();
//	test_case_7();
//	test_case_8();
//	test_case_9();
	return 0;
}
