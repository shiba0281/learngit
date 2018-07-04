#include "calculate.h"
#include <ncurses.h>
#include "check.h"
#define MAX 100
void print_menu();
void print_5(vector<string>&orders);
void calculator();
int main(){
    char tmp[MAX];
    string str;
    print_menu();
    while(true){
        cin.getline(tmp,MAX);
        str=tmp;
        if(str=="quit"||str=="1"){break;}
        else if(str=="./mycalculator"||str=="0"){calculator();}
        else{
            cout<<"输入错误,请重新输入：";
        }
    }
    return 0;
}
void print_menu(){
    cout<<"-----------------------功能介绍------------------------"<<endl
        <<"0.输入\"./mycalculator\"(或者快捷键0)进入复数计算器界面"<<endl
        <<"1.输入\"quit\"离开(或者快捷键1)"<<endl
        <<"2.其他功能待实现"<<endl
        <<"-------------------------------------------------------"<<endl
        <<"请输入选项：";
}
void print_5(vector<string>&orders){
    int cnt=0;
    for(auto it=orders.end()-1;;it--){
        cout<<cnt<<" : "<<*it<<endl;
        if(++cnt==5||it==orders.begin()){break;}
    }
}
void calculator(){
    vector<string>orders;
    string str;
    char tmp[MAX];
    
    while(true){
        printf("-----------------------------------------------------------\n"
           "请输入你要计算的表达式:");
        cin.getline(tmp,MAX);
        str=tmp;
        if(str=="quit"){
            cout<<"退出程序.\n";
            printf("-----------------------------------------------------------\n"); 
            break;
        }
        int index=orders.size();
        if(str=="print"){
            print_5(orders);
            continue;
        }
        while(str=="front"||str=="behind"){
            if(str=="front"){
                if((--index)<0)
                    cout<<"访问受限！"<<endl;
                else cout<<orders[index]<<endl;
            }
            else if(str=="behind"){
                if((++index)>=(int)orders.size())
                    cout<<"访问受限！"<<endl;
                else cout<<orders[index]<<endl;
            }
            printf("-----------------------------------------------------------\n");
            printf("-----------------------------------------------------------\n"
                 "请输入你要计算的表达式:");
            cin.getline(tmp,MAX);
            str=tmp;
        }
        Check check(str);
        if(check.is_correct()){
            Calculate tmp(str);
            str += "\nresult : ";
            str += tmp.get_result();
        }
        else {
            str += "\nresult : error!";
        }
        orders.push_back(str);
    }
}
