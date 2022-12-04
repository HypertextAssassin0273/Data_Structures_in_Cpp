#include "Sorts.hpp"

struct date{
	size_t day, month, year;
	
	date(size_t day=0,size_t month=0,size_t year=0)://default & parameterized ctor
		day(day), month(month), year(year){}
	
	/* comparators (year based comparison only) */
	bool operator>(const date& other)const{ return other.year<year; }
	bool operator<(const date& other)const{ return other.year>year; }
	
	/* overloaded 'cin/cout' methods */
	friend std::ostream& operator<<(std::ostream& out,const date& self){
			out<<self.day<<' '<<self.month<<' '<<self.year<<'\n';
		return out;
	}
	friend std::istream& operator>>(std::istream& in,date& self){
			in>>self.day>>self.month>>self.year;
		return in;
	}
};

int main(){
	const int N=5;//array size
//	date arr[N];//array of N date objects
	
//	for(size_t i=0;i<N;++i)//keyboard input
//		std::cin>>arr[i];
	
	date arr[]={//hard-code approach for testing
		date(1, 12, 2020),
		date(11, 11, 2011),
		date(7, 3, 2001),
		date(3, 4, 1999),
		date(18, 7, 2011)
	};
	
	sort::selection(arr, N);//ascending order
//	sort::selection(arr, arr+N);//iterator version
	
//	sort::selection(arr, N, lesser);//descending order
//	sort::selection(arr, arr+N, lesser);
	
	for(size_t i=0;i<N;++i)
		std::cout<<arr[i];
	
	return 0;
}
