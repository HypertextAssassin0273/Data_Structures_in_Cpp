#ifndef MULTI_ATTRIBUTE_AVL_TREE_ADAPTER_GUARD
#define MULTI_ATTRIBUTE_AVL_TREE_ADAPTER_GUARD 1

#include "../Trees/AVL.hpp"
#include "Indexed_Struct.hpp"
#include "../Utilities/Pair.hpp"
#include "../Linked_Lists/List.hpp"
#include "../Linked_Lists/Forward_List.hpp"

template<typename T>
void print_type(){ std::cout<<__PRETTY_FUNCTION__<<'\n'; }//for debugging

/* Optimized Multi-Attribute AVL Tree Adapter for Efficient Tree Operations */
template<typename... attributes>
class MAATA{
	/** Simplified Type Names (for M.A.A.T.A) **/
	typedef indexed_struct<attributes...> record_type;
	typedef List<record_type> list_type;//Doubly List with/without garbage_collector version
	typedef typename list_type::node record_node_type;
	typedef Forward_List<record_node_type*> dup_list_type;//Singly List with/without garbage_collector version
	
	/* Extended AVL class for handling Pair of respective pointed types alongwith their
	   duplicate record node-addresses in doubly linked-list (only for M.A.A.T.A class) */
	template<typename T>
	class e_AVL:
		public AVL<Pair<T*, dup_list_type>>{//hidden class
		
		/* simplified type names (for e_AVL) */
		typedef Pair<T*, dup_list_type> pair_type;
		typedef AVL<pair_type> base;
		typedef typename base::node node;
		
		using base::root;
		using base::base;//inheriting all ctors of base class [C++11 construct]
		
	public:
		/* modifiers */
		void insert(T* key, record_node_type* key_node){ root=insert(key, key_node, root); }
		
		void remove(T* key, record_node_type* key_node, const size_t key_index){ 
			root=remove(key, key_node, key_index, root);
		}
		/* non-modifiers */
		const dup_list_type* search(const T& key)const{ return search(key, root); }
		
		void traverse()const{ in_order_traversal(root); }
		
		void sort_list(list_type& list, list_type& new_list)const{ sort_list(list, new_list, root); }
		
	private:
		/* hidden methods */
		node* insert(T* key, record_node_type* key_node, node* current){
			if(!current){
				++base::_size;
				return new node(pair_type(key, dup_list_type(1, key_node)));//using forward_list fill ctor
			}
			if(*key==*current->data.first){
    	    	current->data.second.push_front(key_node);
				//inserting respective node address of record in forward_list of duplicates
    	    	++(current->count);
    	    	return current;
    		}
			if(*key<*current->data.first)
				current->left=insert(key, key_node, current->left);
			else
				current->right=insert(key, key_node, current->right);
			current->height=base::calc_height(current);//height must be updated before balancing tree
  			return balance_tree(key, current);//each node needs to be checked for keeping the tree balanced
		}
		
		node* remove(T* key, record_node_type* key_node, const size_t key_index, node* current){
			if(!current) return current;
			if(*key<*current->data.first)
				current->left=remove(key, key_node, key_index, current->left);
			else if(*key>*current->data.first)
				current->right=remove(key, key_node, key_index, current->right);
			else{//current node is same as key
				if(current->count>1){
					current->data.second.erase(key_node);//complexity: O(n)
					//releasing respective node address of record from forward_list of duplicates
					current->data.first=(T*)((current->data.second.front())->data+key_index);
					//updating current type_ptr to one of the present_nodes in forward_list
					--(current->count);
					return current;
				}
				if(current->left&&current->right){//if node has both children, then remove the in-order successor
					node *temp=base::min_value_node(current->right);
					current->data=std::move(temp->data);//Note: here, data can be moved without any exception
					current->count=temp->count;
					temp->count=1;//resetting count, so we can delete the in-order successor node
					current->right=remove(current->data.first, nullptr, 0, current->right);
				}else{//else node is with only one child or no child
					node *temp=current->left?:current->right;
					--base::_size;
					if(temp){//one child case
						*current=std::move(*temp);//move-assignment of node
						delete temp;
					}else{//no child case
						delete current;
						return nullptr;
					}
				}
			}
			current->height=base::calc_height(current);//updating height
			return base::balance_tree(current);//since key's respective node is removed, we need to rely on this version
		}
		
		const dup_list_type* search(const T& key, node* current)const{//const dup_list_type*
			return current?
					key<*current->data.first?
						search(key, current->left):
					key>*current->data.first?
						search(key, current->right):
					&current->data.second:nullptr;
		}//returns a read-only ptr to forward_list of duplicate record's node addresses (on successful search)
		
		void in_order_traversal(node* current)const{
			if(current){
				in_order_traversal(current->left);
				std::cout<<*current->data.first<<'('<<current->count<<") ";
				in_order_traversal(current->right);
			}
		}
		
		/* helper method (for simplifying code) */
		node* balance_tree(T* key, node* current){//overloaded version for accessing key in pair  
			__int64 bf=base::balance_factor(current);
  			if(bf>1){
    			if(*key>*current->left->data.first)//left-right-case
      				current->left=base::left_rotate(current->left);
      			return base::right_rotate(current);//otherwise, its left-left-case
    		}
  			if(bf<-1){
    			if(*key<*current->right->data.first)//right-left-case
    				current->right=base::right_rotate(current->right);
      			return base::left_rotate(current);//otherwise, its right-right-case
    		}
			return current;
		}
		
		/* hidden list operation method  */
		void sort_list(list_type& list, list_type& new_list, node* current)const{
			if(current){
				sort_list(list, new_list, current->left);
				for(auto& iter:current->data.second)
					new_list.push_back(list.erase(iter, true));
				sort_list(list, new_list, current->right);
			}
		}//removes random stored node from old_list & then inserts it in new_list in ascending order w.r.t tree type
	};
	
