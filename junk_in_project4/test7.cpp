#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
    string pattern=R"(\|([^\|]+)\|)";
    string str;
    while(true){
        cin>>str;
        smatch sm;
        regex_search(str,sm,regex(pattern));
/*        for(auto it : sm){
            cout<<it<<'\t';
        }
        cout<<endl;
*/      
        cout<<sm[0]<<endl;
 //       string tmp=sm[0];
        string tmp;
        auto t = sm[0].length();
        auto begin = str.cbegin() + sm.prefix().length()+1;
//        cout<<regex_replace(str,regex(pattern),"*");
        auto x = regex_replace(str,regex(pattern),"*",regex_constants::format_first_only);
        cout<<x<<endl;
//        cout<<str<<endl;
    }
    return 0;
}
