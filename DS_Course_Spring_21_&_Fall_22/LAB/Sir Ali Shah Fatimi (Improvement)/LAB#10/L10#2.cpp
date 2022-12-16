#include "Huffman.hpp"
using namespace std;

template<size_t n>
void Huff_Compare(HN* root, const int (&arr)[n]){
	for(int i=0;i<n;++i){
		HN* current = root;
		while(current->left&&current->right)
			current=(arr[i++]?current->right:current->left);
		cout<<current->data;
	}
}

int main(){
    char data[]="shahzaib";//{'s','h','a','h','z','a','i','b'}
    int freq[]={ 5, 9, 11,12,13,16, 45 },
    	size=sizeof(data)/sizeof(data[0])-1;
    
	HN* root=HuffmanCoding(data, freq, size);
    
    cout<<"Decoding of 1010: ";
	Huff_Compare(root, {1,0,1,0});
    
    return 0;
}
