#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"([\+\-\*/]{2,})";
    string str;
    while(true){
        cin>>str;
        smatch sm;
        if(regex_search(str,sm,regex(pattern))){
            for(auto it : sm){
                 cout<<it<<'\t';
            }
            cout<<endl;
        }
    }
    cout<<"\033[31m"<<"+"<<"\033[0m"<<endl;
    return 0;
}
