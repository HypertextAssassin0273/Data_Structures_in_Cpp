#include<iostream>
#include<cmath>
using namespace std;
class quadratic_eqn{
	int a,b,c;
public:
	quadratic_eqn(int a,int b,int c):a(a),b(b),c(c){}
	void find_roots(){
    	if (!a){
        	cout << "Invalid";
        	return;
    	}
  		int d=b*b-4*a*c;
    	double sqrt_val=sqrt(abs(d)); 
    	if (d>0){
    	    cout<<"Roots are real and different \n"
    	    	<<(double)(-b+sqrt_val)/(2*a)<<"\n"
    	        <<(double)(-b-sqrt_val)/(2*a);
    	}
    	else if(!d){
      		cout<<"Roots are real and same \n"
        		<<-(double)b/(2*a);
    	}
    	else{
        	cout<<"Roots are complex "<<endl
        		<<-(double)b/(2*a)<<" + i"<<sqrt_val<<endl
            	<<-(double)b/(2*a)<<" - i"<<sqrt_val;
    	}
	}
};
int main(){
	quadratic_eqn obj1(1,-2,1),obj2(1,7,12),obj3(1,1,1);
	cout<<"Obj1:-"<<endl;
	obj1.find_roots();
	cout<<"\nObj2:-"<<endl;
	obj2.find_roots();
	cout<<"\nObj3:-"<<endl;
	obj3.find_roots();
	return 0;
}
