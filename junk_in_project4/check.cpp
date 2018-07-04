#include<iostream>
#include "check.h"
#include<regex>
int main(){
    string str;
    while(true){
        cin>>str;
        Check tmp(str);
    }
    return 0;
}
Check::Check(string str){
    exp=str;
    result=true; // 初始化为正确的表达式
    check_mod();
    check_brakets();
    check_operator();
    print_result();
}
void Check::check_brakets(){
    int flag=0;
    string::const_iterator iter;
    for(auto it=exp.begin();it!=exp.end();it++){
        if(*it=='('){
            if(flag==0){iter=it;}
            flag++;
        }
        else if(*it==')'){flag--;}
        if(flag<0){
            list.push_back(make_pair(it,it+1));
            result=false;
        }
    }
    if(flag>0){
        for(auto it=iter;it!=exp.end();it++){
            if(*it=='('&&flag>0){
                list.push_back(make_pair(it,it+1));
                result=false;
                flag--;
            }
        }
    }
}
void Check::check_mod(){
    int count=0;
    string::iterator tmp;
    for(auto it=exp.begin();it!=exp.end();it++){
        if(*it=='|'){
            count++;
            tmp=it;
        }
    }
    if(count%2!=0){
        list.push_back(make_pair(tmp,tmp+1));
        result=false;
    }
}
void Check::check_operator(){
//    string pattern=R"((?:[+-*/]\))|(?:[+-*/]{2,}))";
    regex pattern(R"([\+\-\*/]\))");
    smatch sm;
    string tmp=exp;
    cout<<tmp<<endl;
    if(regex_search(tmp,sm,pattern)){
        cout<<"test"<<endl;
        list.push_back(make_pair(sm[0].first,sm[0].second));
        result=false;
//        tmp=sm.suffix();
    }
}
bool Check::is_in_list(string::iterator it){
    for(auto iter : list){
        if(it>=iter.first&&it<iter.second){
            return true;
        }
    }
    return false;
}
void Check::print_result(){
    if(result){return;}
    for(auto it=exp.begin();it!=exp.end();it++){
        if(is_in_list(it)){
            cout<<"\033[31m"<<*it<<"\033[0m";
        }
        else{
            cout<<*it;
        }
    }
    cout<<endl;
}
