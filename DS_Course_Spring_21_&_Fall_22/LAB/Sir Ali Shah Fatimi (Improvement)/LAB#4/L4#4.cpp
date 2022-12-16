#include "Sorts.hpp"

typedef unsigned int u_int;//4 bytes (0 to 4,294,967,295)

void find_max_no_of_buyable_toys(){
	/*Given (Input):
		arr[] => array of cost of toys
		 K	  => given amount for buying toys
		 N 	  => array size
	*/
	
	/* test_case 1: */
	u_int K=50, arr[]={1, 12, 5, 111, 200, 1000, 10, K+1};
	
	/* test_case 2: */
//	u_int K=100, arr[]={20, 30, 50, K+1};
	
	/* important_note:
		here, last position of array is set as 'sentinal value' in order to avoid
		array bound (range) check for optimized results in below while loop [at line: 26].
		hence, when 'i' reaches (N+1)th index, K will become less, hence loop will terminate
	*/
	
	u_int N=sizeof(arr)/4-1;//value set as N-1 to skip 'sentinal value'
	
	sort::bubble(arr, N);//optimized, ascending-order
	/* important_note:
		in order to find the maximum no. of buyable toys with K amount, we need to sort costs first
		note that, this will break the queue order, as costs will be rearranged in ascending order
	*/
	u_int i=0;		//iterator for counting maximum buyable toys
	while(K>=arr[i])//if given amount is sufficient for buying current toy
		K-=arr[i++];//then subtract its cost from given amount
	N=i;			//otherwise break the loop & set the count to N
	
	std::cout<<"maximum buyable toys: "<<N //Output
			 <<"\nbuyable toys (costs): "; //Explaination
	
	for(i=0;i<N;++i)
		std::cout<<arr[i]<<' ';
}

int main(){
	find_max_no_of_buyable_toys();
	
	return 0;
}
