#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    // 定义两个字符串
    string s("(Welcome) (to NanJing) University!"); // 查找的字符串主体
/*    string pattern("NanJing"); // 查找的目标（不需要捕获）
    regex re(pattern); // 使用查找的目标初始化正则表达式
    
    cout<<"this is regex_match test:"; 
    if(regex_match(s,re)){
        cout<<"matched!"<<endl;
    }
    else{
        cout<<"not match!"<<endl;
    }
    
    cout<<"this is regex_search test:"; 
    if(regex_search(s,re)){
        cout<<"matched!"<<endl;
    }
    else{
        cout<<"not match!"<<endl;
    }
 */   
    string pattern=R"(\((.+?)\))";
//    regex re(R"(\((.+?)\))");
    regex re(pattern);
    smatch sm;
    while(regex_search(s,sm,re)){
         for(size_t i = 1; i < sm.size(); ++i){
         cout<<sm[i]<<'\t';
         }
         s=sm.suffix();
    }
    return 0;
}
