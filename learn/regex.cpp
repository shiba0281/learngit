#include<iostream>
#include<regex>
using namespace std;
int main(){
    string str="HELLO_2018";
    smatch result;
    regex pattern("(.{5})_(\\d{4})");
    if(regex_match(str,result,pattern)){
        cout<<result[0]<<endl
            <<result[1]<<endl
            <<result[2]<<endl;
    }
    return 0;
}
