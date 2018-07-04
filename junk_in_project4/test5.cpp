#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string exp;
    while(true){
        cin>>exp;
    //    string pattern=R"((?:\d+(?:\.\d+)?i)|(?:\d+(?:\.\d+)?(?:[+-]\d+(?:\.\d+i)?)";
        string pattern=R"((?:\d+(?:\.\d+)?i)|(?:\d+(?:\.\d+)?(?:[+-]\d+(?:\.\d+)?i)?))";
//    string pattern=R"(\d+)";
        if(regex_match(exp,regex(pattern))){
        cout<<"matched!"<<endl;
    }
        else{
    cout<<"not matched!"<<endl;
    }
    }
        return 0;
}
