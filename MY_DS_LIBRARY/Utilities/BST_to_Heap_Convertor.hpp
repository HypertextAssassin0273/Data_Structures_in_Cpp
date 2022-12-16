#if __cplusplus >= 201103L

#ifndef BST_TO_HEAP_CONVERTOR_GUARD
#define BST_TO_HEAP_CONVERTOR_GUARD 1

#include <iostream>

//forward declarations:
template<typename> class BST;
template<typename> class List;

template<typename T>
class BST_to_Heap_Convertor:
	public BST<T>{//Note: not very efficient approach
	
	typedef BST<T> base;
	using base::BST;//inheriting ctors of base class (C++11)
	
public:
	void convert_BST_to_max_heap()const{
		List<T> queue;
		in_order_transfer_to_queue(base::root, queue);
		post_order_transfer_to_BST(base::root, queue);
	}
	void convert_BST_to_min_heap()const{
		List<T> queue;
		in_order_transfer_to_queue(base::root, queue);
		pre_order_transfer_to_BST(base::root, queue);
	}
	void convert_min_heap_to_max_heap()const{
		List<T> queue;
		pre_order_transfer_to_queue(base::root, queue);
		post_order_transfer_to_BST(base::root, queue);
	}
	void convert_max_heap_to_min_heap()const{
		List<T> queue;
		post_order_transfer_to_queue(base::root, queue);
		pre_order_transfer_to_BST(base::root, queue);
	}
	
private:
	void pre_order_transfer_to_queue(typename base::node* current, List<T>& queue)const{
		if (current){
			queue.push_back(std::move(current->key));
			pre_order_transfer_to_queue(current->left, queue);
			pre_order_transfer_to_queue(current->right, queue);
		}
	}
	void in_order_transfer_to_queue(typename base::node* current, List<T>& queue)const{
		if (current){
			in_order_transfer_to_queue(current->left, queue);
			queue.push_back(std::move(current->key));
			in_order_transfer_to_queue(current->right, queue);
		}
	}
	void post_order_transfer_to_queue(typename base::node* current,List<T>& queue)const{
		if (current){
			post_order_transfer_to_queue(current->left, queue);
			post_order_transfer_to_queue(current->right, queue);
			queue.push_back(std::move(current->key));
		}
	}
	
	void pre_order_transfer_to_BST(typename base::node* current, List<T>& queue)const{
    	if (current){
	  	  	current->key=std::move(queue.front());
	 		queue.pop_front();
    		pre_order_transfer_to_BST(current->left, queue);
    		pre_order_transfer_to_BST(current->right, queue);
    	}
	}
	void post_order_transfer_to_BST(typename base::node* current, List<T>& queue)const{
    	if (current){
			post_order_transfer_to_BST(current->left, queue);
			post_order_transfer_to_BST(current->right, queue);
			current->key=std::move(queue.front());
		 	queue.pop_front();
		}
	}
};
#endif

#endif
