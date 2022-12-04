#include <iostream>

using std::cout;

class Fraction{
	int x,y;
public:	
	Fraction(int x=0, int y=0):
		x(x),y(y){}//ctor
	
	/* setter */
	int input(int x=0, int y=0){
		this->x=x;
		this->y=y;
	}
	
	/* getters */
	int numerator()const{ return x; }
	int denominator()const{ return y; }
	
	void show()const{ cout<<"hi i'm show!\n"; }
};

int main(){

/* Dynamic Allocation of Objects */
	Fraction * fp1, * fp2, * flist;
	fp1 = new Fraction; // uses default constructor
	fp2 = new Fraction(3,5); // uses constructor with two parameters
	flist = new Fraction[20]; // dynamic array of 20 Fraction objects
	// default constructor used on each

/* Notation: dot-operator vs. arrow-operator */
	//for dynamic objs
	fp1->show();
	(*fp1).show();
	//for automatic objs
	//fp1.show(); //gives error (since dynamic)


/* Deallocation with delete works the same as for basic types */
	delete fp1, fp2;
	delete [] flist;

	return 0;
}
