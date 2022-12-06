#include "Vector.hpp"
#include "String.hpp"
#include "../Algorithms/Sorts.hpp"
#include "../Utilities/Instance_Counter.hpp"

typedef unsigned long long __uint64;
typedef unsigned int __uint32;
typedef unsigned short __uint16;

typedef Vector<String> string_V1;
typedef Vector<int> int_V1;
typedef Vector<int_V1> int_V2;

#if __cplusplus < 201103L
#define override
#else
using std::move;
#endif
using std::cout;
using std::cin;
using std::istream;
using std::ostream;

template<typename T>
void print_type(){ cout<<__PRETTY_FUNCTION__<<'\n'; }//for debugging


void test_case_1(){
	int_V1 vec,	   	   		//just declaration, no allocation
	       vec1(10),	   	//allocate size with 1st arg & initialize the whole vector with 0/""/''
	   	   vec2(5,123);   	//allocate size with 1st arg & initialize the whole vector with 2nd arg
//	int_V1 vec4({99,88,77});//allocate with brace enclosed initializer_list ctor(C++11)
	
	
//	cout<<"vec:"<<'\n'
//		<<"size: "<<vec.size()<<'\n'
//		<<"capacity: "<<vec.capacity()<<'\n';
//
//	vec.push_back(2);
//	vec.push_back(4);
//	cout<<"(after 2 push_back)"<<'\n'
//		<<"size: "<<vec.size()<<'\n'
//		<<"capacity: "<<vec.capacity()<<'\n'
//		<<"elements: ";
//	for(int i=0;i<vec.size();++i)
//		cout<<vec[i]<<' ';
	
	
	cout<<"\n\nvec1:\nelements: "<<vec1
		<<"\nsize: "<<vec1.size()<<'\n'
		<<"capacity: "<<vec1.capacity()<<'\n';

	vec1.push_back(4);
	cout<<"(after push_back)\n"
		<<"size: "<<vec1.size()<<'\n'
		<<"capacity: "<<vec1.capacity()<<'\n';
	
	
	cout<<"\nvec2:\nelements: "<<vec2
		<<"\nsize: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';

	vec2.pop_back();
	cout<<"(after pop_back)\n"
		<<"size: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';

	vec2.reserve(10);
	cout<<"(after reserve)\n"
		<<"size: "<<vec2.size()<<'\n'
		<<"capacity: "<<vec2.capacity()<<'\n';

//	vec2.shrink_to_fit();
//	cout<<"(after shrink_to_fit)\n"
//		<<"size: "<<vec2.size()<<'\n'
//		<<"capacity: "<<vec2.capacity()<<'\n'
//		<<"elements: "<<vec2<<'\n';
}

void test_case_2(){
	{//destroying vector v
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
    	cout<<"(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\n";
    	v.clear();
    	cout<<"After clear: "
    		<<"(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\n"
    		<<"After 3 push_back: ";
		for(int i=1;i<=3;++i)
		    v.push_back(i),cout<<v[i-1]<<", ";
    	cout<<"(size: "<<v.size()<<", capacity: "<<v.capacity()<<")\n";
  	}
    String c;
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
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<")\n"
		<<"After reserve: ";
	c.reserve(15);
	for(int i=0;i<c.size();++i)
		cout<<c[i]<<", ";
	cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<")\n"
		<<"After resize: ";
		c.resize(10,'z');
		for(int i=0;i<c.size();++i)
			cout<<c[i]<<", ";
		cout<<"(size: "<<c.size()<<", capacity: "<<c.capacity()<<")\n";
	
	cout<<"\nString data_type\nElement in vector a: ";
#if __cplusplus >= 201103L
	string_V1 a({String("asad"),String("ali"),String("usman")}); //C++11
#else
	string_V1 a;
	a.push_back("asad"),a.push_back("ali"),a.push_back("usman");
#endif
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<")\n"
		<<"After resize: ";
	a.resize(8);
	for(int i=0;i<a.size();++i)
		cout<<a[i]<<", ";
	cout<<"(size: "<<a.size()<<", capacity: "<<a.capacity()<<")\n";
}

