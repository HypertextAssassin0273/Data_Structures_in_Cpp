#include "dynamic_array.hpp"

using std::cout;

//method#2 (extra): using (dynamic/heap-based) 2d jagged arrays

//=> memory & performance efficient approach: only stores 'less dense' indexes of matrix
//=> best use-case: when having large set of data less densely populated inside matrix

typedef dynamic_array<int> da_int;//redefining as more simplified name

void check_common_course_mates(const DA<da_int>& arr, int s1, int s2){
	cout<<"\nstudent '"<<s1<<"' & '"<<s2<<"' have following common course/courses: ";
	bool flag=false;
	for(int i=0,j=0;i<arr[s1].size() && j<arr[s2].size();){
		if (arr[s1][i]==arr[s2][j]){
			cout<<arr[s1][i]<<", ";
			++i; ++j;
			flag=true;
		}
		else
			(arr[s1][i]<arr[s2][j]) ? ++i : ++j;
	}
	cout<<(flag?"\n":"none\n");
}

int main(){
/* logical 2d array matrix representation of given problem:
   [here: 1 -> true, 0 -> false]
	
	i/j	 0, 1, 2, 3, 4	
	0	{0, 1, 0, 1, 1}
	1	{1, 0, 1, 0, 1}
	2	{0, 1, 0, 0, 0}
	3	{1, 0, 0, 0, 1}
	4	{1, 1, 0, 1, 0}
*/
	
	DA<da_int> arr{//2D jagged dynamic_array initialization as 'sparse matrix'
		da_int{1, 3, 4},
		da_int{0, 2, 4},
		da_int{1},
		da_int{0, 4},
		da_int{0, 1, 3}
	};//assuming indexes will taken in sorted order
	
	for(short i=0;i<arr.size();++i)
		cout<<i<<": "<<arr[i]<<'\n';
	
//	check_common_course_mates(arr, 1, 2); //case-1: no common courses
//	check_common_course_mates(arr, 1, 0); //case-2: one common course only
	check_common_course_mates(arr, 0, 4); //case-3: multiple common courses
	
	return 0;
}
