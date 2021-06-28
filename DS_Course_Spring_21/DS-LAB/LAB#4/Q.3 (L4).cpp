#include<iostream>
#include<map>
using namespace std;

bool is_matched(string _string,int i,string pattern,int j,map<char,string> &_map){
    int n=_string.size(),m=pattern.size();
    //i.e. base condition
    if (n<m)
        return false;
    //i.e. if both pattern and the string reaches the end
    if (i==n&&j==m)
        return true;
    //i.e. if either string or pattern reaches the end
    if (i==n||j==m)
        return false;
    //i.e. consider the next character from the pattern
    char curr=pattern[j];
    //i.e. if the character is seen before
    if (_map.find(curr)!=_map.end()){
        string s=_map[curr];
        int k=s.size();
        //i.e. return false if the next `k` characters of the given string don't match with `s`
        if (_string.substr(i,k).compare(s))
           return false;
        //i.e. recur for remaining characters if the next `k` characters match
        return is_matched(_string,i+k,pattern,j+1,_map);
    }
    //i.e. process all remaining characters in the string if current character isn't seen before
    for (int k=1;k<=n-i;k++){
        //i.e. insert substring formed by next `k` characters of the string into the map
		_map[curr]=_string.substr(i,k);
		//Alternate: _map.insert(pair<char,string>(curr,_string.substr(i,k)));
        //i.e. check if it leads to the soln.
        if (is_matched(_string,i+k,pattern,j+1,_map))
            return true;
        //i.e. otherwise, backtrack & remove the current character from the map
        _map.erase(curr);
    }
    return false;
}
int main(){
    string _string="codesleepcode",pattern="XYX";
    //i.e. create a map to store mappings b/w the pattern & str
    map<char,string> _map;
    //i.e. checking for soln.
    if (is_matched(_string,0,pattern,0,_map))
    	#if __cplusplus >= 201103L
			for(const auto& it:_map)
            	cout<<it.first<<": "<<it.second<<endl;
        #else
        	//i.e. creating iterator_ptr based obj to map for traversing elements
        	for(map<char,string>::iterator it=_map.begin();it!=_map.end();++it)
            	cout<<it->first<<": "<<it->second<<endl;
        #endif
    else
        cout<<"Solution doesn't exist";
    return 0;
}
