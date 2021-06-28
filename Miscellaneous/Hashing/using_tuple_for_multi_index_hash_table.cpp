#include<iostream>
#include<algorithm>
#include<map> //tree
#include<unordered_map> //hash-table
#include<tuple> 
using namespace std;

typedef tuple<int,char,double> type;

namespace std{ 
    template <>
    struct hash<type>{
        auto operator()(const type& t)const->size_t{ return hash<int>{}(get<0>(t)*get<1>(t)); }
    };
}

bool operator==(const type& lhs,const type& rhs){ return (get<0>(lhs)*get<1>(lhs))==(get<0>(rhs)*get<1>(rhs)); }

tuple<string,int> getNameAge(){ return make_tuple("rosemary",17); }
 
int main(){
    auto p1=make_pair(8,"appricot");
    cout<<"p1.first -> "<<p1.first<<" & p2.first -> "<<p1.second<<'\n';

    auto t1=make_tuple(17,"cherry",'c');    
    cout<<"1st element: "<<get<0>(t1)<<'\n'
    	<<"2nd element: "<<get<1>(t1)<<'\n' 
    	<<"3rd element: "<<get<2>(t1)<<'\n';
    
    auto name=string{}; auto age=int{}; //string name; int age;
    tie(name,age)=getNameAge();
    cout<<"\nName: "<<name<<" age: "<<age<<'\n';
    
    auto t2=make_tuple(1,2,3),t3=make_tuple(4,5,6); //make_tuple can be replaced with tuple<int,int,int>
    cout<<(t2<t3?"\nt2 < t3\n":"\nt2 >= t3\n");
    
    auto m1=map<type,string>{};
    m1[make_tuple(17,'f',7.864)]="Faith will move mountains.";
    
    auto m2=unordered_map<type,string>{};
    m2[make_tuple(17,'f',7.864)]="Faith will move mountains.";
    
    int a=1,b=2,c=3;
    tie(b,c,a)=make_tuple(a,b,c); 
 
    return 0;
}
