#include "calculate.h"
#include "check.h"
#include "matrix.h"
#include "equation.h"
#include <readline/readline.h>
#include <readline/history.h>
#define MAX 100
void print_menu();
bool print_5(vector<string>&orders);
void calculator();
int main(){
    char tmp[MAX];
    string str;
    while(true){
       print_menu();
        cin.getline(tmp,MAX);
        str=tmp;
        if(str=="quit"||str=="1"){break;}
        else if(str=="matrix"||str=="2"){
            vector<string> input;   
            string str;
            cout<<"请输入虚数行列式，输入“#”结束:\n";
            cin>>str;
            while(str!="#"){
            input.push_back(str);
            cin>>str;
            }
            while(getchar()!='\n');
            matrix m(input);
            if(m.get_order()){
                m.print_matrix();
                cout<<"the result of the matrix is "<<m.get_result()<<endl;
            }
        }
        else if(str=="equation"||str=="3"){
            equation();
        }
        else if(str=="./mycalculator"||str=="0"){
            calculator();
        }
        else{
            cout<<"输入错误!\n";
        }
    }
    return 0;
}
void print_menu(){
    cout<<"-----------------------功能介绍------------------------"<<endl
        <<"0.输入\"./mycalculator\"(或者快捷键0)进入复数计算器界面"<<endl
        <<"1.输入\"quit\"离开(或者快捷键1)"<<endl
        <<"2.输入\"matrix\"计算虚数行列式的值(或者快捷键2)"<<endl
        <<"3.输入\"equation\"计算线性方程组(或者快捷键3)"<<endl
        <<"4.其他功能待实现"<<endl
        <<"-------------------------------------------------------"<<endl
        <<"请输入选项：";
}
bool print_5(vector<string>&orders){
    if(orders.size()==0){
        cout<<"没有之前输入的表达式记录！"<<endl;
        return false;
    }
    cout<<"已进入快捷输入模式，你可以通过选择历史表达式的编号"<<endl
        <<"直接将表达式添加到下一个要计算的表达式的开头"<<endl
        <<"或者输入任意键退出快捷输入模式"<<endl;
    int cnt=0;
    for(auto it=orders.end()-1;;it--){
        cout<<cnt<<" : "<<*it<<endl;
        if(++cnt==5||it==orders.begin()){break;}
    }
    return true;
}
void calculator(){
    vector<string>orders;
    string str;
//    char tmp[MAX];
    
    while(true){
        char *tmp=readline("----------------------------------------------------------\n请输入你要计算的表达式：");
        if(*tmp){
            add_history(tmp);
        }
        if(tmp[0]=='\0'){
            cout<<"输入错误！"<<endl;
            continue;
        }
        str=tmp;
        if(str=="quit"){
            cout<<"退出程序.\n";
            printf("-----------------------------------------------------------\n"); 
            break;
        }
        int index=orders.size();
        if(str=="print"){
            if(!print_5(orders)){continue;}
            cout<<"请输入编号或者其他任意键：";
            int flag;
            cin>>flag;
            while(getchar()!='\n');
            if(flag>=0&&flag<=4){
                str=orders[orders.size()-1-flag];
                str=str.substr(0,str.find("result"));
                printf("----------------------------------------------------------\n"
                     "请输入你要计算的表达式:");
//                cin>>tmp;
                for(auto it : str){
                    if(it!='\n'&&it!='\t'&&it!=' '){
                        cout<<it;
                    }
                }
                cin.getline(tmp,MAX);
                str+=tmp;
                Check check(str);
                if(check.is_correct()){
                Calculate tmp(str);
                if(tmp.is_correct){
                     Complex c(tmp.result);
                     cout<<"运算结果为："<<c<<endl;
//        cout<<"after Calculate:"<<recursion(exp)<<endl;
                }
                else{
                    tmp.result="error!";
                    for(auto it : tmp.error){
                        cout<<'\t'<<it<<endl;
                    }
                }
                 printf("-----------------------------------------------------------\n");
                str += "\nresult : ";
                str += tmp.get_result();
                }
                 else {
                    str += "\nresult : error!";
                 }
                orders.push_back(str);
            }
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
            if(tmp.is_correct){
               Complex c(tmp.result);
               cout<<"运算结果为："<<c<<endl;
            }
            else{
               tmp.result="error!";
               for(auto it : tmp.error){
                    cout<<'\t'<<it<<endl;
               }
            }
            printf("-----------------------------------------------------------\n");
            str += "\nresult : ";
            str += tmp.get_result();
        }
        else {
            str += "\nresult : error!";
        }
        orders.push_back(str);
        rl_free(tmp);
    }
}