	/** Main-Class Attributes **/
	list_type data;//Note: records are stored inside Doubly Linked List as Mapped Object Array
	indexed_struct<e_AVL<attributes>...> trees;
	/*Important Notes for 'trees':
		1) theoretically: AVL<Pair<respective_type*, Forward_List<List::node<record_type>*>>> trees[total_attributes];
		2) each e_AVL tree individually points to a specific attribute of record (i.e. indexed_struct)
		   and also to a singly linked-list of pointers to the duplicates of that record.
	*/
	
public:
	/** Constructors & Assignment Operators **/
	MAATA()noexcept{}//default ctor
	//Note: it implicitly default constructs e_AVL r-value-objects directly inside indexed_struct 'trees'
	
	//copy semantics (deep copy) [disabled]:
	MAATA(const MAATA&)noexcept=delete;//copy ctor
	MAATA& operator=(const MAATA&)noexcept=delete;//copy assignment operator
	//Reason: e_AVL trees contains dependant & non-sharable data_node pointers, which cannot be copied to new location.
	
	//move semantics (shallow copy) [allowed]:
	MAATA(MAATA&&)noexcept=default;//move ctor
	MAATA& operator=(MAATA&&)noexcept=default;//move assignment operator
	//Reason: only main ptrs of List & e_AVLs are copied to new location, means stored data_node ptrs aren't shared.
	
	template<size_t N>
	MAATA(record_type (&&init_list)[N])noexcept{//move initializer_list ctor
		for(auto& iter:init_list)//traversing array of r-value references through iterator
			this->insert(std::move(iter));
	}
	
