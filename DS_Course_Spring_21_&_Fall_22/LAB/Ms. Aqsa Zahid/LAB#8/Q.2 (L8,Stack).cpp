#include"String.hpp"
#include"SLL.hpp"

bool check(const String& str,bool){
	String stack;//i.e. String can also be used as efficient stack in Ascending/FILO order
	stack.reserve(8);
	//i.e. reserving possible space in order to avoid extra constructions/destructions
	try{
		for(int i=0;i<str.size();++i){
			if(str[i]=='{'||str[i]=='('||str[i]=='[')
				stack.push_back(str[i]);
			else if(str[i]=='}'||str[i]==')'||str[i]==']'){
				char var=stack.back();
				stack.pop_back();
				if((var!='{'&&str[i]=='}')||(var!='('&&str[i]==')')||(var!='['&&str[i]==']'))
					return false;
			}
		}
	}
	catch(...){
		return false;
	}
	return stack.size()?false:true;	
}

bool check(const String& str){//i.e. using singly linked-list
	SLL<char> stack;//i.e. stack in Descending/LIFO order
	try{
		for(int i=0;i<str.size();++i){
			if(str[i]=='{'||str[i]=='('||str[i]=='[')
				stack.push_front(str[i]);
			else if(str[i]=='}'||str[i]==')'||str[i]==']'){
				char var=stack.front();
				stack.pop_front();
				if((var!='{'&&str[i]=='}')||(var!='('&&str[i]==')')||(var!='['&&str[i]==']'))
					return false;
			}
		}
	}
	catch(...){
		return false;
	}
	return stack.size()?false:true;	
}

int main(){
	String expression="{25 + (3 - 6) * 8}";//i.e. test-case 1
//	String expression="7 + 8 * 2";//i.e. test-case 2
//	String expression="5 + {(13 + 7) / 8 - 2 * 9";//i.e. test-case 3
	
	cout<<"Expression:\n"
		<<expression
		<<"\n\nContains matching grouping symbols: "<<endl
		<<std::boolalpha<<check(expression);
//		<<std::boolalpha<<check(expression,1);
	return 0;
}
