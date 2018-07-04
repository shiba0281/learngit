#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"((?!(?:arg\()).*)";
    string str;
    smatch sm;
    while(true){
        cin>>str;
        if(regex_search(str,sm,regex(pattern))){
            for(auto it : sm){
                cout<<it<<'\t';
            }
            cout<<endl;
        }
    }
}
