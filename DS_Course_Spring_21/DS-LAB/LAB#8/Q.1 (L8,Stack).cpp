#include"SLL.hpp"
#include"DLL.hpp"
#include"Vector.hpp"
#include<math.h>

template<typename T>
void store_prime_factors(int n,T& stack,void (*operation)(T&,int)){//i.e. passing func ptr
	while(!(n%2)){
        operation(stack,2);
        n=n/2;
    }
    for (int i=3;i<=sqrt(n);i=i+2){
        while (!(n%i)){
        	operation(stack,i);
            n=n/i;
        }
    }
    if (n>2)
   		operation(stack,n);
}
//i.e. this method removes code duplication
template<typename T>
void push_front(T& stack,int val){ stack.push_front(val); }
template<typename T>
void push_back(T& stack,int val){ stack.push_back(val); }

int main(){
	const int n=60;
	cout<<"Prime factors of "<<n<<":-"<<endl;
	{//i.e. SLL is efficient when traversing or creating stack only in descending order (FILO)
		SLL<int> stack;
		store_prime_factors(n,stack,push_front);
		cout<<"\nSingly Linked-List Stack (Descending Order):"<<endl;
		stack.traverse();
	}//i.e. destroying stack obj
	SLL<int>::clear_gc();//i.e. clearing all nodes of SLL<int> type
	
	{/*i.e. DLL is efficient when traversing or creating stack in both
	    	ascending (FILO) & descending order (LIFO) */
		DLL<int> stack;
		store_prime_factors(n,stack,push_back);
		cout<<"\nDoubly Linked-List Stack (Ascending Order):"<<endl;
		stack.traverse_forward();
		cout<<"reverse:"<<endl;
		stack.traverse_backward();
	}
	{
		DLL<int> stack;
		store_prime_factors(n,stack,push_front);
		cout<<"\nDoubly Linked-List Stack (Descending Order):"<<endl;
		stack.traverse_forward();
		cout<<"reverse:"<<endl;
		stack.traverse_backward();
	}
	DLL<int>::clear_gc();//i.e. clearing all nodes of DLL<int> type
	
	//i.e. Vector is efficient when traversing or creating stack only in ascending order (LILO)
	Vector<int> stack;
	stack.reserve(8);//i.e. process will get more efficient if we reserve the memory before pushes
	store_prime_factors(n,stack,push_back);
	cout<<"\nVector Stack (Ascending Order):"<<endl;
#if __cplusplus >= 201103L
	for(const auto& it:stack)
		cout<<it<<" ";
	cout<<"\nreverse:"<<endl;
	for(const auto& it:stack.reverse_it())
		cout<<it<<" ";
#else
	for(Vector<int>::iterator it=stack.begin();it!=stack.end();++it)
		cout<<*it<<" ";
	cout<<"\nreverse:"<<endl;
	for(Vector<int>::r_iterator it=stack.rbegin();it!=stack.rend();++it)
		cout<<*it<<" ";
	/* Alternate */
//	for(int i=0;i<stack.size();++i)
//		cout<<stack[i]<<" ";
//	cout<<"\nreverse:"<<endl;
//	for(int i=stack.size()-1;i>=0;--i)
//		cout<<stack[i]<<" ";
#endif
	return 0;
}
