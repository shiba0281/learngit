#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"(arg\(([^\(\)]*(?:\([^\(\)]+\))?[^\(\)]*)+\))";
    string str;
    while(true){
        cin>>str;
        if(regex_match(str,regex(pattern))){cout<<"matched!"<<endl;}
    }
    return 0;
}
