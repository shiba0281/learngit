#include<iostream>
#define MAX 100
using namespace std;
int main(){
    char tmp[MAX];
    while(true){
        cin.getline(tmp,MAX);
        if(tmp[0]=='\0'){cout<<"test";}
        cout<<"test1"<<endl;
    }
    return 0;
}
