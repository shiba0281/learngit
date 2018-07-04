#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"(#([^#]+)#)";
    string suffix_exp="#1+2i##3+4i#*";
//    cin>>suffix_exp;
    for(auto it=suffix_exp.begin();it!=suffix_exp.end();it++){
        if(*it=='#'){
            smatch sm;
            regex_search((string::const_iterator)it,suffix_exp.cend(),sm,regex(pattern));
            cout<<sm[1]<<endl;
            suffix_exp=sm.suffix();
            cout<<suffix_exp<<endl;
            it=suffix_exp.begin()-1;
        } 
        // 操作符
        else{
            cout<<"操作符:"<<*it<<endl;
        }
    }
    return 0;
}

