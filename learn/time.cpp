#include<iostream>
#include<ctime>
using namespace std;
int main(){
    clock_t start,end;
    start=clock();
    for(int i=0;i<INT8_MAX;i++);
    end=clock();
    cout<<end-start<<endl;
    return 0;
}