void test_case_3(){
	cout<<"\n\nDeclaring Nested Array without Initializer-List & Index-based Accessing:-\n";
	Vector<int_V2> vec_3d;//3D(l x m x n); l=2,m=5,n=6
	vec_3d.reserve(2);
	{//destroys 2d arr
		int_V2 vec_2d;
		vec_2d.reserve(5);
		{//destroys 1d arr
			int_V1 vec_1d;
			vec_1d.reserve(6);
			for (short i=0;i<vec_1d.capacity();++i)
 				vec_1d.push_back(i+10);//assigning values (1-10)
			for(short i=0;i<vec_2d.capacity();++i)
				vec_2d.push_back(vec_1d);//assigning 1d vec address to 2d vec
		}
		for(short i=0;i<vec_3d.capacity();++i)
			vec_3d.push_back(vec_2d);//assigning 2d vec address to 3d vec
	}//note: use emplace_back for vec_2d & vec_3d in C++11
	
	Vector<int_V2> vec_x,vec_y=vec_x=vec_3d;
	/*Note: copy assignment (3d to x), copy ctor (x to y)
	  For Testing: Replace 'vec_x' with others in below loop */
	for(short i=0,j;i<vec_x.size();++i){
		cout<<"\n2D Vector "<<i+1<<":\n";
		for(j=0;j<vec_x[i].size();++j)
				cout<<vec_x[i][j]<<'\n';
	}
	cout<<"\nTotal Size Occupied: "<<vec_3d.size()*vec_3d[0].size()*vec_3d[0][0].size();
}

/*Abstract/Interface Class (for test_case_4) */
class Items{
	__uint64 ID;
	__uint16 Quantity;//0-65535
	float Price;
	String Name,Brand,Category;
public:
	Items():ID(ID_Generator()),Price(0),Quantity(1){}//default ctor
	
