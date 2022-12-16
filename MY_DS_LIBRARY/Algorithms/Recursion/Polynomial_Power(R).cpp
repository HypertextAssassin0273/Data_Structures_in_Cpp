#include<iostream>
using namespace std;

class Polynomial{
	int x;
	int powr;
	int res;
	
	public:
		Polynomial(){
			
		}
		
		Polynomial(const int x, const int powr){
			this->x = x;
			this->powr = powr;
			res = 0;
		}
		
		long poly_pow(int res, int pwr){
			if(pwr == 1){								//basecase
				return res;
			}
			if(pwr%2 == 0){
				return poly_pow(res*res, pwr/2);
			}else{
				return res*poly_pow(res*res, (pwr-1)/2);
			}
		}
};

int main(){
	int x = 2, powr = 5;
	Polynomial P(x, powr);
	cout<< endl<< "x^y = "<< x<< "^"<< powr<< " = "<< P.poly_pow(x, powr)<< endl<< endl;
	system("PAUSE");
	return 0;
}
