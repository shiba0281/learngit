#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string str;
    while(true){
        cin>>str;
        str=regex_replace(str,regex(R"(arg\()"),"@@@@");
        cout<<str<<endl;
    }
    return 0;
}
