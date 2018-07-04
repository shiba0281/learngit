#include<iostream>
#include<string>
#include<regex>
using namespace std;
int main(){
            string str;
            while(true){
            cin>>str;
            string pattern=R"((\d+(?:\.\d+)?i)|(?:\d+(?:\.\d+)?(?:[+-]\d+(?:\.\d+)?i)?))";
            //string pattern=R"(\d+(?:\.\d+)?i)";
            smatch sm;
            regex_search(str,sm,regex(pattern));
            for (auto&& x : sm) {
                cout << x << endl;
            }
            //cout<<sm[1]<<endl;
            }
            return 0;
}
