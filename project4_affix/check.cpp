#include<iostream>
#include "check.h"
#include<regex>
Check::Check(string str){
    exp=str;
    result=true; // 初始化为正确的表达式
//    cout<<"initial:"<<exp<<endl;
    preprocess();
    check_invalid();
    check_mod();
//    cout<<"mod:"<<exp<<endl;
    check_brakets_count();
    check_brakets();
//    check_i();
    check_real();
    //    cout<<"check_brakets:"<<exp<<endl;
    check_operator();
    check_i();
    print_result();
    print_error();
}
bool Check::is_correct(){return result;}
void Check::preprocess(){
    string pattern=R"(\s+)";
    if(regex_search(exp,regex(pattern))){
        for(auto it=exp.begin();it!=exp.end();it++){
            if(*it==' '||*it=='\t'||*it=='\n'||*it=='\r'){
                it=exp.erase(it);
                it--;
                if(it==exp.end()){break;}
            }
        }
    }
}
void Check::check_real(){
    smatch sm;
    if(regex_search(exp,sm,regex(R"(\d*\.\d*\.\d*)"))){
        result=false;
        error.push_back("实数之间不能相邻!");
        list.push_back(make_pair(sm[0].first,sm[0].second));
    }
    for(auto it=exp.begin()+1;it!=exp.end();it++){
        if(*(it-1)>='0'&&*(it-1)<='9'&&*it=='|'){
            int flag=0;
//            cout<<*it<<endl;
            for(auto iter=it;iter!=exp.end();iter++){
//                cout<<"*iter="<<*iter;
                if(*iter=='|'){flag++;}
            }
//            cout<<flag<<endl;
            if(flag%2==0){
                result=false;
                error.push_back("实数不能和模运算相邻!");
                list.push_back(make_pair(it-1,it+1));
            }
        }
    }
    if(regex_search(exp,sm,regex(R"(/0)"))){
        result=false;
        error.push_back("除数不能为0!");
        list.push_back(make_pair(sm[0].first,sm[0].second));
    }
}
void Check::check_invalid(){
    exp=regex_replace(exp,regex(R"(arg\()"),"@@@@");
    exp=regex_replace(exp,regex(R"(cjg\()"),"####");
    string pattern=R"([^\+\-\*\^/\d\.\|\(\)@#i]+)";
    smatch sm;
    if(regex_search(exp,sm,regex(pattern))){
        list.push_back(make_pair(sm[0].first,sm[0].second));
        error.push_back("不合法输入.");
        result=false;
    }
    exp=regex_replace(exp,regex(R"(@{4})"),"arg(");
    exp=regex_replace(exp,regex(R"(#{4})"),"cjg(");
}
void Check::check_i(){
    vector<string>pattern{R"(i{2,})",R"((?:i\(+)+)",R"((?:i\d+(?:\.\d+)?)+)"};
    for(auto it : pattern){
        smatch sm;
        if(regex_search(exp,sm,regex(it))){
            list.push_back(make_pair(sm[0].first,sm[0].second));
            error.push_back("i与其后的内容匹配错误!");
            result=false;
        }
    }
    for(auto it=exp.begin()+1;it!=exp.end();it++){
        if(*(it-1)=='i'&&*it=='|'){
            int flag=0;
            for(auto iter=it;iter!=exp.end();iter++){
                if(*iter=='|'){flag++;}
            }
            if(flag%2==0){
                result=false;
                error.push_back("i不能和模运算相邻!");
                list.push_back(make_pair(it-1,it+1));
            }
        }
    }
    smatch sm;
    exp=regex_replace(exp,regex(R"(arg\()"),"####");
    if(regex_search(exp,sm,regex(R"((?:cjg\([^\(\)i]+i\)i)|(?:\(\d*(?:\.\d+)?[+-]?\d*(?:\.\d+)?i\)i)|(?:\([+-]?\d*(?:\.\d+)?i[+-]\d+(?:\.\d+)?\)i))"))){
        result=false;
        error.push_back("虚数不能和虚数相邻!");
        list.push_back(make_pair(sm[0].first,sm[0].second));
    }
    exp=regex_replace(exp,regex(R"(####)"),"arg(");
}
void Check::check_brakets(){
    vector<string>pattern{R"((?:\(\))+)",R"((?:\)\()+)",R"((?:\([\+\*/]+)+)",R"((?:\)\d+)+)",R"((?:\)\|)+)"};
    for(auto it : pattern){
        smatch sm;
        if(regex_search(exp,sm,regex(it))){
            list.push_back(make_pair(sm[0].first,sm[0].second));
            error.push_back("括号与其后内容匹配错误!");
            result=false;
        }
    }
}
void Check::check_brakets_count(){
    int flag=0;
//    cout<<exp<<endl;
    string::const_iterator iter;
    for(auto it=exp.begin();it!=exp.end();it++){
        if(*it=='('){
            if(flag==0){iter=it;}
            flag++;
        }
        else if(*it==')'){flag--;}
        if(flag<0){
//            iterator_to_pos(make_pair(it,it));
//            cout<<position.top().first<<'\t'<<position.top.second<<endl;
            error.push_back("括号匹配错误!");
            list.push_back(make_pair(it,it+1));
//            cout<<"test1"<<endl;
            result=false;
        }
    }
    if(flag>0){
        for(auto it=iter;it!=exp.end();it++){
            if(*it=='('&&flag>0){
//                iterator_to_pos(make_pair(it,it));
                list.push_back(make_pair(it,it+1));
                error.push_back("左括号多于右括号!");
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
//        iterator_to_pos(make_pair(tmp,tmp));
        error.push_back("取模运算符号匹配错误!");
        result=false;
    }
}
void Check::check_operator(){
    string pattern=R"([\+\-\*/]\))";
    smatch sm;
//    string tmp=exp;
    if(regex_search(exp,sm,regex(pattern))){
        list.push_back(make_pair(sm[0].first,sm[0].second));
//        iterator_to_pos(make_pair(sm[0].first,sm[0].second-1));
        error.push_back("操作符不能和右括号相邻!");
        result=false;
//        exp=sm.suffix();
    }
    pattern=R"([\+\-\*/]{2,})";
//    exp=tmp;
//    cout<<exp<<endl;
    if(regex_search(exp,sm,regex(pattern))){
//        cout<<sm[0]<<endl;
        error.push_back("操作符之间不能相邻!");
        list.push_back(make_pair(sm[0].first,sm[0].second));
//        iterator_to_pos(make_pair(sm[0].first,sm[0].second-1));
        result=false;
//        exp=sm.suffix();
    }
//    exp=tmp;
}
bool Check::is_in_list(string::iterator it){
    for(auto iter : list){
        if(it>=iter.first&&it<iter.second){
//            cout<<"test"<<endl;
            return true;
        }
    }
    return false;
}
void Check::print_error(){
    if(result){return;}
    cout<<"错误类型:"<<endl;
    for(auto it = error.begin();it!=error.end();it++){
        bool flag=false; // 假设之后的内容没有相同的
        for(auto iter=error.begin()+1;iter!=error.end();iter++){
            if(*iter==*it){flag=true;break;}
        }
        if(flag){
            it=error.erase(it);
            it--;
            if(it==error.end()){break;}
        }
    }
    for(auto it : error){
        cout<<'\t'<<it<<endl;
    }
}
void Check::print_result(){
    if(result){return;}
//    cout<<position.size()<<endl;
    for(auto it : position){
        cout<<it.first<<'\t'<<it.second<<endl;
    }
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
