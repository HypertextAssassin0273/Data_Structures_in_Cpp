#include <time.h>
#include "../Utilities/Date.hpp"
#include "../Algorithms/Sorts.hpp"

using std::cout;

int main(){//sorts array of random dates
	srand(time(0));
	
	Date arr[6];
	
	for(int i=0;i<5;++i)
		arr[i]=Date(rand()%30+1, rand()%12+1, rand()%(2030-1990+1)+1990);
	
	arr[5]=arr[4];
	arr[4].day=31;
	
	for(auto& it:arr)
		cout<<it<<'\n';
	cout<<"\n\n";
	
	sort::bubble(arr, 6);//ascending
	
	for(auto& it:arr)
		cout<<it<<'\n';
	cout<<"\n\n";
	
	sort::bubble(arr, 6, lesser);//descending
	
	for(auto& it:arr)
		cout<<it<<'\n';
	
	return 0;
}
