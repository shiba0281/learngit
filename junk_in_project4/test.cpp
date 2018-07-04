#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
//    string pattern = R"(\d*\.\d+[+-]\d*i)";
    string pattern=R"(\d*(?=\.)\.[+-]\d*i)";

//    string pattern=R"(\.\d+)";
    while(true){
        string str;
        cin>>str;
        if(regex_match(str,regex(pattern))){
            cout<<"matched!"<<endl;
        }
        else{
            cout<<"not matched!"<<endl;
        }
    }
    return 0;
}
