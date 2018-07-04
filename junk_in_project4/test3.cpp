#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string str;
    double real,image;
    while(true){
    cin>>str;
    string pattern=R"((\d+(?:\.\d+)?)i)";
    smatch sm;
    if( regex_match(str,sm,regex(pattern))){
        real=0;
        image=stod(sm[1]);
    }
    pattern=R"((\d+(?:\.\d+)?)(?:([+-]\d+(?:\.\d+)?)i)?)";
    if(regex_match(str,sm,regex(pattern))){
        real=stod(sm[1]);
        image=stod(sm[2]);
    }
    cout<<"real="<<real<<",image="<<image<<endl;
    }
    return 0;
}
