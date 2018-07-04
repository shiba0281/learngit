#include<iostream>
#include<string>
#include<regex>
#define MAX 100
using namespace std;
int main(){
    string pattern=R"(\s+)";
    string str;
    char tmp[MAX];
    while(true){
        cin.getline(tmp,MAX);
        str=tmp;
        if(regex_search(str,regex(pattern))){
//            cout<<"test"<<endl;
            for(auto it=str.begin();it!=str.end();it++){
                if(*it==' '||*it=='\t'||*it=='\n'||*it=='\r'){
                    it=str.erase(it);
                    it--;
                    if(it==str.end()){break;}
            }
        }}
        cout<<str<<endl;
    }
    return 0;
}
