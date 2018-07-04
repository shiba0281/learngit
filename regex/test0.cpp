#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string s="hello everyone, it's an awesome morning, right?";
    regex self_regex("EVERYONE",regex_constants::icase);
    if(regex_search(s,self_regex)){
        cout<<"matched!"<<endl;
    }
    regex word_regex("(\\S+)");
    
}
