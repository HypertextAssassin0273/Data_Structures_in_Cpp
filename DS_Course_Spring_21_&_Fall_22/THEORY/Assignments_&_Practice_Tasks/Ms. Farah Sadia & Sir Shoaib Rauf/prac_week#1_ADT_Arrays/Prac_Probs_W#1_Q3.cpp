#include<iostream>

class bool_2d_array{
	int rows, cols;
	bool** data;
	
public:
	template<size_t N, size_t M>
	bool_2d_array(const int (&arr)[N][M])://holds temporary 2d array of integers of N*M size
		rows(N),cols(M),data(new bool*[N]){
		for(int i=0,j;i<N;++i){
			data[i]=new bool[M];
			for(j=0;j<M;++j)
				data[i][j]=arr[i][j];
		}
	}
	
	bool areFriends(int i, int j)const{ return data[i][j]; }
	
	~bool_2d_array(){
		for(int i=0,j;i<rows;++i)
			delete []data[i];
		delete []data;
	}
	
	friend std::ostream& operator<<(std::ostream& out,const bool_2d_array& self){//overloaded cout method
		for(int i=0,j;i<self.rows;++i){
			for(j=0;j<self.cols;++j)
				std::cout<<self.data[i][j]<<' ';
			std::cout<<'\n';
		}
		return out;
	}
};

int main(){
	bool_2d_array people({//creates 5x5 bool 2d array
		{0,1,0,1,1},
		{1,0,1,0,1},
		{0,1,0,0,0},
		{1,0,0,0,1},
		{1,1,0,1,0}
	});
	
	std::cout<<people
			 <<"\n1 & 0 are friends: "
			 <<(people.areFriends(1, 0)?"true":"false");
	
	return 0;
}
