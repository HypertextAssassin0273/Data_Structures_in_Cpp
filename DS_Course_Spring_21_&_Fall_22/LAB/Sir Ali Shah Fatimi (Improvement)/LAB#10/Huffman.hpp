#ifndef HUFFMAN_GUARD
#define HUFFMAN_GUARD 1

#include <iostream>
#include <queue>

#define MAX_SIZE 100

template<typename T>
struct Huff_Node{
   	T data;
   	int freq;
    Huff_Node* left;
    Huff_Node* right;
    
    Huff_Node(const T& data, int freq):
    	data(data), freq (freq), left(nullptr), right(nullptr){}
};

typedef Huff_Node<char> HN;

struct comparator{
    bool operator()(HN* ob1,HN* ob2){
		return ob1->freq > ob2->freq;
	}
};

HN* generateTree(std::priority_queue<HN*, std::vector<HN*>, comparator> s){
    while(s.size()!=1){
    	HN* left=s.top(); s.pop();
        HN* right=s.top(); s.pop();
        HN* node=new HN('$', left->freq+right->freq);
        
		node->left=left;
        node->right=right;
        s.push(node);
    }
    return s.top();
}

void print(HN* root, int *arr, int top){
    if(root->left){
        arr[top]=0;
        print(root->left,arr, top + 1);
    }
    if(root->right){
        arr[top]=1;
        print(root->right, arr, top + 1);
    }
    if(!root->left&&!root->right){
        std::cout<<root->data<<' ';
        for(int i=0;i<top;i++)
            std::cout<<arr[i];
        std::cout<<'\n';
    }
}

HN* HuffmanCoding(char *data, int *freq, int size){
    std::priority_queue<HN*, std::vector<HN*>, comparator> pq;
    for(int i=0;i<size;i++)
        pq.push(new HN(data[i], freq[i]));
    
	HN* root=generateTree(pq);
    
	int arr[MAX_SIZE];
    print(root, arr, 0);
    
	return root;
}

#endif
