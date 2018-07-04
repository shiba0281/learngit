#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern("(\\d{3}-\\d{8}|\\d{4}-\\d{7}|\\d{3}-\\d{8})");
    regex re(pattern);

    vector<string>str{"010-12345678","0319-9876543","021-123456789"};

    smatch result;

    for(auto tmp : str){
        if(regex_match(tmp,result,re)){
            printf("%s can match\n",tmp.c_str());
        }
        else{
            printf("%s cannot match\n",tmp.c_str());
        }
    }
    
    for(auto tmp : result){
        cout<<tmp<<endl;
    }
    return 0;
}
