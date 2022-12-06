/** Node Garbage Collector (for Linked Lists only) **/
/*	Warning: objects shouldn't be used directly [i.e. has-a relationship required]
	Use: effective in long run programs where there is constant usage of operations
   	Important Notes:
	1) only effective for Linked-Lists with tail preserved versions
	2) should be kept private since, all exception safeties are removed for optimize results
	3) for keeping public, first enable all exception safety checks
*/
#ifndef GARBAGE_COLLECTOR_GUARD
#define GARBAGE_COLLECTOR_GUARD 1

#include <iostream>

#if __cplusplus < 201103L
#define nullptr 0L
#define noexcept
#endif

template<typename node>
class garbage_collector{//implementing stack by LIFO order
	node* top;//points top node
	size_t _size;//tracks total nodes present in GC stack
public:
	const size_t max_capacity;
	
	/* accessors */
	const node* peek()const{ return top; }
	size_t size()const{ return _size; }
	bool empty()const{ return !top; }
	
	garbage_collector(size_t mc)noexcept://parameterized ctor
		max_capacity(mc), _size(0), top(nullptr){}
	
	/* modifiers */
	void push(node* l_node){//complexity O(1)
//		if(!l_node) return;//exception safety
		if(_size<max_capacity){
			l_node->next=top;
			top=l_node;
			++_size;
		}
		else delete l_node;
	}
	void push(node* l_head, node* l_tail, size_t l_size){//complexity O(1)
//		if(!(l_head&&l_tail&&l_size)) return;//exception safety
		l_tail->next=top;
		top=l_head;
		_size+=l_size;
		if(_size>=max_capacity) release(_size-max_capacity);//remove extra nodes if new size exceeds limit
	}//note: useful when list is destroyed & its' nodes need to transfer at O(1) complexity in GC stack 
	
#if __cplusplus >= 201103L
	template<typename... _T>
	node* pop(_T&&... new_data){//complexity O(1)
#else
	template<typename _T>
	node* pop(const _T& new_data){
#endif
//		if(!top) return nullptr;//exception safety
	    node *popped=top;
    	top=top->next;
    	--_size;
    #if __cplusplus >= 201103L
    	popped->data={std::forward<_T>(new_data)...};
    #else
    	popped->data=new_data;
    #endif
    	popped->next=nullptr;
    	return popped;
	}
	
	void release(size_t n){//complexity O(n)
		for(node* temp;n;--n){
			temp=top->next;
			delete top;
			top=temp;
		}
		_size-=n;
	}
	void release(size_t n, bool){//bound exception safe version
		for(node* temp;n&&top;--n){
			temp=top->next;
			delete top;
			top=temp;
		}
		_size-=n;
	}
	
	void clear(){//complexity O(n)
		node* temp;
		while(top){
			temp=top->next;
			delete top;
    		top=temp;
		}
		_size=0;
	}
	
	~garbage_collector(){ clear(); }//dtor
};

#endif
