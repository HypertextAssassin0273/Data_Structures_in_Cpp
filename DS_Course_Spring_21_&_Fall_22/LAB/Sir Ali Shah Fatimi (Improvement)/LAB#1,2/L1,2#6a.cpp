#include "dynamic_array.hpp"

using std::cout;

int main(){
	DA<DA<double>> arr{//2D jagged dynamic_array initialization
		DA<double>{3.66, 3.33, 4.0, 3.0, 2.66},
		DA<double>{3.33, 3.0, 3.66, 3.0},
		DA<double>{4.0, 3.66, 2.66},
		DA<double>{2.66, 2.33, 4.0},
		DA<double>{3.33, 3.66, 4.0, 3.0, 3.33}
	};
	
	std::string SN[]{"Ali", "Hiba", "Asma", "Zain", "Faisal"}; //student names
	
	cout<<"Students' Course GPA's:\n";
	for(short i=0;i<arr.size();++i)
		cout<<SN[i]<<": "<<arr[i]<<'\n';
	
	cout<<"\nStudents' Overall SGPA:\n";
	constexpr char rch=3; //repective credit hour (given: each course has 3 credit_hrs) 
	//note: signed char -> 1byte -> range: -128 to 127
	
	float tgpa, //total GPA
		   tch; //total credit hours
	
	for(char i=0,j;i<arr.size();++i){
		for(j=0,tgpa=0;j<arr[i].size();++j)
			tgpa+=(arr[i][j]*rch); //total sum of product of: GPA & repective_credit_hour
		tch=arr[i].size()*rch;
		cout<<SN[i]<<": "<<tgpa/tch<<" ("<<tgpa<<'/'<<tch<<")\n";
	}
	return 0;
}