	MAATA(const std::string& file_name, bool ignore_sb_flag=false)noexcept{//input_file_stream ctor
		std::ifstream file("Data_Files/"+file_name);
		if(file){
			if(ignore_sb_flag){//for .csv files
				std::string temp_stream_buffer;
				std::getline(file, temp_stream_buffer);
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
	template<typename... __attributes>//universal references
	void insert(__attributes&&... key_record_attrbs){//emplaced_insert, efficient version
		this->data.push_back(std::forward<__attributes>(key_record_attrbs)...);
		size_t idx=0;//index iterator for traversing mapped array of (distinct) respective type AVL trees
		bool expander[]{
			( ((e_AVL<attributes>*)(this->trees+idx++))->
				insert((attributes*)(this->data.back()+idx), this->data.back_node()), false )... 
		};
	}
	template<typename __record_type>
	void insert(__record_type&& key_record){//copy/move constructed record object insert version
		this->data.push_back(std::forward<__record_type>(key_record));
		size_t idx=0;
		bool expander[]{
			( ((e_AVL<attributes>*)(this->trees+idx++))->
				insert((attributes*)(this->data.back()+idx), this->data.back_node()), false )... 
		};
	}//O(M*logN) time complexity [M=total_attributes, N=total_records]
	
	template<size_t N, typename type, typename... types>//removes records along with its duplicates (in any order)
	void remove(const int (&key_indexes)[N], const type& key, const types&... keys){
		if(N!=sizeof...(keys)+1) return;//bound exception safety
		auto dup_list_ptr=((e_AVL<type>*)(this->trees+key_indexes[0]))->search(key);
		if(dup_list_ptr){//null exception safety
			auto begin=dup_list_ptr->begin(), end=dup_list_ptr->end();//node iterators for safely traversing dup_list
			size_t idx;//index iterator for traversing key_indexes (of respective record attributes)
			bool is_present;//flag for storing decision whether to keep duplicate or not
			while(begin!=end){
				idx=1; is_present=true;//needs to be re-initialized for every iteration
				auto dup_node_ptr=*begin;//preserves current pointed duplicate record's node address
				++begin;//Note: iterator must be updated here, because its pointed node might be deleted afterwards
				bool expander[]{ is_present=is_present&&(keys==*(types*)(dup_node_ptr->data+key_indexes[idx++]))... };
				if(is_present){//removes only respective matched records
					idx=0;//resets index iterator for traversing mapped array of AVL trees
					bool expander[]{//removes respective key node or duplicate record's node address from all trees
						( ((e_AVL<attributes>*)(this->trees+idx))->
							remove((attributes*)(dup_node_ptr->data+idx), dup_node_ptr, idx), ++idx, false )...
					};
					this->data.erase(dup_node_ptr);//removes current node (along with record) from list in O(1) time
				}
			}
		}else std::cout<<"No Records Found!\n\a";
	}//O((D*F*(logN+1)+logN) time complexity [D=total_duplicates, F=filter_keys, N=total_records]
		
	template<size_t N, typename... types>//update records along with its duplicates (in any order)
	void update(dup_list_type&& filtered_dup_list, const int (&key_indexes)[N], types&&... keys)const{
		if(N!=sizeof...(keys)) return;//bound exception safety
		size_t i, idx;
		while(!filtered_dup_list.empty()){
			auto dup_node_ptr=filtered_dup_list.front();
			filtered_dup_list.pop_front();
			{i=0;
			bool expander[]{
				( idx=key_indexes[i++],
				  ((e_AVL<types>*)(this->trees+idx))->
					remove((types*)(dup_node_ptr->data+idx), dup_node_ptr, idx),
				  false )...
			};}//local scope (defined for explicit manual deallocation)
			dup_node_ptr->data.set(key_indexes, keys...);//Note: keys shouldn't be forwarded
			i=0;
			bool expander[]{
				( idx=key_indexes[i++],
				  ((e_AVL<types>*)(this->trees+idx))->
					insert((types*)(dup_node_ptr->data+idx), dup_node_ptr),
				  false )...
			};
		/*removes respective key attributes & after updating record, inserts
		  updated keys of filtered duplicate records in their respective trees*/
		}
	}//O(S+T*R) time complexity [S=search_time, D=total_filtered_duplicates, R=record_filter_keys]
	
	void sort(size_t index){//for run-time
		type_extractor<0, attributes...>(index);
	}//O(N*D+E) time complexity [N=total_records, D=total_varying_duplicates, E=recursive_extraction_time]
	template<size_t index>
	void sort(){//for compile-time (efficient)
		list_type new_list;
		this->trees.template get<index>().sort_list(data, new_list);
		data=std::move(new_list);
	}//O(N*D) time complexity [N=total_records, D=total_varying_duplicates]
	
	void clear(){//clears all the resources of both list & trees
		data.clear();
		size_t idx=0;
		bool expander[]{ (((e_AVL<attributes>*)(this->trees+idx++))->clear(), false)... };
	}//O(N+M*logN) time complexity [N=total_records, M=total_attributes]
	
	/** Non-Modifiers **/
	template<size_t N, typename type, typename... types>//search records along with its duplicates (in any order)
	dup_list_type search(const int (&key_indexes)[N], const type& key, const types&... keys)const{
		if(N!=sizeof...(keys)+1) return dup_list_type();//bound exception safety
		auto dup_list_ptr=((e_AVL<type>*)(this->trees+key_indexes[0]))->search(key);
		dup_list_type filtered_dup_list;
		if(dup_list_ptr){//null exception safety
			size_t idx; bool is_present;
			for(auto& iter:*dup_list_ptr){//using iterator of pointed forward_list in range loop
				idx=1; is_present=true;//needs to be reset for every iteration
				bool expander[]{ is_present=is_present&&(keys==*(types*)(iter->data+key_indexes[idx++]))... };
				if(is_present) filtered_dup_list.push_front(iter);//stores only respective matched record nodes
			}
		}else std::cout<<"No Records Found!\n\a";
		return filtered_dup_list;
	}//O(logN+D*F) time complexity [N=total_records, D=total_duplicates, F=filter_keys]
	
	void traverse_by_attributes()const{//traverse records by trees
		if(this->data.empty()) return;
		size_t idx=0;
		bool expander[]{
			( ((e_AVL<attributes>*)(this->trees+idx++))->traverse(), std::cout<<'\n', false )...
		};
	}
	void traverse_by_records()const{//traverse records by list
		for(auto& iter:this->data)
			std::cout<<iter<<'\n';
	}
	
	/** File Operations **/
	void fread(const std::string& file_name,//reads from source_file
			   bool clear_flag=false,//to either clear the previous stored records or not in system
			   bool ignore_sb_flag=false//to either ignore coloumn names or not in .csv files
			   ){
		if(clear_flag) this->clear();
		std::ifstream file("Data_Files/"+file_name);
		if(!file) return;
		if(ignore_sb_flag){//sb: stream_buffer
			std::string temp_stream_buffer;
			std::getline(file, temp_stream_buffer);
		}
		record_type temp_key_rec;
		while(file.peek()!=EOF){
			file>>temp_key_rec;
			this->insert(std::move(temp_key_rec));
		}
		file.close();
	}
	
	void fwrite(const std::string& file_name,//writes in destination_file
				bool overwrite_flag=false,//to either overwrite or append a file
				const std::string& stream_buffer=""//for adding coloumn names in .csv files
				)const{
		std::ofstream file("Data_Files/"+file_name,
							overwrite_flag? std::ios::binary: std::ios::binary|std::ios::ate|std::ios::in);
		/*Note: if file is present, then open in binary_truncation mode (for overwriting)
				or in binary_append mode (for appending data in file).
		  Why binary mode?: we've used seekp for moving file_ptr to replace last comma with new-line
							character in indexed_struct 'fout' operator, which basically disturbs 
							windows file_encoding format if we open file in normal mode.
		*/
		if(!file)//if file isn't present, first create file & then open in binary mode
			file.open("Data_Files/"+file_name, std::ios::binary);
		if(stream_buffer.size())
			file<<stream_buffer<<'\n';
		for(const auto& iter:this->data)
			file<<iter;
		file.close();
	}
	
private:
	/** Hidden Methods **/
	template<size_t N>
	void type_extractor(size_t){ std::cout<<"Error: Wrong Tree Index Provided!\n"; }//base case overload
	
	template<size_t N , typename T, typename... Ts>
	void type_extractor(size_t index){//helper method for applying operations on single specific tree
		if(N==index){
			list_type new_list;
			((e_AVL<T>*)(this->trees+N))->sort_list(data, new_list);
			data=std::move(new_list);
			return;
		}
		type_extractor<N+1, Ts...>(index);	
	}//O(E) time complexity [E=recursive_extraction_time: total_attributes-index_position]
};

#endif
