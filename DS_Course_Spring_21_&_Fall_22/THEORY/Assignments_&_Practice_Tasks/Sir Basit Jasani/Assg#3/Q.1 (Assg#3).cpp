#include"String.hpp"

struct COORD{
	double X,Y;
		
	COORD(const double& X,const double& Y):X(X),Y(Y){}
		
	bool operator<(const COORD& other)const{ return X==other.X?Y<other.Y:X<other.X; }
    bool operator>(const COORD& other)const{ return other<*this; }
};

class BST;

class city_record{
	String city;
	COORD coordinates;
public:
	city_record(const String& city={},const double& X=0,const double& Y=0):
		city(city),coordinates(X,Y){}
	
	bool less_compare(const city_record& other,bool flag)const{
		return flag?city<other.city:coordinates<other.coordinates;
	}
	bool greater_compare(const city_record& other,bool flag)const{
		return flag?city>other.city:coordinates>other.coordinates;
	}
	
	friend ostream& operator<<(ostream& out,const city_record& self){
			out<<self.city<<" ("<<self.coordinates.X<<','<<self.coordinates.Y<<")\n";
		return out;
	}
	
	friend class BST;
};

class BST{
	typedef unsigned int __uint32;
	
	struct node{
		city_record key;
		node *left,*right;
		
		node(const city_record& key=city_record())noexcept:
			key(key),left(nullptr),right(nullptr){}
	};
	
	node *root;
	__uint32 _size;
	
public:
	BST()noexcept:
		root(nullptr),_size(0){}
	
	BST(const BST&)noexcept=delete;
	BST& operator=(const BST&)noexcept=delete;
#if __cplusplus >= 201103L
 	BST(BST&& other)noexcept://i.e. move ctor (C++11 Construct)
  		root(other.root),_size(other._size){
		other.root=nullptr; other._size=0;
	}
	BST& operator=(BST&& other)noexcept{//i.e. move assignment func (C++11 Construct)
  		if(this==&other)
			return *this;
		clear();
  		root=other.root; _size=other._size;
  		other.root=nullptr; other._size=0;
  		return *this;
	}
#endif
	
	__uint32 total_records()const{ return _size; }
	
	void in_order_traversal()const{ in_order_traversal(root); }
	void pre_order_traversal()const{ pre_order_traversal(root); }
	void post_order_traversal()const{ post_order_traversal(root); }
	
	void insert(const city_record& key,bool order_flag){ root=insert(key,root,order_flag); }
//	void remove(const city_record& key,bool order_flag){ remove(key,root,order_flag); }
	city_record search_by_city(const String& key){ return search_by_city(key,root); }
	city_record search_by_coordinates(double X,double Y){ return search_by_coordinates(COORD(X,Y),root); }
	void clear(){ clear(root); root=nullptr; _size=0; }
	
	~BST(){ clear(root); root=nullptr; }
	
private:
	void pre_order_traversal(node *current)const{
		if(current){
			cout<<current->key;
			pre_order_traversal(current->left);
			pre_order_traversal(current->right);
		}
	}
	void in_order_traversal(node *current)const{
		if (current){
			in_order_traversal(current->left);
			cout<<current->key;
			in_order_traversal(current->right);
		}
	}
	void post_order_traversal(node *current)const{
		if(current){
			post_order_traversal(current->left);
			post_order_traversal(current->right);
			cout<<current->key;
		}
	}
	node* insert(const city_record& key,node* current,bool order_flag){
		if (!current){
			++_size;
			return new node(key);
		}
		if (key.less_compare(current->key,order_flag))
			current->left=insert(key,current->left,order_flag);
		else
			current->right=insert(key,current->right,order_flag);
		return current;
	}
//	node* min_value_node(node *current){//i.e. returns the inorder successor
//		while(current&&current->left)//i.e. finds the left-most leaf
//			current=current->left;
//		return current;
//	}
//	node* remove(const T& key,node* current,bool order_flag){
//		if (!current)
//			return current;
//		if (key<current->key)
//			current->left=remove(key,current->left);
//		else if(key>current->key)
//			current->right=remove(key,current->right);
//		else{//i.e. if the node is with only one child or no child
//			if (!current->left){
//				node *temp=current->right;
//				delete current;
//				--_size;
//				return temp;
//			}
//			else if(!current->right){
//				node *temp=current->left;
//				delete current;
//				--_size;
//				return temp;
//			}
//			/*Note: If the node has two children, place the in-order successor in position
//					of the node to be deleted & delete the in-order successor */
//			node *temp=min_value_node(current->right);
//			current->key=temp->key;
//			current->right=remove(temp->key,current->right);
//		}
//		return current;
//	}
	city_record search_by_city(const String& key,node* current){
		if(!current)
			return city_record("not found");
        if(key<current->key.city)
			return search_by_city(key,current->left);
		if(key>current->key.city)
			return search_by_city(key,current->right);
		return current->key;
	}
	city_record search_by_coordinates(const COORD& key,node* current){
		if(!current)
			return city_record("not found");
        if(key<current->key.coordinates)
			return search_by_coordinates(key,current->left);
		if(key>current->key.coordinates)
			return search_by_coordinates(key,current->right);
		return current->key;
	}
	void clear(node* current){
		if(!current)
			return;
		clear(current->left);
		clear(current->right);
		delete current;
	}
};

int main(){
	BST city_database;
	//Note: order-flag: true-> by city, false-> by coordinates
	
	city_database.insert(city_record("karachi",24.8607,67.0011),false);
	city_database.insert(city_record("islamabad",33.6844,73.0479),false);
	city_database.insert(city_record("peshawar",34.0151,71.5249),false);
	city_database.insert(city_record("kashmir",33.2778,75.3412),false);
	
	city_database.in_order_traversal();
	
//	cout<<"\nAfter deleting 10:";
//	tree.remove(10);
	
//	cout<<"\nInorder traversal: ";
//	tree.in_order_traversal();
	
	cout<<"\ntotal records: "<<city_database.total_records()<<endl;
	
//	cout<<"search: "<<city_database.search_by_city("islamabad");	
//	cout<<"search: "<<city_database.search_by_coordinates(33.6844,73.0479);
	return 0;
}
