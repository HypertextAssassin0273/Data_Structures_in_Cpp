#ifndef MULTI_ATTRIBUTE_TREE_ADAPTER_GUARD
#define MULTI_ATTRIBUTE_TREE_ADAPTER_GUARD 1

#include"Indexed_Struct.hpp"
#include"../Node_Structures/AVL.hpp"
#include"../Node_Structures/List.hpp"
#include"Additional_Header_Files/Pair.hpp"

/* Optimized Multi-Attribute AVL Tree Adapter for Efficient Tree Operations */
template<typename... attributes>
class multi_attribute_tree_adapter{
private:
	/* Extended AVL class for handling Pair of respective pointed types alongwith their duplicate
	   record node-addresses in doubly linked-list, only for multi_attribute_tree_adapter class */
	template<typename T,typename storage_list_type>
	class e_AVL:public AVL<Pair<T*,List<storage_list_type*,true>>>{//i.e. hidden class (from outer-world)
		typedef List<storage_list_type*,true> dup_list_type;//i.e. using List with Garbage_Collector version
		typedef Pair<T*,dup_list_type> pair_type;
		typedef AVL<pair_type> base;
		using base::base;//i.e. inheriting all ctors of base class
		
	public:	/* methods directly used/accessed by multi_attribute_tree_adapter class */
		void insert(T* key,storage_list_type* key_node){ base::root=insert(key,key_node,base::root); }
		void remove(T* key,storage_list_type* key_node,const size_t& key_index){ 
			base::root=remove(key,key_node,key_index,base::root);
		}
		const dup_list_type* search(const T& key)const{ return search(key,base::root); }
		void traverse()const{ in_order_traversal(base::root); }
		
	private: /* complete hidden methods */
		typename base::node* insert(T* key,storage_list_type* key_node,typename base::node* current){
			if (!current){
				++base::_size;
				return new typename base::node(pair_type(key,dup_list_type{key_node}));
			}
			if (*key==*current->data.first){
    	    	current->data.second.push_back(key_node);
				//i.e. inserting respective node address of storage_list in dup_list
    	    	++(current->count);
    	    	return current;
    		}
			if (*key<*current->data.first)
				current->left=insert(key,key_node,current->left);
			else
				current->right=insert(key,key_node,current->right);
			current->height=base::max(base::height(current->left),base::height(current->right))+1;
  			/*i.e. balancing the tree by updating balance_factor of each node */
			__int64 bf=base::balance_factor(current);
  			if (bf>1){
    			if (*key>*current->left->data.first)//i.e. left-right-case
      				current->left=base::left_rotate(current->left);
      			return base::right_rotate(current);//i.e. if above condition isn't true, then its left-left-case
    		}
  			if (bf<-1){
    			if (*key<*current->right->data.first)//i.e. right-left-case
    				current->right=base::right_rotate(current->right);
      			return base::left_rotate(current);//i.e. if above condition isn't true, then its right-right-case
    		}
			return current;
		}
		
		typename base::node* remove(T* key,storage_list_type* key_node,
									const size_t& key_index,
									typename base::node* current){
			if (!current) return current;
			if (*key<*current->data.first)
				current->left=remove(key,key_node,key_index,current->left);
			else if(*key>*current->data.first)
				current->right=remove(key,key_node,key_index,current->right);
			else{//i.e. current node is same as key
				if(current->count>1){
					for(auto& iter:current->data.second)
						if(key_node==iter.data){
							current->data.second.erase(&iter);
							//i.e. releasing respective node address of storage_list from dup_list
							current->data.first=(T*)((current->data.second.front())->data+key_index);
							//i.e. updating current type_ptr to one of the present_nodes in dup_list
							break;
						}
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
						*current=std::move(*temp);//i.e. move-assignment of node
					--base::_size;
					delete temp;
				}
				else{/*Note: If the node has two children, it places the in-order successor in position
							 of the node to be deleted & deletes the in-order successor */
					typename base::node *temp=base::min_value_node(current->right);
					current->data=std::move(temp->data);//i.e. data of min_value_node must be moved
					current->count=temp->count;
					temp->count=1;//i.e. so we don't remove duplicates again
					current->right=remove(current->data.first,nullptr,0,current->right);
				}
			}
			if(!current) return current;
			current->height=base::max(base::height(current->left),base::height(current->right))+1;
			/*i.e. balancing the tree by updating balance_factor of each node */
  			__int64 bf=base::balance_factor(current);
  			if (bf>1){
    			if (base::balance_factor(current->left)<0)
      				current->left=base::left_rotate(current->left);
      			return base::right_rotate(current);
    		}
  			if (bf<-1){
    			if (base::balance_factor(current->left)>0)
    				current->right=base::right_rotate(current->right);
      			return base::left_rotate(current);
    		}
			return current;
		}
		
