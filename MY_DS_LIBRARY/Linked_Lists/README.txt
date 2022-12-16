NOTE: you can also perform cross class as well as cross object operations,
      but cross node type isn't possible without type convertor.

1) Singly Linked List (SLL) Node Transfer:-
pushing node from Forward_List (FL) to Circular_Forward_List (CFL):
e.g. CFL.push_back(FL.pop_back(true));
e.g. CFL.push_front(FL.pop_back(true));
e.g. CFL.push_back(FL.pop_middle(true));
e.g. CFL.push_middle(FL.pop_middle(true));
e.g. CFL.push_middle(FL.erase([any_index], true));

and, ofcourse its vice-versa is also possible (if return_node overloads are present):
e.g. FL.push_back(CFL.pop_back(true));
e.g. FL.push_front(CFL.pop_back(true));
e.g. FL.push_back(CFL.pop_middle(true));
e.g. FL.push_middle(CFL.pop_middle(true));
e.g. FL.insert([any_index], CFL.pop_back(true));

cross object transfer:
e.g. FL.push_front(FL.pop_back(true));
e.g. CFL.push_front(CFL.pop_back(true));

2) Doubly Linked List (DLL) Node Transfer:-
similarly, pushing node from List (L) to Circular_List (FL):
e.g. CL.push_back(L.pop_back(true));
e.g. CL.push_front(L.pop_back(true));
e.g. CL.push_back(L.pop_middle(true));
e.g. CL.push_middle(L.pop_middle(true));
e.g. CL.push_middle(L.erase([any_index], true));

and, ofcourse its vice-versa is also possible (if return_node overloads are present):
e.g. L.push_back(CL.pop_back(true));
e.g. L.push_front(CL.pop_back(true));
e.g. L.push_back(CL.pop_middle(true));
e.g. L.push_middle(CL.pop_middle(true));
e.g. L.insert([any_index], CL.pop_back(true));

cross object transfer:
e.g. L.push_front(L.pop_back(true));
e.g. CL.push_front(CL.pop_back(true));
