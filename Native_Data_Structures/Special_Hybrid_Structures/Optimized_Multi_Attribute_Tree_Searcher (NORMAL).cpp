									/* NORMAL / LIGHT-WEIGHT VERSION (COMPLETED) */
#include"Pair.hpp"
#include"Indexed_Struct.hpp"
#include"../Node_Structures/AVL.hpp"
#include"../Node_Structures/List.hpp"

#include"../Contiguous_Structures/String.hpp"
//#include"../Contiguous_Structures/Vector.hpp"

template<typename T>
void print_type(){ std::cout<<__PRETTY_FUNCTION__<<'\n'; }//i.e. for debugging


/* Extended AVL class for handling Pair of respective pointed types alongwith
   their node-addresses of record in multi_attribute_tree_adapter class */
template<typename T,typename list_node_type>
class special_AVL:public AVL<Pair<T*,list_node_type*>>{
	typedef Pair<T*,list_node_type*> pair_type;
	typedef AVL<pair_type> base;
	using base::base;//i.e. inheriting all ctors of base class
	
public:
	void insert(const pair_type& key){ base::root=insert(key,base::root); }
	void remove(const T& key){ base::root=remove(key,base::root); }
	list_node_type* search(const T& key)const{ return search(key,base::root); }
	void traverse()const{ in_order_traversal(base::root); }
	
private:
	typename base::node* insert(const pair_type& key,typename base::node* current){
		if (!current){
			++base::_size;
			return new typename base::node(key);
		}
		if (*key.first==*current->key.first){
        	++(current->count);
        	return current;
    	}
		if (*key.first<*current->key.first)
			current->left=insert(key,current->left);
		else
			current->right=insert(key,current->right);
		current->height=base::max(base::height(current->left),base::height(current->right))+1;
  		/*i.e. balancing the tree by updating balance_factor of each node */
		__int64 bf=base::balance_factor(current);
  		if (bf>1)
    		if (*key.first<*current->left->key.first)//i.e. left left case
      			return base::right_rotate(current);
    		else if(*key.first>*current->left->key.first){//i.e. left right case
      			current->left=base::left_rotate(current->left);
      			return base::right_rotate(current);
    		}
  		if (bf<-1)
    		if (*key.first>*current->right->key.first)//i.e. right right case
      			return base::left_rotate(current);
    		else if (*key.first<*current->right->key.first){//i.e. right left case
    			current->right=base::right_rotate(current->right);
      			return base::left_rotate(current);
    		}
		return current;
	}
	
	typename base::node* remove(const T& key,typename base::node* current){
		if (!current)
			return current;
		if (key<*current->key.first)
			current->left=remove(key,current->left);
		else if(key>*current->key.first)
			current->right=remove(key,current->right);
		else{//i.e. current node is same as key
			if(current->count>1){
				--(current->count);
				return current;
			}
			if (!current->left||!current->right){//i.e. if the node is with only one child or no child
				typename base::node *temp=current->left?current->left:current->right;
				if(!temp){//i.e. no child case
					temp=current;
					current=nullptr;
				}
				else//i.e. one child case
					*current=std::move(*temp);
				--base::_size;
				delete temp;
			}
			else{/*Note: If the node has two children, it places the in-order successor in position
						 of the node to be deleted & deletes the in-order successor */
				typename base::node *temp=base::min_value_node(current->right);
				current->key=temp->key;
				current->count=temp->count;
				temp->count=1;
				current->right=remove(*temp->key.first,current->right);
			}
		}
		if(!current)
			return current;
		current->height=base::max(base::height(current->left),base::height(current->right))+1;
		/*i.e. balancing the tree by updating balance_factor of each node */
  		__int64 bf=base::balance_factor(current);
  		if (bf>1)
    		if (base::balance_factor(current->left)>-1)
      			return base::right_rotate(current);
    		else{
      			current->left=base::left_rotate(current->left);
      			return base::right_rotate(current);
    		}
  		if (bf<-1)
    		if (base::balance_factor(current->left)<1)
      			return base::left_rotate(current);
    		else{
    			current->right=base::right_rotate(current->right);
      			return base::left_rotate(current);
    		}
		return current;		
	}
	
	list_node_type* search(const T& key,typename base::node* current)const{
		if(!current)
			return nullptr;
        if(key<*current->key.first)
			return search(key,current->left);
		if(key>*current->key.first)
			return search(key,current->right);
		return current->key.second;
	}
	
	void in_order_traversal(typename base::node *current)const{
		if (current){
			in_order_traversal(current->left);
			std::cout<<*current->key.first<<'('<<current->count<<") ";
			in_order_traversal(current->right);
		}
	}
};


