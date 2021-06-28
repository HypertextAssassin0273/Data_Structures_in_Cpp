#include<iostream>
using namespace std;

class find_consecutive_trees{
	int size,count,max_count;
	char **field;
	
	find_consecutive_trees():count(0),max_count(0){//i.e. ctor
		cout<<"Input:"<<endl;
		cin>>size;//i.e. taking size of field from user
		
		field=new char*[size];//i.e. allocation of field
		for(int i=0;i<size;++i)
			field[i]=new char[size];
		
		for(int i=0;i<size;++i)//i.e. user input for field
    		for(int j=0;j<size;++j)
    			cin>>field[i][j];
	}
	
	~find_consecutive_trees(){//i.e. dtor
		for(int i=0;i<size;++i)//i.e. deallocation of field
			delete field[i];
		delete []field;
	}
	
	//i.e. checking place is inside the forest & have tree 'T'
	bool is_valid_place(int x,int y)const{
		//i.e. 1-> T, 0->W (assuming bool logic as char)
   		return (x>=0&&x<size&&y>=0&&y<size&&field[x][y]=='T')?true:false;
	}

	bool find_path_for_tree(int x,int y){
		++count;
		field[x][y]='W';//i.e. blocking previous path to prevent recounting of previously counted trees
		
		if(is_valid_place(x+1,y)&&x<size-1)
			if (find_path_for_tree(x+1,y))//i.e. go downwards
   	    		return true;
   	    	
		if(is_valid_place(x,y+1)&&y<size-1)
			if (find_path_for_tree(x,y+1))//i.e. go rightwards
        		return true;
        		
		if(is_valid_place(x-1,y)&&x>0)
			if (find_path_for_tree(x-1,y))//i.e. go upwards
				return true;
				
		if(is_valid_place(x,y-1)&&y>0)
			if (find_path_for_tree(x,y-1))//i.e. go leftwards
				return true;
      	
      	return false;//i.e. if all are closed,then there is no path
	}
public:
	static void solution(){
		find_consecutive_trees fct;
    
    	for(int i=0;i<fct.size;++i)//i.e. finding consecutive trees in forest (array)
    		for(int j=0;j<fct.size;++j)
    	    	if(fct.is_valid_place(i,j)){
    	    		fct.find_path_for_tree(i,j);
    	    		if(fct.max_count<fct.count)
    	    			fct.max_count=fct.count;
					fct.count=0;//i.e. reseting counter for next path
				}
	
    	cout<<"\nOutput:\n"<<fct.max_count<<endl;
	}
};

int main(){
	find_consecutive_trees::solution();
	return 0;
}
