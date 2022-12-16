#include <iostream>

using std::cout;
using std::cin;

class Matrix2DArray{
	int height, width;
	int** data;
public:	
    Matrix2DArray(int height, int width)noexcept://ctor
		height(height), width(width), data(new int*[height]){
			for (int i=0;i<height;++i)
				data[i]=new int[width]{0};
		}
	
	void input(){
		cout<<"enter values:\n";
		for(int i=0,j;i<height;++i)
			for(j=0;j<width;++j)
				cin>>data[i][j];
	}
	
	void display()const{
		cout<<"\nmatrix:\n";
		for(int i=0,j;i<height;++i){
			for(j=0;j<width;++j)
				cout<<data[i][j]<<' ';
			cout<<'\n';
		}
	}
	
    bool check_indentity_matrix()const{
    	if (height!=width) return false;
    	
		for(int i=0,j;i<height;++i)
			for(j=0;j<width;++j){
				if(i == j){// diagonal
					if(data[i][j] == 1)
						continue;
					return false;
				}
				if (data[i][j])
					return false;
			}
		return true;
	}
	
	~Matrix2DArray(){//dtor
		for(int i=0;i<height;++i)
        	delete[] data[i]; //deleting sub/1d arrays
		delete[] data; //deleting main/2d (pointer) array
	}
};

int main(){
	Matrix2DArray m1(3, 3);
	
	m1.input();
	m1.display();
	
	cout<<"\nabove matrix is"
		<<(m1.check_indentity_matrix()?"":" not")
		<<" an indentity matrix!";
	
	return 0;
}
