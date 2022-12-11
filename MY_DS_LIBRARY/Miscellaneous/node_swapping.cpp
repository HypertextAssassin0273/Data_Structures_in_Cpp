#include<iostream>
using namespace std;

class Node{
	public:
		int data;
		Node *nxt;	
};

class S_LinkedList{
	Node *hd, *tl;
	int size;
	
	public:
		S_LinkedList(){
			hd = NULL;
			tl = NULL;
			size = 0;
		}	
		
		void addnode_end(const int val){
			Node *NODE = new Node;
			NODE->data = val;
			NODE->nxt = NULL;
			if(hd == NULL){
				hd = NODE;
				tl = hd;
			}else{
				tl->nxt = NODE;
				tl = NODE;
			}
		}
		
		void set_size(){
			Node *tmp;
			for(tmp = hd; tmp!=NULL; tmp = tmp->nxt)
				size+= 1;
				
				//extra for swap
			for(tmp = hd; tmp->nxt != tl; tmp = tmp->nxt);
			swap(hd, hd->nxt->nxt);	
				//extra ended
		}
		
		void swap(Node *left, Node *right){
			Node *tmp;
			if( (left == hd) && (right == tl)){					//to swap head and tail
				Node *tmp2;
				for(tmp = hd; tmp!=NULL; tmp = tmp->nxt){
					if(tmp->nxt == tl)
						break;
				}
				tmp2 = hd;
				tmp->nxt = hd;
				hd = tl;
				tl->nxt = tmp2->nxt;
				tl = tmp->nxt;
				tl->nxt = NULL;
				return;
			}else if( (left == hd) && (right == hd->nxt) ){		//to swap head and its adjacent
				tmp = right;
				hd->nxt = tmp->nxt;
				tmp->nxt = hd;
				hd = tmp;
				return;			
			}else if( (left->nxt == tl) && (right == tl) ){		//to swap adjacent and tail
				for(tmp = hd; tmp->nxt!= left; tmp = tmp->nxt);
				tmp->nxt = right;
				right->nxt = left;
				tl = left;
				tl->nxt = NULL;
				return;
			}else if( (left->nxt!= right) && (left!=hd) && (right!=tl)){	//to swap anyone by anyone except head and tail || adjacents
				Node *tmp3, *tmp4;
				Node *tmp2 = right->nxt;
				for(tmp3 = hd; tmp3->nxt!= left; tmp3 = tmp3->nxt);
				tmp = left->nxt;
				for(tmp4 = hd; tmp4->nxt!=right; tmp4 = tmp4->nxt);
				tmp4->nxt = left;
				left->nxt = tmp2;
				right->nxt = tmp;
				tmp3->nxt = right;
				return;
			}else if( (left == hd) && (right!= tl && right!=hd->nxt) ){		//to swap head by anyone, but not adjacent || tail
				Node *tmp2 = left->nxt, *tmp3 = right->nxt;
				for(tmp = hd; tmp->nxt!=right; tmp = tmp->nxt);
				right->nxt = tmp2;
				tmp->nxt = hd;
				hd->nxt = tmp3;
				hd = right;
				return;
			}else if( (right == tl) && (left->nxt!= right && left!=hd) ){	//to swap tail by anyone, but not adjacent || head
				for(tmp = hd; tmp->nxt!=tl; tmp = tmp->nxt);
				Node *tmp2 = left->nxt, *tmp3;
				for(tmp3 = hd; tmp3->nxt!=left; tmp3 = tmp3->nxt);
				tmp3->nxt = right;
				left->nxt = NULL;
				right->nxt = tmp2;
				tmp->nxt = left;
				tl = left;
				return;
			}else if( (left!= hd && right!=tl) && (left->nxt == right) ){	//to swap adjacents other than head and tail
				for(tmp = hd; tmp->nxt!= left; tmp = tmp->nxt);
				Node *tmp2 = right->nxt;
				left->nxt = tmp2;
				tmp->nxt = right;
				right->nxt = left;
				return;
			}
		}
		
		void disp(){
			Node *tmp;
			cout<< endl;
			for(tmp = hd; tmp!= NULL; tmp = tmp->nxt)
				cout<< tmp->data << " ";
			cout<< endl;	
		}
};

//scope of main:
int main(){
	S_LinkedList List;
	List.addnode_end(10);
	List.addnode_end(102);
	List.addnode_end(39);
	List.addnode_end(101);
	List.addnode_end(3);
	List.addnode_end(2);
	List.addnode_end(300);
	List.disp();
	List.set_size();
	
	List.disp();
	cout<< endl<< endl<< endl;
	system("PAUSE"); 
	return 0;
}
