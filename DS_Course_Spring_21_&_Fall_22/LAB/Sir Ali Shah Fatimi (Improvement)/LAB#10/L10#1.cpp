#include "Huffman.hpp"
using namespace std;

int main(){
	char data[]="shahzaib";//{'s','h','a','h','z','a','i','b'}
	int freq[]={3, 9, 11, 12, 13, 16, 45},
		size=sizeof(data)/sizeof(data[0])-1;
	
	HuffmanCoding(data, freq, size);
    
    return 0;
}