	Items(const String& Category):ID(ID_Generator()),Price(0),Quantity(1),Category(Category){}//copies resources
#if __cplusplus >= 201103L
	Items(String&& Category):ID(ID_Generator()),Price(0),Quantity(1),Category(move(Category)){}//moves resources
#endif
	Items(float Price,const String& Name,const String& Brand,const String& Category):
		ID(ID_Generator()),Price(Price),Name(Name),Brand(Brand),Quantity(1),Category(Category){}
#if __cplusplus >= 201103L
	Items(float Price,String&& Name,String&& Brand,String&& Category):
		ID(ID_Generator()),Price(Price),Name(move(Name)),Brand(move(Brand)),Quantity(1),Category(move(Category)){}
#endif
	static __uint64 ID_Generator(const bool Reset_Flag=false){//can produce upto 20 digit no.
		static __uint64 _ID=40400;
		if(Reset_Flag){
			_ID=40400;
			return _ID;
		}
		return ++_ID;
	}
	virtual void Input_Data(istream&)=0;//pure virtual func, acts like hooker for below friend '>>' operator func
	friend istream& operator>>(istream& in,Items &obj){
		cout<<"	Enter Product Name: ";
		in.sync();//neglects remaining buffer
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
	virtual ~Items(){}//virtual dtor -> to destruct in correct order
};

void test_case_4(){
	/* Local Derived Classes for Abstract objs */
	class Beverages:public Items{
		String Unit; __uint32 Unit_Size;
	public:
		Beverages(const String& Unit,__uint32 Unit_Size=0)://copies resources
			Unit(Unit),Unit_Size(Unit_Size),Items("Beverages"){}
	#if __cplusplus >= 201103L
		Beverages(String&& Unit=String(),unsigned short Unit_Size=0)://moves resources
			Unit(move(Unit)),Unit_Size(Unit_Size),Items("Beverages"){}
	#endif
		Beverages(float Price,const String& Name=String(),const String& Brand=String(),const String& Unit=String(),__uint32 Unit_Size=0):
			Unit(Unit),Unit_Size(Unit_Size),Items(Price,Name,Brand,"Beverages"){}
	#if __cplusplus >= 201103L
		Beverages(float Price,String&& Name=String(),String&& Brand=String(),String&& Unit=String(),__uint32 Unit_Size=0):
			Unit(move(Unit)),Unit_Size(Unit_Size),Items(Price,move(Name),move(Brand),"Beverages"){}
	#endif
		void Input_Data(istream& in)override{
			cout<<"	Enter Unit: "; in>>Unit; cout<<"	Enter Unit Size (",Unit,"): "; in>>Unit_Size;
		}
		void Display_Data(ostream& out)const override{ out<<", Unit Size: "<<Unit_Size<<" ("<<Unit<<')'; }
		~Beverages(){ cout<<"Beverages dtor\n"; }
		//explicitly defined to display the indication of destruction, else no need
	};
	
	class Bakery_Items:public Items{
		float Weight;
	public:
		Bakery_Items(float Weight=0):
			Weight(Weight),Items("Bakery_Items"){}
		
		Bakery_Items(float Price,const String& Name=String(),const String& Brand=String(),float Weight=0):
			Weight(Weight),Items(Price,Name,Brand,"Baking_Items"){}
	#if __cplusplus >= 201103L
		Bakery_Items(float Price,String&& Name=String(),String&& Brand=String(),float Weight=0):
			Weight(Weight),Items(Price,move(Name),move(Brand),"Baking_Items"){}
	#endif
		void Input_Data(istream& in)override{ cout<<"	Enter Weight: "; in>>Weight; }
		void Display_Data(ostream& out)const override{ out<<", Weight: "<<Weight; } 
		~Bakery_Items(){ cout<<"Bakery_Items dtor\n"; }
	};
	
	class Baking_Items:public Items{
	public:
		Baking_Items():Items("Baking_Items"){}
		
		Baking_Items(float Price,const String& Name=String(),const String& Brand=String()):
			Items(Price,Name,Brand,"Baking_Items"){}
	#if __cplusplus >= 201103L
		Baking_Items(float Price,String&& Name=String(),String&& Brand=String()):
			Items(Price,move(Name),move(Brand),"Baking_Items"){}
	#endif
		void Input_Data(istream& in)override{}
		void Display_Data(ostream& out)const override{}
		~Baking_Items(){ cout<<"Baking_Items dtor\n"; }
	};
	
	Vector<Items*> items_list;//initializing Vector of Items* as double-ptr for pointing dynamic abstract objs
	items_list.push_back(new Beverages(111,"pepsi","pepsico","ml",500));
	items_list.push_back(new Bakery_Items(222,"sandwitch","home-made"));
	items_list.push_back(new Baking_Items);
	
	cout<<"\nItems List (Abstract Objs):\n";
	for(int i=0;i<items_list.size();++i)
		cout<<i+1<<*items_list[i]<<'\n';
	
	cout<<"\nClearing Items List:\n";
	for(int i=0;i<items_list.size();++i)
		delete items_list[i];
}

void test_case_5(){
#if __cplusplus >= 201103L
	Vector<int> v({2,-32,12,3,6,5,8});
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
	cout<<"Before:\n";
#if __cplusplus >= 201103L
	for(auto& it:v)//1) forward direction/ ascending order
		cout<<it<<' ';
#else
	for(Iterator<int> it=v.begin();it!=v.end();++it)
		cout<<*it<<' ';
#endif
	cout<<'\n';
	
#if __cplusplus >= 201103L
	for(auto& it:v.r_iterator_adapter())//2) reverse direction/ descending order
		cout<<it<<' ';
#else
	for(Reverse_Iterator<int> it=v.rbegin();it!=v.rend();++it)
		cout<<*it<<' ';
#endif
	cout<<'\n';
	
	sort::bubble(v.begin(), v.end());				//un-comment any of the following sort
//	sort::insertion<int>(v.begin(), v.end());		//to see its working at a time
//	sort::selection(v.begin(), v.end());
//	sort::quick(v.begin(), v.end());
	
	cout<<"After:\n";
	for(Vector<int>::r_iterator it=v.rend()-1;it!=v.rbegin()-1;--it)//1) forward direction/ ascending order
		cout<<*it<<' ';
	cout<<'\n';
	
	for(Vector<int>::iterator it=v.end()-1;it!=v.begin()-1;--it)//2) reverse direction/ descending order
		cout<<*it<<' ';
	cout<<'\n';
}

#if __cplusplus >= 201103L
void test_case_6(){
	cout<<"\nJagged Vector Demonstration:-";
	int_V1 obj({123,321});//lvalue obj
	//using as Jagged Array
	Vector<int_V2> vec_3d({//3Dx2Dx1D
						int_V2({
							int_V1({1,2,3,4}),
					   		int_V1({11,22,33}),
							int_V1({111,222,333,444}),
						 	move(obj)							
					    }),
					   	int_V2({	
						   	int_V1({5,6,7,8}),
						  	int_V1({55,66,77,88}),
						  	int_V1({555,666,777,888})
					  	})
					});
	
//	for(const auto &__it:vec_3d){
//		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<':'<<'\n';
//		for(const auto &_it:__it){
//			for(const auto &it:_it)
//				cout<<it<<' ';
//			cout<<'\n';
//		}
//	}
	
	cout<<"\nMoved obj: "<<(obj.size()?"no":"yes");
	cout<<"\nRe-assigning rvalue obj to lvalue holder (invokes move assignment func):"<<'\n';
	obj=int_V1(5,404); 
	for(const auto &it:obj)
		cout<<it<<' ';
	cout<<"\n-------------\n";
	
	cout<<"clearing row 2 of vector 1 & row 1 of vector 2:";
	vec_3d[0][1].clear();
	vec_3d[1][0].clear();	
	for(short i=0,j,k;i<vec_3d.size();++i){
		cout<<"\n2D Vector "<<i+1<<":\n";
		for(j=0;j<vec_3d[i].size();++j){
			for(k=0;k<vec_3d[i][j].size();++k)
				cout<<vec_3d[i][j][k]<<' ';
			cout<<'\n';
		}
	}
	cout<<"\n------------\n";

//	cout<<"clearing vector 1:";
//	vec_3d[0].clear();
//	for(const auto &__it:vec_3d){
//		cout<<"\n2D Vector "<<(&__it-&vec_3d[0])+1<<":\n";
//		for(const auto &_it:__it){
//			for(const auto &it:_it)
//				cout<<it<<' ';
//			cout<<'\n';
//		}
//	}
}

class Fun{//for test_case_6
	char c;
	int i;
	String s;
public:
	Fun(char c,int i,String& s):c(c),i(i),s(s){}
	Fun(char c='\0',int i=0,String&& s=String()):c(c),i(i),s(move(s)){}
	
