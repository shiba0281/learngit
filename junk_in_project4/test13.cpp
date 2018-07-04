#include<iostream>
#include<string>
using namespace std;
int len(size_t pos,string str);
int main(){
    string str;
    while(true){
        cin>>str;
        if(len(str.find("arg")+3,str)!=1){
        str.replace(str.find("arg("),len(str.find("arg(")+3,str)+3,"*");
        }
        cout<<str<<endl;
    }
    return 0;
}
int len(size_t pos,string str){
    // pos 为左括号的位置
    int len=1;
    int flag=1;
    for(pos++;pos!=string::npos;pos++){
        if(str[pos]=='('){flag++;}
        else if(str[pos]==')'){flag--;}
        len++;
        if(flag==0){break;}
    }
    return len;
}
