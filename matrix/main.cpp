#include<iostream>
#include "matrix.h"
#include<string>
#define MAX 100
using namespace std;
int main(){
    string s[MAX][MAX];
    for(int i=0;i<MAX;i++){
        for(int j=0;j<MAX;j++){
            s[i][j]="#";
        }
    }
    while(true){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                cin>>s[i][j];
            }
        }
        matrix m(s);
    }
/*  
    string str;
    while(true){
        cin>>str;
        cout<<stod(str)<<endl;
    }
*/
    return 0;
}