		const dup_list_type* search(const T& key,typename base::node* current)const{ 
			if(!current)
				return nullptr;
    	    if(key<*current->data.first)
				return search(key,current->left);
			if(key>*current->data.first)
				return search(key,current->right);
			return &current->data.second;//i.e. returns a ptr to list of duplicate record ptrs (on successful search)
		}
		
		void in_order_traversal(typename base::node *current)const{
			if (current){
				in_order_traversal(current->left);
				std::cout<<*current->data.first<<'('<<current->count<<") ";
				in_order_traversal(current->right);
			}
		}
	};
	
	
	/** Main-Class Attributes **/
	typedef multi_attribute_tree_adapter __self;
	typedef indexed_struct<true,attributes...> record_type;//i.e. using optimized memory indexed_struct version
	typedef List<record_type> list_type;
	
	list_type data;//Note: records are stored as indexed_struct in List
	indexed_struct<true,e_AVL<attributes,typename list_type::node>...> trees;
	/*Important Notes for 'trees':
		1) theoretically similar to: AVL<Pair<respective_type*,List<storage_list_node_type*>>> trees[total_attributes]
		2) each e_AVL tree individually points to a specific attribute of record (i.e. indexed_struct)
		   and also to a list of pointers to the duplicates of that record
	*/
public:
	/** Constructors **/
	multi_attribute_tree_adapter()noexcept://i.e. default constructing e_AVL r-value-objs on indexed_struct 'trees'
		trees{e_AVL<attributes,typename list_type::node>()...}{}//i.e. default ctor
	
	multi_attribute_tree_adapter(const __self&)noexcept=delete;//i.e. deleted copy ctor
	multi_attribute_tree_adapter& operator=(const __self&)noexcept=delete;//i.e. deleted copy assignment operator
	/*Why Deleted?: e_AVL trees contains dependant & non-sharable data_node pointers, 
					which cannot be copied to new location */
	
	multi_attribute_tree_adapter(__self&&)noexcept=default;//i.e. allowed move ctor
	multi_attribute_tree_adapter& operator=(__self&&)noexcept=default;//i.e. allowed move assignment operator
	/*Why Allowed?: only main ptrs of List & e_AVLs are copied to new location, 
					means stored data_node ptrs aren't shared */
	
	multi_attribute_tree_adapter(std::initializer_list<record_type> init_list)noexcept:
		trees{e_AVL<attributes,typename list_type::node>()...}{//i.e. initializer_list ctor
		for(const auto& it:init_list)//i.e. traversing init_list through iterator
			this->insert(it);
	}
	
	multi_attribute_tree_adapter(const std::string& file_name,bool ignore_sb_flag=false)noexcept:
		trees{e_AVL<attributes,typename list_type::node>()...}{//i.e. input_file_stream ctor
		std::ifstream file("Data_Files/"+file_name);
		if(file){
			if(ignore_sb_flag){//i.e. for .csv files
				std::string temp_stream_buffer;
				std::getline(file,temp_stream_buffer);
			}
			record_type temp_key_rec;
			while(file.peek()!=EOF){
				file>>temp_key_rec;
				this->insert(std::move(temp_key_rec));
			}
			file.close();
		}
	}
	
	/** Accessors **/
	size_t attributes_size()const{ return sizeof...(attributes); }
	size_t records_size()const{ return data.size(); }
	
	/** Modifiers **/
	template<typename... __attributes>// i.e. emplaced_insert, efficient version
	void insert(__attributes&&... key_record_attrs){//i.e. O(M*logN) complexity [M=total_attributes, N=total_records]
		this->data.push_back(std::forward<__attributes>(key_record_attrs)...);
		size_t index=0;
		bool expander[]{
			( ((e_AVL<attributes,typename list_type::node>*)(this->trees+index++))->
				insert((attributes*)(this->data.back()+index),this->data.back_node()),false )... 
		};
	}
	template<typename __record_type>//Note: __record_type&&... -> universal reference
	void insert(__record_type&& key_record){//i.e. overloaded version for inserting copy/move constructed record obj
		this->data.push_back(std::forward<__record_type>(key_record));
		size_t index=0;
		bool expander[]{
			( ((e_AVL<attributes,typename list_type::node>*)(this->trees+index++))->
				insert((attributes*)(this->data.back()+index),this->data.back_node()),false )... 
		};
	}
	
