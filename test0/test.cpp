#include<iostream>
#include<string>
#include<regex>
using namespace std;
string add_1(string str);
string get(string str);
int main(){
    string input;
//    string pattern=R"((?!\d)i)";
    cin>>input;
    cout<<get(input)<<endl;
    return 0;
}
string add_1(string str){
    string pattern=R"(([^\d])i)";
    return regex_replace(str,regex(pattern),"$011i");
}
string get(string str){
    string pattern=R"((\d+(?:\.\d+)?[+-]?\d*(?:\.\d+)?i?))";
    smatch sm;
    regex_search(str,sm,regex(pattern));
    str=sm.suffix();
    cout<<"str="<<str<<endl;
    return sm[1];  
}
