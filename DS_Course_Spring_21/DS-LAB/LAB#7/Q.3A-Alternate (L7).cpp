#include<iostream>
using namespace std;

//Note: include "Vector.hpp" after including iostream & using namespace std
#include"Vector.hpp"

template<typename T>
void Vector<T>::sort(bool direction_flag){//i.e. insertion-sort
	for (__int64 j,i=1;i<_size;++i){
      	T key=*(T*)(data+sizeof(T)*i);
       	if(direction_flag)
			for (j=i-1;j>=0&&*(T*)(data+sizeof(T)*j)>key;--j)
            	*(T*)(data+sizeof(T)*(j+1))=*(T*)(data+sizeof(T)*j);
        else
            for (j=i-1;j>=0&&*(T*)(data+sizeof(T)*j)<key;--j)
            	*(T*)(data+sizeof(T)*(j+1))=*(T*)(data+sizeof(T)*j);
        *(T*)(data+sizeof(T)*(j+1))=key;
    }
}

int main(){
#if __cplusplus >= 201103L
	Vector<int> vec{3,-1,7,5,4};
#else
	Vector<int> vec;
	vec.push_back(3);
	vec.push_back(-1);
	vec.push_back(7);
	vec.push_back(5);
	vec.push_back(4);
#endif
	cout<<vec;
	vec.sort();//i.e. using insertion-sort in ascending order
	cout<<vec;
	return 0;
}
