#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard,\
		which can be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
#endif

/*i.e. Type_Parse_Traits template struct for defining its' specialized templates*/
template<typename T>
struct type_parse_traits;
#define REGISTER_PARSE_TYPE(type) \
template<>struct type_parse_traits<type>{ static const char* name; }; \
const char* type_parse_traits<type>::name = #type //i.e. '#' converts 'type' into string & initializes 'name'

/*i.e. Counter Class for keeping track of instance's resources*/					
template <typename T>
class instance_counter{//i.e. generates summary of each type after complete execution of main() func
	struct counter{
		bool flag;//i.e. pass 'true' in ctor to view summary
    	__int64 num_construct,num_copy,num_move,num_destruct;
		
		counter(bool flag=0): //i.e. ctor
			flag(flag),num_construct(0),num_copy(0),num_move(0),num_destruct(0){}
		
		~counter(){//i.e. dtor
			if(flag){
				std::cout<<"\nSummary ("<<type_parse_traits<T>::name<<"):-\n"
				 	<<num_construct<<" direct constructions\n"
    	    	    <<num_copy<<" copies\n"
    	        	<<num_move<<" moves\n"
        	    	<<num_construct+num_copy+num_move<<" total constructions\n"
            		<<num_destruct<<" destructions ";
            	if ((num_construct+num_copy+num_move)==num_destruct)
            	   	std::cout<<"(no leaks)\n";
            	else
            	   	std::cout<<"(WARNING: potential leak)\n";
			}
        }
    };
	static counter icounter;//i.e. static counter obj

public:
    instance_counter()noexcept{ ++icounter.num_construct; }
    instance_counter(const instance_counter&)noexcept{ ++icounter.num_copy; }
    instance_counter(instance_counter&&)noexcept{ ++icounter.num_move; }
    //i.e. simulates both copy-assign and move-assign funcs
    instance_counter& operator=(instance_counter)noexcept{ return *this; }
    ~instance_counter(){ ++icounter.num_destruct; }
};
//Static Initialization Format: datatype class::static_variable;
template<typename T>
typename instance_counter<T>::counter instance_counter<T>::icounter(true);

/*i.e. combining instantiated class with counter class to get same results*/
template<typename T>
struct counted:T,instance_counter<T>{
    using T::T;//i.e. inheriting ctor (C++11 Construct)
	//Note: it provides the same interface for the class that is instantiated
};

#endif
