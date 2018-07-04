#include<iostream>
#include<string>
using namespace std;


int get_pos(size_t pos,string exp){
    int rnt=0;
    int flag=1;
    for(size_t i=pos+1;i!=string::npos;i++){
        if(exp[i]=='('){flag++;}
        else if(exp[i]==')'){flag--;}
        rnt++;
        if(flag==0){return rnt;}
    }
    return rnt;
}
int main(){
    string str;
    while(true){
        cin>>str;
        str.replace(str.find("arg("),get_pos(str.find("arg(")+3,str),"*");
        cout<<str<<endl;
    }
}
