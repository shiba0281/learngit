#include<iostream>
#include<array>
#include<algorithm>
using namespace std;
int main(){
    array<int,3>a={1,3,};
    // 使用迭代器进行访问
    for(auto it:a){
        cout<<it<<"\t";
    }
    cout<<endl;
    sort(a.begin(),a.end());
    for(auto it:a){
        cout<<it<<'\t';
    }
    cout<<endl;
    cout<<"size = "<<a.size()<<endl
        <<"max_size = "<<a.max_size()<<endl;
    return 0;
}
