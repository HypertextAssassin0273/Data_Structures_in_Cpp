/* INCOMPLETE */
#include<iostream>
#if __cplusplus < 201103L
#include<cstdlib>
#endif
using namespace std;

const int maxLevel=4;

template<class T>
class node{
public:
	T key;
	node **next;
};

template<class T>
class Skip_List{
	typedef node<T> *nodePtr;
	nodePtr root[maxLevel];
	int powers[maxLevel];
public:
	Skip_List();
	bool is_empty()const;
	void choose_powers();
	int choose_level();
	T* search_list(const T&);
	void insert(const T&);	
};

template<class T>
Skip_List<T>::Skip_List(){
	for (int i=0;i<maxLevel;++i)
		root[i]=0;
}

template<class T>
bool Skip_List<T>::is_empty()const{
	return root[0]==0;
}

template<class T>
void Skip_List<T>::choose_powers(){
	powers[maxLevel-1]=(2<<(maxLevel-1))-1;//2^maxLevel-1
	for (int i=maxLevel-2,j=0;i>=0;--i,++j)
		powers[i]=powers[i+1]-(2<<j);//2^(j+1)
}

template<class T>
int Skip_List<T>::choose_level(){
	int i,r=rand()%powers[maxLevel-1]+1;
	for (i=1;i<maxLevel;++i)
	if (r<powers[i])
		return i-1;//return a level < the highest level;
	return i-1;//return the highest level;
}

template<class T>
T* Skip_List<T>::search_list(const T& key){
	if (is_empty())
		return 0;
	nodePtr prev, curr;
	int lvl;//find the highest non-null
	for (lvl=maxLevel-1;lvl>=0&&!root[lvl];--lvl);//level
	prev=curr=root[lvl];
	while(true){
		if (key==curr->key)//success if equal
			return &curr->key;
		else if(key<curr->key){//if smaller, go down
			if(lvl==0)//if possible,
				return 0;
			else if(curr==root[lvl])//by one level
				curr=root[--lvl];//starting from the
			else 
				curr=*(prev->next+--lvl);// predecessor
			}//which can be the root
			else{//if greater,
				prev=curr;//go to the next
				if (*(curr->next + lvl) != 0)//non-null node
					curr = *(curr->next + lvl);//on the same level
				else {//or to a list on a lower level
					for (--lvl;lvl>=0&&*(curr->next+lvl)==0;--lvl);
						if(lvl>=0)
							curr=*(curr->next+lvl);
						else
							return 0;
				}
			}
	}
}

template<class T>
void Skip_List<T>::insert(const T& key){
	nodePtr curr[maxLevel],prev[maxLevel],newNode;
	int lvl,i;
	curr[maxLevel-1]=root[maxLevel-1];
	prev[maxLevel-1]=0;
	for (lvl=maxLevel-1;lvl>=0;--lvl){
		while (curr[lvl] && curr[lvl]->key<key){//go to the next if smaller
			prev[lvl]=curr[lvl];
			curr[lvl]=*(curr[lvl]->next+lvl);
		}
		if (curr[lvl]&&curr[lvl]->key==key)//don’t include duplicates
			return;
		if (lvl>0)//go one level down
			if (prev[lvl]==0){//if not the lowest level use a link either from the root
				curr[lvl-1]=root[lvl-1];
				prev[lvl-1]=0;
			}
			else{//or from the predecessor
				curr[lvl-1]=*(prev[lvl]->next+lvl-1);
				prev[lvl-1]=prev[lvl];
			}
	}
	lvl=choose_level();//generate randomly level for newNode
	newNode=new node<T>;
	newNode->next=new nodePtr[sizeof(nodePtr)*(lvl+1)];
	newNode->key=key;
	for(i=0;i<=lvl;i++){//initialize next fields of
		*(newNode->next+i)=curr[i];//newNode and reset to newNode
		if (prev[i]==0)//either fields of the root
			root[i]=newNode;
		else//or next fields of newNode’s predecessors
			*(prev[i]->next+i)=newNode;
	}
}

int main(){
//	Skip_List<int> list;
	
	return 0;
}
