#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string s = "this expression could match from A and beyond";
    string rs = "exp\\w*";  //  正则字符串
    cout<<s<<endl;
    regex expression(rs);   //  建立正则表达式
    if(regex_match(s,expression)){
        cout<<"can match"<<endl;
    }
    else{
        cout<<"cann't match!"<<endl;
    }
    return 0;
}
