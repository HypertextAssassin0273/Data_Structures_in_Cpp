#include"input_validator.hpp"
#include"Vector.hpp"

void case_1(){
	/* Graphs Representation using Vectors as Adjacency-List */
	Vector<Vector<int>> adjacency_list;
	adjacency_list.reserve(8);//i.e. atleast 8 vertices might be inserted
	int choice,edge;
	while(true){
		Validate_Input(choice,1,4,true,"Select your choice:"
								  "\n1. Add new vertex"
								  "\n2. Add new edge"
								  "\n3. View all vertices alongwith their edges"
								  "\n4. Exit"
								  "\n==> ");
		system("cls");
		switch (choice){
			case 1:
				adjacency_list.push_back(Vector<int>());
				cout<<"new vertex added succesfully!\n";
				break;
			case 2:
				if(adjacency_list.empty()){
					cout<<"Warning: First insert a new vertex!\n";
					break;
				}
				Validate_Input(choice,0,adjacency_list.size()-1,true,"Choose Vertex (0-",adjacency_list.size()-1,"): ");
				Validate_Input(edge,0,adjacency_list.size()-1,false,"Add Edge (0-",adjacency_list.size()-1,"): ");
				for(int i=0;i<adjacency_list[choice].size();++i)
					if(adjacency_list[choice][i]==edge){
						cout<<"Warning: Selected edge is already added to vertex "<<choice<<"!\n";
						break;
					}
				adjacency_list[edge].push_back(choice);
				if(edge!=choice)
					adjacency_list[choice].push_back(edge);
				cout<<"New edge added succesfully to vertex "<<choice<<"!\n";
				break;
			case 3:
				if(adjacency_list.empty())
					cout<<"Empty!\n";
				for(int i=0;i<adjacency_list.size();++i)
					cout<<"Vertex "<<i<<": "<<adjacency_list[i]<<(adjacency_list[i].empty()?"N.i.l\n":"\n");
				break;
			case 4:
				return;
		}
		system("pause");
	}
}

void case_2(){
	/* Graphs Representation using Vectors as Adjacency-Matrix */
	Vector<Vector<bool>> adjacency_matrix;
	adjacency_matrix.reserve(8);//i.e. atleast 8 vertices might be inserted
	int choice,edge;
	while(true){
		Validate_Input(choice,1,4,true,"Select your choice:"
								  "\n1. Add new vertex"
								  "\n2. Add new edge"
								  "\n3. View all vertices alongwith their edges"
								  "\n4. Exit"
								  "\n==> ");
		system("cls");
		switch (choice){
			case 1:
				for(int i=0;i<adjacency_matrix.size();++i)
					adjacency_matrix[i].resize(adjacency_matrix.size()+1);
					adjacency_matrix.push_back(Vector<bool>(adjacency_matrix.size()+1));
				cout<<"new vertex added succesfully!\n";
				break;
			case 2:
				if(adjacency_matrix.empty()){
					cout<<"Warning: First insert a new vertex!\n";
					break;
				}
				Validate_Input(choice,0,adjacency_matrix.size()-1,true,"Choose Vertex (0-",adjacency_matrix.size()-1,"): ");
				Validate_Input(edge,0,adjacency_matrix.size()-1,false,"Add Edge (0-",adjacency_matrix.size()-1,"): ");
				if(adjacency_matrix[edge][choice]){
					cout<<"Warning: Selected edge is already added to vertex "<<choice<<"!\n";
					break;
				}
				adjacency_matrix[edge][choice]=true;
				adjacency_matrix[choice][edge]=true;
				cout<<"New edge added succesfully to vertex "<<choice<<"!\n";
				break;
			case 3:
				if(adjacency_matrix.empty()){
					cout<<"Empty!\n";
					break;
				}
				cout<<"    ";
				for(int i=0;i<adjacency_matrix.size();++i)
					cout<<i<<' ';
				cout<<"\n    ";
				for(int i=0;i<adjacency_matrix.size();++i)
					cout<<"- ";
				cout<<'\n';
				for(int i=0;i<adjacency_matrix.size();++i)
					cout<<i<<" | "<<adjacency_matrix[i]<<'\n';
				cout<<'\n';
				break;
			case 4:
				return;
		}
		system("pause");
	}
}
int main(){
	case_1();//Adjacency-List
//	case_2();//Adjacency-Matrix
	return 0;
}
