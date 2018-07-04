#include<iostream>
#include<cstring>
#define SIZE 8
using namespace std;
void print(int arrary[][SIZE]);
int main(){
    int score[SIZE][SIZE];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            score[i][j]=1;
        }
    }
    int tmp[SIZE][SIZE];
    cout<<"this is score:"<<endl;
    print(score);
    memcpy(tmp,score,sizeof(tmp));
    cout<<"this is tmp:"<<endl;
    print(tmp);
    tmp[4][4]=0;
    cout<<"this is tmp:"<<endl;
    print(tmp);
    cout<<"this is score:"<<endl;
    print(score);
}
void print(int arrary[][SIZE]){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            cout<<arrary[i][j]<<'\t';
        }
        cout<<endl;
    }
}
