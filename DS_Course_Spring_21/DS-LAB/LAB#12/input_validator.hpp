#if __cplusplus >= 201103L

#ifndef _GLIBCXX_IOSTREAM 
#include<iostream>
using namespace std;
#endif


inline void Print_Multiple_Args(){}//i.e. base case condition func
	
template<typename T,typename... Types>
void Print_Multiple_Args(const T& Arg1,const Types&... Args){//Note: Parameter-Pack (...)-> takes multiple args
	cout<<Arg1;
	Print_Multiple_Args(Args...);
	/*Note: Func will recursively call variadic template based func until it recieves 
			    zero args & then, it calls base func (using overloading concept) */
}

template<typename D,typename L1,typename L2,typename T,typename... Types>
void Validate_Input(D& Dest,const L1& Lower_Limit,const L2& Upper_Limit,bool clear_flag,const T& Arg1,const Types&... Arg2){//Note: Dest should only be any integer type
	while(true){
		if(clear_flag)
			system("cls");
		Print_Multiple_Args(Arg1,Arg2...);//i.e. displays complete string
		cin>>Dest;
		if(Dest>=Lower_Limit&&Dest<=Upper_Limit)
			break;
		cout<<"\a";//i.e. system sound
		cin.clear();
		fflush(stdin);
		//Note: Here, we have to use both cin.clear() & fflush(stdin) to clear buffer
	}
}
#endif
