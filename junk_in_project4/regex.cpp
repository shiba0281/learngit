#include<iostream>
#include<string>
#include<regex>
using namespace std;
string get_expression(string str);
/*
int main(){
    string str="a+(a+bi)";
    string pattern=R"(\((.+)\))";
    regex re(pattern);
    smatch sm;
    if(regex_search(str,sm,re)){
        for(auto it : sm){
            cout<<it<<'\t';
        }
        cout<<endl;
    }  
    return 0;
}
*/
int main(){
    string str="(a+(+++))";
//    cin>>str;
    cout<<get_expression(str)<<endl;
    return 0;
}
string get_expression(string str){
//    string pattern=R"(\(([^()]+)\))";
    string pattern=R"(\(([^[[()]|[^\+]]]+)\))";
    regex re(pattern);
    smatch sm;
    if(regex_search(str,sm,re)){
        return sm[1];
    }
    else{
        return "";
    }
}
/*
string get_expression(string str){
    // 捕获左右括号之间的
    string pattern=R"(\((.+)\))";
    regex re(pattern);
    smatch sm;
    regex_search(str,sm,re);
    if(sm.size()!=0){
        bool flag=false; // 如果捕获的字符串中没有'('即捕获成功
        for(auto it : sm){
            string tmp=it;
            tmp.erase(tmp.begin());
            if(tmp.find_first_of('(')!=string::npos){
                flag=true;
                break;
            }
        }
        if(flag){
            return get_expression(sm[0]);
        }
    }
    return sm[1];
}
*/
