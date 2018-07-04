#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"(--)";
    string str;
    smatch sm;
    while(true){
        cin>>str;
        if(regex_search(str,sm,regex(pattern))){
            for(auto it=str.begin();it!=str.end();it++){
                if(it>=sm[0].first&&it<sm[0].second){
                    cout<<"\033[31m"<<*it<<"\033[0m";
                }
                else{
                    cout<<*it;
                }
            }
        }
        cout<<endl;
    }
}
