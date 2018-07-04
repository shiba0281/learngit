#include<algorithm>
#include<functional>
#include<array>
#include<iostream>

int main(){
    //  定义一个array对象
    std::array<int,10>s={5,3,3,5,6,7,7};
    //  用默认的sort排序
    std::sort(s.begin(),s.end());
    //  遍历数组
    for(auto a : s){
        std::cout<<a<<" ";
    }
    std::cout<<'\n';
    //  用自定义函数对象排序
    struct{
        bool operator()(int a,int b)const{
            return a>b;
        }
    }customLess;
    std::sort(s.begin(),s.end(),customLess);
    for(auto a:s){
        std::cout<<a<<" ";
    }
    std::cout<<'\n';
    return 0;
}