	friend ostream& operator<<(ostream& out,const Fun& obj){
		out<<obj.c<<", "<<obj.i<<", "<<obj.s<<'\n';
		return out;
	}
	friend istream& operator>>(istream& in,Fun& obj){
		in>>obj.c>>obj.i>>obj.s;
		return in;
	}
};

void test_case_7(){
	{//destroys vec obj
		Vector<Fun> vec;
		cout<<"\nEmplaced-back objs:"<<'\n';
		Fun obj('1',22,"333");
		vec.emplace_back(obj);//here, works same as push_back (passing const reference)
		vec.emplace_back(Fun('2',33,"444"));//pasing temporary (rvalue) obj of 'Fun' type
		vec.emplace_back('2',33,"444");
		vec.emplace_back('3',44,"555");//direct initialization (same as initializing any obj)
		{
			Fun temp_obj('4',55,"666");
			vec.emplace_back(move(temp_obj));//moving/stealing temp_obj (passing rvalue reference)
		}
		for(const auto& it:vec)
		 	cout<<it;
	}
}

//defining specialized template to get their typename at run-time:
REGISTER_PARSE_TYPE(String);
//Note: Here, macro replaces the specialized template struct alongwith its static member initialization

typedef counted<String> c_str;

void test_case_8(){	
//	c_str vec_1[]{"foo", "bar", "baz"};//suprisingly, compilers do optimize the raw arrays
	
//	Vector<c_str> vec_2;
//	vec_2.reserve(3);
//	vec_2.emplace_back("asad");
//	vec_2.emplace_back("user");
//	vec_2.emplace_back("ali");
	
	Vector<c_str> vec_3({"user", "asad", "ali"});//gives optimized results for r-values
	
//	Vector<c_str> vec_4({c_str("user"), c_str("user"), c_str("ali")});
	
/* for copying l-value (use vec 4 format), like this:
	c_str v="user-copy";
	Vector<c_str> vec_4({v, c_str("user"), c_str("ali")});
*/
	
//	Vector<c_str> vec_5{"foo", "bar", "baz"};//available when brace initializer_list ctor is uncommented in Vector.hpp
	
	/*IMP-NOTES:
		vec 1 to 3: gives direct constructions only
		vec 4: gives extra 3 moves (acceptable).
		vec 5: gives extra 3 copies (expensive, worst for r-values).
	  SIDE-NOTES (for lvalues):
	  	vec 2 & 3: best for passing lvalues (gives only 1 extra copy per direct construction)
	  	vec 4: not best for lvalues, but acceptable (gives 1 extra copy & 1 extra move per direct construction)
	*/
}

void test_case_9(){
	/* for primitive testing */
//	Vector<int> vec({11,22,33,44,55,66,77,88,99});
//	
//	vec.insert(717);
//	vec.insert(434, 2);
//	vec.erase(0);
//	vec.erase(4);
//	
//	cout<<vec<<'\n';
	
	/* for non-primitive (object) testing */
	Vector<c_str> vec({"foo","bar","baz"});
	/* important-note for understading shifting/swapping:
	  - copy/move complexity for insert is 3(swapping_times+1)+2
	  - copy/move complexity for erase is 3(swapping_times+1)
	*/
	vec.insert("LOL");//3 swaps => 11 moves
//	vec.insert("taebak", 2);//1 swap => 5 moves
//	vec.erase();//2 swaps => 6 moves
//	vec.erase(2);//0 swaps => 0 moves
	
	cout<<vec<<'\n';
}
#endif

/*  Test Cases:
	1) covers different methods of constructor calling & some basic operations.
	
	2) understanding the use of modifiers & their changes.
	
	3) demonstration of copy assingment & construction in nested Vector while safely
	   using/storing same objs inside Vector.
	   
	4) using Vector as container for local abstract objs of Items class by utilizing the concept
	   of polymorphism (not ideal, use handler-class specially dedicated for pointer-types).
	   
	5) using sorting algorithms with different formats of iterators.
	
	6) direct initialization of 3d jagged vector & understanding move-semantics.
	
	7) focus on best use of emplace_back (as it directly pushes another class objs).
	
	8) understanding methods to initialize Vector in optimized way with instance_counter
	   (inlcudes: perfect use of make_vector function).
	   
	9) understanding & testing shift methods with instance_counter.
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
