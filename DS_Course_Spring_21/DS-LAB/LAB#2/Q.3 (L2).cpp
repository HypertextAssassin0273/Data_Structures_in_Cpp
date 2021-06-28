#include<iostream>
using namespace std;
#define __uint64 unsigned long long

template<typename T>
/*Note: 
	In templates, typename is used for independant & dependant (nested/class-based)
	type of arguments whereas, class is used only for independant type of arguments. 
*/
class Array final{
	__uint64 _size;
	T *data;
	
	class Iterator{//i.e. nested iterator class wrapper for any pointer-based/node class,
    	T* ptr;	   //     in order to utilize C++11 range-based 'for' loop.
   	public:
    	Iterator(T* ptr):ptr(ptr){}
    	Iterator operator++(){ ++ptr; return *this; }
    	bool operator!=(const Iterator& other)const{ return ptr!=other.ptr; }
		/*Note: 
			ptrs are defined for '!=' operator, but if this is 2d or greator Array then
			'!=' operator func will be called recursively for Array class until it gets 
			the definition of ptr. Then it recursively returns the flag value on the
			basis of ptr comparison. (this process is also known as tracing) 
		*/
		T& operator*()const{ return *ptr; }//i.e. gives read & write access
    };
public:
	Array(__uint64 n=1):data(new T[n]),_size(n){}
	~Array(){ delete[] data; };
	Array(const Array& v):data(new T[v._size]),_size(v._size){//i.e. copy ctor
 		copy(v.data,v.data+_size,data);
 		/*Note:
		 	It copies all elements directly on address. Hence, it's prefered to use
		 	this rather than using loop with assignment operator as it increases
			overhead for nested template class objs (i.e. it recursively deduces
			to the overloaded assignment operator func). */
	}
	Array& operator=(const Array& v){//i.e. copy assignment func
 		T* new_data=new T[v._size];
 		copy(v.data,v.data+v._size,new_data);
 		delete[] data;
 		data=new_data;
 		_size=v._size;
	 	return *this;
 	}
 	T& operator[](__uint64 n)const{ return data[n]; }//i.e. gives read & write access
 	__uint64 size()const{ return _size; }
 	
 	//i.e. overloaded/replaced methods for 'range-based loop'
	Iterator begin()const{ return Iterator(data); }//i.e. points to first element
	Iterator end()const{ return Iterator(data+_size); }//i.e. points to last element
	/*Note: 
		Here, Iterator class ctor's returns '*this pointer'. People usually misunderstood the  
		concept that ctor has no return type which is true but at the same time the reason is 
		because it's fixed for returning *this pointer (i.e. pointer to its current obj) 
	Proof: 
		When we use dynamic allocation, we call the ctor of class in different syntaxes/formats
	*/
};
int main(){
	short i,arr_size;
	cout<<"Enter Size of 2D-Array: ";
	cin>>arr_size;
	Array<Array<int>> arr_2d(arr_size);
	for (auto& _it: arr_2d){//i.e. range-based for loop (C++11 Construct)
		cout<<"\nEnter Size of Array "<<++i<<" (1D): ";
		cin>>arr_size;
		Array<int> arr_1d(arr_size);//i.e. gets destroyed after one cycle of loop
		cout<<"Enter Elements:"<<endl;
		for (auto& it: arr_1d)
			cin>>it;
	 	_it=arr_1d;//i.e. assigning 1d_arr addresses to 2d_arr
	}
	/*Note:
		auto& it-> iterator points the acutal memory location  
		auto it -> iterator points the copy of acutal memory location 
				   (i.e. any modification in this mode will only affect the copy) */
	cout<<"\nRESULT:"<<endl;
	for(const auto& _it: arr_2d){//i.e. read-only access to iterator
		for(const auto& it: _it)
			cout<<it<<" ";
		cout<<endl;
	}
//	for(short i=0;i<arr_2d.size();++i){//i.e. normal iterative test-case
//		for(short j=0;j<arr_2d[i].size();++j)
//			cout<<arr_2d[i][j]<<" ";
//		cout<<endl;
//	}
 	return 0;
}
/*Note: 
	Use 'auto' only when u know its deduced type will not affect results.
	Usually it's used with iterators since they always deduce into their specified iterator type.
	But, this is not the case with normal primitive data-types. (i.e. 'int' expected iterator 
	might get deduce into 'unsigned int' or 'short' & will cause trouble in results)
Disadvantage:
	Too many use of 'auto' increases the compiler-overhead for deducing their types.
		
For more info about different variants/use-cases of 'auto', visit the link:
https://stackoverflow.com/questions/52153732/using-references-as-control-variable-in-range-based-for-loops-in-c
*/
