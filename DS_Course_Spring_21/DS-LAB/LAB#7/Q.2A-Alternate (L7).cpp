#include<iostream>
using namespace std;

//Note: include "Vector.hpp" after including iostream & using namespace std
#include"Vector.hpp"

template<typename T>
void Vector<T>::sort(bool direction_flag){//i.e. selection sort
	for (__uint32 i=0;i<_size-1;++i){
        __uint32 min_index=i;
        for (__uint32 j=i+1;j<_size;++j){
            if(direction_flag){//i.e. ascending (by default)
				if(*(T*)(data+sizeof(T)*j)<*(T*)(data+sizeof(T)*min_index))
        	       	min_index=j;
			}
			else{//i.e. descending
				if(*(T*)(data+sizeof(T)*j)>*(T*)(data+sizeof(T)*min_index))
        	       	min_index=j;
			}
        }
        swap(*(T*)(data+sizeof(T)*i),*(T*)(data+sizeof(T)*min_index));
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
	vec.sort(0);//i.e. using selection-sort in descending order
	cout<<vec;
	return 0;
}
