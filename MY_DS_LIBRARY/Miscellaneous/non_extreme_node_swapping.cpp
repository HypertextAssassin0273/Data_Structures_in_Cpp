#include<iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *nxt;
		Node *prv;
		
		Node(){
			data = 0;
			nxt = prv = NULL;
		}
};

class DLL{
	Node *hd, *tl;	
	
	public:
		void addnode_hd(const int val){
			Node *newnode = new Node;
			newnode->data = val;
			if(hd == NULL){
				hd = tl = newnode;
			}else{
				hd->prv = newnode;
				newnode->nxt = hd;
				hd = newnode;
			}
		}
		
		void const disp(){
			Node *tmp = new Node;
			for(tmp = hd; tmp!=NULL; tmp = tmp->nxt)
				cout<< tmp->data<< " ";
			cout<< endl;
		}
		
		bool swap_adjacent(const int val){
			int fg = false;
			if( (hd->data != val) ){
				Node *tmp, *tmp2, *tmp3;
				for(tmp = hd; tmp!=NULL; tmp = tmp->nxt){
					if(tmp->data == val){
						Node *tmp3 = tmp;
						Node *tmp2 = tmp->nxt;
						tmp->prv->nxt = tmp2;
						tmp2->prv = tmp->prv;
						Node *tmp4 = tmp2->nxt;
						tmp4->prv = tmp;
						tmp2->nxt->prv = tmp;
						tmp->nxt = tmp2->nxt;
						tmp->prv = tmp2;
						tmp2->nxt = tmp;
						fg = true;
					}
				}
			}
			return fg;				//in-case of extreme nodes
		}
};

int main(){
	DLL List;
	
	List.addnode_hd(5);
	List.addnode_hd(6);
	List.addnode_hd(7);
	List.addnode_hd(8);
	List.addnode_hd(9);
	List.addnode_hd(11);
	List.addnode_hd(12);
	List.addnode_hd(31);		
	
	List.disp();
	
	bool chk = List.swap_adjacent(11);
	if(chk == false)
		cout<< endl<< "FAILED TO SWAP THE NODES!"<< endl;
	else
		List.disp();

	cout<< endl<< endl;
	system("PAUSE");
	return 0;
}
