#include "dynamic_array.hpp"

using std::cout;

int main(){
	DA<DA<int>> arr{//2D jagged dynamic_array initialization
		DA<int>{366, 333, 400, 300, 266},
		DA<int>{333, 300, 366, 300},
		DA<int>{400, 366, 266},
		DA<int>{266, 233, 400},
		DA<int>{333, 366, 400, 300, 333}
	};
	
	std::string AN[]{"British Airways", "Eastern Airways", "Easy Jet", "FlyBe", "Ryanair"}; //airline names
	
	cout<<"Airline's Covered Distances (of each City):\n";
	for(short i=0;i<arr.size();++i)
		cout<<AN[i]<<": "<<arr[i]<<'\n';
	
	cout<<"\nAirline's' Cumulative Distance:\n";
	int cd; //cummalative distance
	for(char i=0,j;i<arr.size();++i){
		for(j=0,cd=0;j<arr[i].size();++j)
			cd+=arr[i][j];
		cout<<AN[i]<<": "<<cd<<'\n';
	}
	return 0;
}