/* Multi-Attribute AVL Tree Adapter for Efficient Tree Operations */
template<typename... attributes>
class multi_attribute_tree_adapter{
	typedef List<indexed_struct<attributes...>> list_type;
	list_type data;//i.e. records stored as indexed_struct in List
	
	indexed_struct<special_AVL<attributes,typename list_type::node>...> trees;
	/*Important Notes for 'trees':
		1) theoretically similar to: AVL<Pair<respective_type*,respective_node_type*>> trees[total_attributes]
		   (i.e. array of pointer-AVL trees of distinct data-types & their respective storage_nodes )
		2) each special_AVL tree individually points to specific attribute of records (i.e. indexed_structs)
	*/
public:
	multi_attribute_tree_adapter()noexcept:
		trees{special_AVL<attributes,typename list_type::node>()...}{}
	
	size_t total_attributes()const{ return sizeof...(attributes); }
	size_t total_records()const{ return data.size(); }
	
	template<typename... _attributes>//Note: _attributes&&... -> universal references
	void insert(_attributes&&... key_record)//i.e. O(M*logN) time-complexity [here, N=total records, M=total attributes]
		data.push_back(forward<_attributes>(key_record)...);
		size_t index=0;
		bool expander[]{
			( ((special_AVL<attributes,typename list_type::node>*)(trees+index++))->
				insert(Make_Pair((attributes*)(data.back()+index),data.back_node())),
				false )... 
		};
	}
	//FEATURE:need move_insert_for_indexed_struct, no copy!!
	
	template<typename T>
	void remove(const T& key,const size_t index){//i.e. O((M+1)*logN) time-complexity
		typename list_type::node* list_node=((special_AVL<T,typename list_type::node>*)(trees+index))->search(key);
		if(list_node){//i.e. to handle null-exception for both AVL-tree & List containers
			size_t i=0;
			bool expander[]{
				( ((special_AVL<attributes,typename list_type::node>*)(trees+i++))->
					remove(*(attributes*)(list_node->data+i)),
					false )... 
			};
			data.erase(list_node);//i.e. removes node randomly in O(1) time since current_node is known
		}
		else
			cout<<"No Records Found!\n\a";
	}
	
	template<typename T>
	void search(const T& key,const size_t index)const{//i.e. O(logN) time-complexity
		typename list_type::node* list_node=((special_AVL<T,typename list_type::node>*)(trees+index))->search(key);
		if(list_node)//i.e. for null-exception safety
			cout<<*list_node;
		else
			cout<<"No Records Found!\n\a";
	}
	
	void traverse_by_attributes()const{//i.e. traverses records by trees
		size_t index=0;
		bool expander[]{
			( ((special_AVL<attributes,typename list_type::node>*)(trees+index++))->traverse(),cout<<'\n',false )...
		};
	}
	void traverse_by_records()const{//i.e. traverses records by list
		for(const auto& it:data)
			cout<<it<<'\n';
	}
	
	void clear(){//i.e. clears all the resources of both list & trees
		size_t index=0;
		bool expander[]{ ((*(special_AVL<attributes,typename list_type::node>*)(trees+index++)).clear(),false)... };
		data.clear();
	}
};


int main(){
	multi_attribute_tree_adapter<int,String,double,char> MATA;
	
	MATA.insert(123,String{"Great Work!"},77.11,'f');//i.e. insert record in O(M*logN) time
	MATA.insert(919,String{"noice"},444.444,'c');
	MATA.insert(919,String{"hello"},444.444,'z');//i.e. also handles duplicate values
	MATA.insert(191,String{"hello"},919.19,'d');
	MATA.insert(332,String{"right"},345.1,'e');
	MATA.insert(404,String{"left"},345.1,'q');
	MATA.insert(321,String{"stranded"},0.1,'f');
	
	{
		int i=393; String s{"copied resource"};
		MATA.insert(i,s,5555555.55,'f');
		//i.e. both local/left/l-values & register/right/r-values can be passed efficiently & simultaneously
	}
	
//	MATA.remove('c',3);//i.e. remove record by any attribute
//	MATA.remove(String{"hello"},1);//Note: for duplicates, it removes the first most inserted attribute
//	MATA.remove(345.1,2);
	
//	MATA.search('d',3);//i.e. search record by any attribute in O(logN) time
//	MATA.search('f',3);//Note: for duplicates, shows the first-most inserted duplicate

//	MATA.clear();
	
	cout<<"\n-----\n";
	MATA.traverse_by_records();
	cout<<'\n';//Note: always prefer to use '\n' over std::endl
	MATA.traverse_by_attributes();	
	return 0;
}
