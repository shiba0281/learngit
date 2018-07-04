#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"(([^\d])i)";
    string str;
    while(true){
        cin>>str;
        
        str=regex_replace(str,regex(pattern),"$011i");
        cout<<str<<endl;
    }
    cout<<str<<endl;
}
