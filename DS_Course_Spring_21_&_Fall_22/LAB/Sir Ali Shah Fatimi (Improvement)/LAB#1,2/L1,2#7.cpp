#include <iostream>

using std::cout;

//topics covered: understanding 'rule of three' & 'safe arrays'

class Numbers{
	int size, *data;
public:
	template<typename... T>
	Numbers(T... attrbs)://variadic ctor for taking values as std::initializer_list
		size(sizeof...(attrbs)),
		data(new int[size]{attrbs...}){}

#if	1 /* (deep) copy semantics */
	Numbers(const Numbers& other)://copy ctor
		size(0),data(new int[other.size]){
 		while(size<other.size)
			data[size]=other.data[size++];
	}
	Numbers& operator=(const Numbers& other){//copy assignment operator
		if(this!=&other){
	  		delete[] data;
	  		data=new int[other.size];
 			for(size=0;size<other.size;++size)
				data[size]=other.data[size];
	 	}
		return *this;
 	}
#endif

	int& operator[](size_t n){//accessor (getter + setter): gives read & write both access
		if (n>=size)//parameter is of unsigned type, hence condition 'n < 0' is excluded
			throw false;
		return data[n];
	}
	
	int get_size()const{ return size; }//getter
	
	//overloaded 'cout' (console output) method
	friend std::ostream& operator<<(std::ostream& out,const Numbers& self){
		for(int i=0;i<self.size;++i)
			out<<self.data[i]<<' ';
		return out;
	}
	
	~Numbers(){ delete[] data; }//dtor
};

int main(){
	Numbers n1{11,44,66,77,909};
	
	cout<<"n1 object:-\nvalues: "<<n1
		<<"\nsize: "<<n1.get_size()<<'\n';
	
	/* Understanding Safe Array */
	try{
		cout<<"value at index '2': "
			<<n1[2]<<'\n';
		cout<<"value at index '7': "
			<<n1[7]<<'\n';//throws exception since given index is out of range
	}
	catch(bool){
		cout<<"Exception occured!\n"
			<<"Error: given index is out of bound!\n";	
	}
	
	/* Understanding Rule of Three */
	Numbers n2 = n1;//gives undefined behaviour (error) when 'copy ctor' isn't defined
	
/* reason for error?:
  - here n2 points the same 'data' memory segment as n1
    (because of shallow copy)
	
  - hence, when dtor of n1 deallocates the data segment,
    n2's dtor can't deallocate again the shared data segment
    as it's already destructed/deallocated
    
   why shallow copy?:
  - since no explicit copy ctor or copy assignment operator is defined,
    the class uses the default copy ctor in which every member attribute
	of class is copied directly. hence in case of pointers, instead of copying
	data pointed by them, they copy only the address of dynamic resources.
	
   possible fixes/solutions:
  - make declarations of copy ctor & copy assignment operator 'private'
  	(this will give compile error if user accidently uses them)
	
  - or completely follow 'rule of three'
  	(i.e. define copy ctor & copy assignment operator explicitly)
*/
	
	return 0;
}
