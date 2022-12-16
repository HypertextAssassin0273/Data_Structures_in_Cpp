#include "Hashing.hpp"
using namespace std;

int main(){
	Hash_Map<int> ob;
	
	for(int i=15;i<25;++i)
		ob.insert(i+8, i);
	
	ob.traverse();
	cout<<"\nKey was placed on "<<ob.search(30)<<'\n';
	
	ob.remove(23);
	ob.traverse();
	
	return 0;
}
