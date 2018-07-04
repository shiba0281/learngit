#include "equation.h"
#include "matrix.h"
equation::equation(){
    // 用户输入线性方程组
    cout<<"请输入你要计算的线性方程组(以“#”结束):\n";
    string str;
    cin>>str;
    while(str!="#"){
        input.push_back(str);
        cin>>str;
    }
    while(getchar()!='\n');
    get_variable();
    preprocess();
    get_data();
    process();
    is_correct=true;
    if(variable.size()!=input.size()){is_correct=false;}
    calculate();
    if(is_correct){
        for(int i=0;i<(int)variable.size();i++){
            cout<<variable[i]<<"="<<result[i]<<endl;
        }
    }
    else{
        cout<<"你输入的行列式有误！"<<endl;
    }
}
void equation::calculate(){
    // 计算分母
    Complex denominator=matrix(trans(data)).get_result();
    if(denominator.real==0&&denominator.image==0){
        is_correct=false;
        return;
    }
    for(int i=0;i<(int)variable.size();i++){
        string s[SIZE][SIZE];
        for(int j=0;j<(int)variable.size();j++){
            for(int k=0;k<(int)variable.size();k++){
                if(k==i){s[j][k]=data[j][variable.size()];}
                else{s[j][k]=data[j][k];}
            }
        }
        Complex numerator=matrix(trans(s)).get_result();
        Complex c=numerator/denominator;
        result.push_back(c.complex_to_str());
    }
}
vector<string> equation::trans(string s[][SIZE]){
    vector<string> rnt;
    for(int i=0;i<(int)variable.size();i++){
        for(int j=0;j<(int)variable.size();j++){
            rnt.push_back(s[i][j]);
        }
    }
    return rnt;
}
void equation::preprocess(){
    // 处理开头
    for(auto &it : input){
        if(regex_match(it.substr(0,1),regex(R"([^\+\-\*/\(\)\.\d\^\|,=argcjdis])"))){
            it="1"+it;
        }
    }
    string pattern=R"(([+-])([^\+\-\*/\(\)\.\d\^\|,=argcjdis]))";
    for(auto &it : input){
        while(regex_search(it,regex(pattern))){
            it=regex_replace(it,regex(pattern),"$011$02");
        }
    }
}
// 获取系数表
void equation::get_data(){
    // 初始化data
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            data[i][j]="#";
        }
    }
    // 对于每一个表达式来进行析取
    string pattern=R"(([\+\-\*/\(\)\.\d\^\|,=argcjdis]+)(.))";
    int index=0;
    for(auto it : input){
        string tmp=it;
        smatch sm;
        while(regex_search(tmp,sm,regex(pattern))){
            for(size_t i=0;i<variable.size();i++){
                if(variable[i]==sm[2]){
                    data[index][i]=sm[1];
                }
            }
            tmp=sm.suffix();
        }
        // 等号后边的部分
        if(regex_search(it,sm,regex(R"(=(.+))"))){
            data[index][variable.size()]=sm[1];
        }
        index++;
    }
}
// 获取变量表
void equation::process(){
    for(int i=0;i<(int)variable.size();i++){
        for(int j=0;j<(int)variable.size()+1;j++){
            if(data[i][j]=="#"){data[i][j]="0";}
            else if(data[i][j][0]=='+'){data[i][j].erase(data[i][j].begin());}
        }
    }
}
void equation::get_variable(){
    string pattern=R"([^\+\-\*/\(\)\.\d\^\|,=argcjdis])";
    for(auto it : input){
        string tmp=it;
        smatch sm;
        while(regex_search(tmp,sm,regex(pattern))){
            bool flag=false;
            for(auto iter : variable){
                if(iter==sm[0]){
                    flag=true;
                    break;
                }
            }
            if(!flag){variable.push_back(sm[0]);}
            tmp=sm.suffix();
        }
    }
}