	template<typename type,typename... types>//i.e. remove narrowed-down/specific duplicates by multiple-attributes
	void remove(const size_t& key_index,
				const type& key,const types&... keys){//i.e. O(logN+D*M*logN) complexity [D=total_duplicates]
		if(key_index>sizeof...(attributes)-1) return;
		auto dup_list_ptr=((e_AVL<type,typename list_type::node>*)(this->trees+key_index))->search(key);
		if(dup_list_ptr){//i.e. null-exception safety
			auto iter=dup_list_ptr->front_node();//i.e. iterator to dup_list, since we can't traverse it directly
			typename list_type::node* dup_node_ptr;//i.e. pointer to duplicate record node
			bool is_present;//i.e. flag for storing decision whether to keep duplicate or not
			for(size_t index,total_dups=dup_list_ptr->size(),i=0;i<total_dups;++i){
				index=key_index+1; is_present=true;//i.e. need to reset for every record
				dup_node_ptr=iter->data;
				iter=iter->next;//Note: iter must be updated here, because its pointed node will be deleted afterwards
				bool expander[]{ is_present=is_present&&(keys==*(types*)(dup_node_ptr->data+index++))... };
				if(is_present){
					index=0;//i.e. resetting index in order to correctly access all AVL trees
					bool expander[]{//i.e. removing currently-pointed record attributes from their respective tree
						( ((e_AVL<attributes,typename list_type::node>*)(this->trees+index))->
						    remove((attributes*)(dup_node_ptr->data+index),dup_node_ptr,index),
							index++,false )...
					};
					this->data.erase(dup_node_ptr);//i.e. removes random node from list in O(1) time
				}
			}
		}
		else
			std::cout<<"No Records Found!\n\a";
	}
	
	void clear(){//i.e. clears all the resources of both list & trees
		data.clear();
		size_t index=0;
		bool expander[]{
			(((e_AVL<attributes,typename list_type::node>*)(this->trees+index++))->clear(),false)...
		};
	}
	
	/** Non-Modifiers **/
	template<typename type,typename... types>//i.e. search by multiple-attributes for narrowed-down duplicate results
	void search(const size_t& key_index,const type& key,const types&... keys)const{//i.e. O(logN+D) time-complexity
		if(key_index>sizeof...(attributes)-1) return;
		auto dup_list_ptr=((e_AVL<type,typename list_type::node>*)(this->trees+key_index))->search(key);
		if(dup_list_ptr){//i.e. for null-exception safety
			size_t index; bool is_present;
			for(const auto& iter:*dup_list_ptr){//i.e. using ptr to list of node-ptrs of duplicates
				index=key_index+1; is_present=true;//i.e. need to reset for every record
				bool expander[]{ is_present=is_present&&(keys==*(types*)(iter.data->data+index++))... };
				if(is_present) std::cout<<iter.data->data<<'\n';//i.e. prints only respective matched records
			}
		}
		else
			std::cout<<"No Records Found!\n\a";
	}
	
	void traverse_by_attributes()const{//i.e. traverse records by trees
		if(this->data.empty()) return;
		size_t index=0;
		bool expander[]{
			( ((e_AVL<attributes,typename list_type::node>*)(this->trees+index++))->traverse(),
				std::cout<<'\n',false )...
		};
	}
	void traverse_by_records()const{//i.e. traverse records by list
		for(const auto& iter:this->data)
			std::cout<<iter<<'\n';
	}
	
	/** File Operations **/
	void fread(const std::string& file_name,//i.e. reads from source_file
			   bool clear_flag=false,//i.e. to either clear the previous stored records or not in system
			   bool ignore_sb_flag=false//i.e. to either ignore coloumn names or not in .csv files
			   ){
		if(clear_flag)
			this->clear();
		std::ifstream file("Data_Files/"+file_name);
		if(file){
			if(ignore_sb_flag){
				std::string temp_stream_buffer;
				std::getline(file,temp_stream_buffer);
			}
			record_type temp_key_rec;
			while(file.peek()!=EOF){
				file>>temp_key_rec;
				this->insert(std::move(temp_key_rec));
			}
			file.close();
		}
	}
	
	void fwrite(const std::string& file_name,//i.e. writes in destination_file
				bool overwrite_flag=false,//i.e. to either overwrite or append a file
				const std::string& stream_buffer=""//i.e. for adding coloumn names in .csv files
				)const{
		std::ofstream file("Data_Files/"+file_name,overwrite_flag?
													std::ios::binary:
													std::ios::binary|std::ios::ate|std::ios::in);
		/*Note: if file is present, open in binary_truncation mode for overwriting or in binary_append mode
				for appending data in file.
		  Why binary mode?: we've used seekp for moving file_ptr to replace last comma with new-line
							character in indexed_struct 'fout' operator, which basically disturbs 
							windows file_encoding format if we open file in normal mode.
		*/
		if(!file)//i.e. if file isn't present, first create file & then open in binary mode
			file.open("Data_Files/"+file_name,std::ios::binary);
		if(stream_buffer.size())
			file<<stream_buffer<<'\n';
		for(const auto& iter:this->data)
			file<<iter.data;
		file.close();
	}
};

#endif
