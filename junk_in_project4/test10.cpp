#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
/*    string pattern=R"(\(([^\(\)]+)\))";
    string str;
    smatch sm;
    while(true){
        cin>>str;
        if(regex_search(str,sm,regex(pattern))){
            for(auto it : sm){
                cout<<it<<'\t';
            }
            cout<<endl;
        }
    }
*/
    string str;
    while(true){
        cin>>str;
        int flag=1;
        int count=4;
        size_t pos=str.find("arg(")+4;
        for(;pos!=string::npos;pos++){
            if(str[pos]=='('){flag++;}
            else if(str[pos]==')'){flag--;}
            count++;
            if(flag==0){break;}
        }
//        str.replace(str.find("arg("),count,"*");
        cout<<str<<endl;
    }
}
