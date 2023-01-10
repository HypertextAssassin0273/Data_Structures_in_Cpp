#include<iostream>

struct d_arr_int{//for temporarily holding dynamic array of integers
	int size,*data;//public member attributes
	
	d_arr_int(int* d_ptr=NULL, int s=0)://default & parameterized ctor
		data(d_ptr),size(s){}
	
};//alternative: std::vector<int>

d_arr_int add_split_sum_of_two_arrays(int* Arr1,int* Arr2, int size1, int size2, const int max_digit_size=2){
	const int capacity3=(size1+size2)*max_digit_size;
	/*Note: capacity of Arr3 is set to handle max possible split for 2 digits, 
			since we can't assume actual size.
	*/
	int	size3=0,//no. of elements present in Final_Array
		*Arr3=new int[capacity3];//Final_Array
	
	int i=0, N=(size1>=size2?size2:size1), sum, rem;
	while(i<N){
		sum=Arr1[i]+Arr2[i++];
		rem=sum%10;//store remainder of sum for pushing as last digit
		while(sum>10)//store divisors of sum until only 1 digit is left
			Arr3[size3++]=sum/=10;
		Arr3[size3++]=rem;
	}
	
	//for remaining elements of either Arr1 or Arr2, do the same operations as above:
	if(size1>=size2)
		while(i<size1){
			sum=Arr1[i++];
			rem=sum%10;
			while(sum>10)
				Arr3[size3++]=sum/=10;
			Arr3[size3++]=rem;
		}
	else
		while(i<size2){
			sum=Arr2[i++];
			rem=sum%10;
			while(sum>10)
				Arr3[size3++]=sum/=10;
			Arr3[size3++]=rem;
		}
	
	//resize Final_Array (similar to: std::vector::shrink_to_fit):
	if(size3<capacity3){//sets capacity = size, i.e. deallocates unused memory blocks
		int *new_arr=new int[size3];
		for(i=0;i<size3;++i)//copy values
			new_arr[i]=Arr3[i];
		delete[] Arr3;//delete previous data
		Arr3=new_arr;//set Arr3 to new data
	}
	
	return d_arr_int(Arr3, size3);//returns rvalue struct
}

int main(){
	int *Arr1=new int[4]{23,5,2,7},
		*Arr2=new int[3]{4,67,2};
	
	d_arr_int Arr3=add_split_sum_of_two_arrays(Arr1, Arr2, 4, 3);//move (shallow copy) constructed
	
	delete[] Arr1; delete[] Arr2;//free (unused) memory
	
	for(int i=0,N=Arr3.size;i<N;++i)
		std::cout<<Arr3.data[i]<<' ';
	
	delete[] Arr3.data;//free memory
	
	return 0;
}
