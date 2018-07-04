#include<iostream>
#include<string>
#include<vector>
using namespace std;

int main(){
    vector<string>str;
    string tmp;
    cin>>tmp;
    while(tmp!="#"){
        str.push_back(tmp);
        cin>>tmp;
    }
    //  使用auto自动推导数据类型,此处为vector<string>::iterator
    //  此外,多使用auto来推导迭代器类型
    for(auto a : str){
        cout<<a<<'\t';
    }    
    cout<<endl;
    
    return 0;
}

