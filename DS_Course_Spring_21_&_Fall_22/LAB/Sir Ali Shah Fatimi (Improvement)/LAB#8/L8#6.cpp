#include "D_Stack.hpp"
using namespace std;

void UNDO(D_Stack<char>& Undo, D_Stack<char>& Redo){
	Redo.push(Undo.pop(true));
}

void REDO(D_Stack<char>& Undo, D_Stack<char>& Redo){
	Undo.push(Redo.pop(true));
}

void READ(D_Stack<char>& Undo){
	D_Stack<char> revOrder;
	while(!Undo.empty())
		revOrder.push(Undo.pop(true));
	
	while(!revOrder.empty()){//Traverse Undo stack in ascending order
		cout<<revOrder.front();
		Undo.push(revOrder.pop(true));
	}
	cout<<'\n';
}

void WRITE(D_Stack<char>& Undo, char X){ Undo.push(X); }

template<size_t N>
void QUERY(const char* (&&Q)[N]){
	D_Stack<char> Undo,//Stores the history of all the queries that have been processed on the document
				  Redo;//Stores the elements of REDO query
	
	for(const auto& iter:Q){//Traverse all the query
		if(iter=="UNDO")
			UNDO(Undo, Redo);
		else if(iter=="REDO")
			REDO(Undo, Redo);
		else if(iter=="READ")
			READ(Undo);
		else
			WRITE(Undo, iter[6]);
	}
}

int main(){
	QUERY({"WRITE A", "WRITE B", "WRITE C", "UNDO", "READ", "REDO", "READ"});
	
	return 0;
}

