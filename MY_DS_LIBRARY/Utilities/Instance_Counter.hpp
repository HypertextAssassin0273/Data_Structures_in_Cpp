#if __cplusplus < 201103L
#error: This file requires compiler and library support for the ISO C++ 2011 standard \
		and must be enabled with the -std=c++11 or -std=gnu++11 compiler options.
#else

#ifndef INSTANCE_COUNTER_GUARD
#define INSTANCE_COUNTER_GUARD 1

#include<iostream>

/* Type_Parse_Traits template struct for defining its' specialized templates: */
template<typename T>
struct type_parse_traits;

#define REGISTER_PARSE_TYPE(type) \
template<>struct type_parse_traits<type>{ static const char* name; }; \
const char* type_parse_traits<type>::name = #type //'#' converts 'type' into string & initializes 'name'

/* Counter Class for keeping track of instance's resources: */					
template <typename T>
class instance_counter{//generates summary of each type after complete execution of main() func
	struct counter{
		bool flag;//pass 'true' in ctor to view summary
    	__int64 num_construct, num_copy, num_move,num_destruct;
		
		counter(bool flag=0)noexcept://ctor
			flag(flag), num_construct(0), num_copy(0), num_move(0), num_destruct(0){}
		
		~counter(){//dtor
			if(flag){
				std::cout<<"\nSummary ("<<type_parse_traits<T>::name<<"):-\n"
				 	<<num_construct<<" direct constructions\n"
    	    	    <<num_copy<<" copies\n"
    	        	<<num_move<<" moves\n"
        	    	<<num_construct+num_copy+num_move<<" total constructions\n"
            		<<num_destruct<<" destructions "
            		<<(num_construct+num_copy+num_move==num_destruct?"(no leaks)\n":"(WARNING: potential leak)\n");
			}
        }
    };
	static counter icounter;//static counter object
	
public:
	instance_counter()noexcept{ ++icounter.num_construct; }//ctor
	
	instance_counter(const instance_counter&)noexcept{ ++icounter.num_copy; }//copy ctor
	instance_counter(instance_counter&&)noexcept{ ++icounter.num_move; }//move ctor
    
	//simulates both copy-assignment and move-assignment operator methods:
	instance_counter& operator=(instance_counter)noexcept{ return *this; }
	
	~instance_counter(){ ++icounter.num_destruct; }//dtor
};
//static initialization format: datatype class::static_variable;
template<typename T>
typename instance_counter<T>::counter instance_counter<T>::icounter(true);

/* Combining Instantiated class 'T' with Counter class to invoke same methods for counting: */
template<typename T>
struct counted:T, instance_counter<T>{
    using T::T;//inheriting methods [C++11 Construct]
	//Note: this technique provides the same interface for the class that is instantiated
};

#endif

#endif
