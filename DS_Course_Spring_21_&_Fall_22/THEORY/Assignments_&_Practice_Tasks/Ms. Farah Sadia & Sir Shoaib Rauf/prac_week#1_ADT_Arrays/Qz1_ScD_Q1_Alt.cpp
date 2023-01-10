#include<iostream>
#include<vector>

//using std::vector for Final_Array, since we can't assume its actual size
typedef std::vector<int> int_vec;

int_vec add_split_sum_of_two_arrays(int* Arr1,int* Arr2, int size1, int size2, const int max_digit_size=2){
	int_vec Arr3;//Final_Array
	Arr3.reserve((size1+size2)*max_digit_size);//set to handle max possible split for 2 digits
	
	int i=0, N=(size1>=size2?size2:size1), sum, rem;
	
	while(i<N){
		sum=Arr1[i]+Arr2[i++];
		rem=sum%10;//store remainder of sum for pushing as last digit
		while(sum>10)//store divisors of sum until only 1 digit is left
			Arr3.push_back(sum/=10);
		Arr3.push_back(rem);
	}
	
	//for remaining elements of either Arr1 or Arr2, do the same operations as above:
	if(size1>=size2)
		while(i<size1){
			sum=Arr1[i++];
			rem=sum%10;
			while(sum>10)
				Arr3.push_back(sum/=10);
			Arr3.push_back(rem);
		}
	else
		while(i<size2){
			sum=Arr2[i++];
			rem=sum%10;
			while(sum>10)
				Arr3.push_back(sum/=10);
			Arr3.push_back(rem);
		}
	
#if __cplusplus >= 201103L
	Arr3.shrink_to_fit();//sets capacity = size, i.e. deallocates unused memory
#endif
	return Arr3;//returns as rvalue (because of R.V.O)
}

int main(){
	int Arr1[]={23,5,2,7},
		Arr2[]={4,67,2};
	
	int_vec Arr3=add_split_sum_of_two_arrays(Arr1, Arr2, 4, 3);//move (shallow copy) constructed
	
	for(int i=0,N=Arr3.size();i<N;++i)
		std::cout<<Arr3[i]<<' ';
	
	return 0;
}
