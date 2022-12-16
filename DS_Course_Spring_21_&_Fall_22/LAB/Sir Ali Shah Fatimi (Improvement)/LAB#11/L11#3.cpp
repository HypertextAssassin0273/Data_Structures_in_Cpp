#include "Hashing.hpp"
using namespace std;

int main(){
    Hash_Map<string> ob;
    int s;
    string value;
    for(int i=0;i<5;++i){
        cout<<"Enter ID: ";
        cin>>s;
        cout<<"Enter number: ";
        cin>>value;
        ob.insert(s, value);
    }
    
	cout<<(ob.isEmpty()?"empty\n":"Not Empty\n")
    	<<"Size of contact bookey: "<<ob.get_count()
    	<<"\nEnter the student ID for search : ";
    cin>>s;
    
    cout<<"Pair found at index : "<<ob.search(s)
    	<<"\nEnter the pair to be deleted : ";
    cin>>s;
    
    ob.remove(s);
    
	cout<<"Size of contact book: "<<ob.get_count()<<'\n';
    ob.traverse();
    
    return 0;
}
