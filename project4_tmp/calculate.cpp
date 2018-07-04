#include "calculate.h"
#include <regex>
#include "check.h"
char OP[8] = {'^','+','-','*','/','(',')','#'};  //运算符集合
/*
int priority[7][7] =     //各运算符相遇时，优先级比较 1:大于，2:小于，3:等于，0:不可能，错误
{
    { 1, 1, 2, 2, 2, 1, 1 },
    { 1, 1, 2, 2, 2, 1, 1 },
    { 1, 1, 1, 1, 2, 1, 1 },
    { 1, 1, 1, 1, 2, 1, 1 },
    { 2, 2, 2, 2, 2, 3, 0 },
    { 1, 1, 1, 1, 0, 1, 1 },
    { 2, 2, 2, 2, 2, 0, 3 }
};
*/
bool priority[8][8] = 
{
    {0,1,1,1,1,1,0,1},
    {0,0,0,0,0,1,0,1},
    {0,0,0,0,0,1,0,1},
    {0,1,1,0,0,1,0,1},
    {0,1,1,0,0,1,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1},
    {0,0,0,0,0,0,0,1}
};
Calculate::Calculate(string exp){
    is_correct=true;
    exp= preprocess(exp);
//    cout<<"exp = "<<exp<<endl;
    result=recursion(exp);
/*    if(is_correct){
        Complex tmp(result);
        cout<<"运算结果为："<<tmp<<endl;
//        cout<<"after Calculate:"<<recursion(exp)<<endl;
    }
    else{
        result="error!";
        for(auto it : error){
            cout<<'\t'<<it<<endl;
        }
    }
    printf("-----------------------------------------------------------\n");
*/
}
int Calculate::len(size_t pos,string str){
    int rnt=1;
    int flag=1;
    for(pos++;pos!=string::npos;pos++){
        if(str[pos]=='('){flag++;}
        else if(str[pos]==')'){flag--;}
        rnt++;
        if(flag==0){break;}
    }
    return rnt;
}
int Calculate::forward_len(size_t pos,string str){
    int rnt=1;
    int flag=-1;
    for(pos--;pos+1!=0;pos--){
        if(str[pos]=='('){flag++;}
        else if(str[pos]==')'){flag--;}
        rnt++;
        if(flag==0){break;}
    }
    return rnt;
}
string Calculate::preprocess(string str){
    if(str[0]=='-'||str[0]=='+'){
        str="0"+str;
    }
    string pattern=R"(\(-)";
    str=regex_replace(str,regex(pattern),"(0-");
//    pattern=R"(\(+)";
//    str=regex_replace(str,regex(pattern),"(0+");
    str=regex_replace(str,regex(R"(\|i)"),"|*i");
    str=regex_replace(str,regex(R"(\)i)"),")*i");
    return str;
    pattern=R"(([^\d])i)";
    return regex_replace(str,regex(pattern),"$011i");
}
Complex Calculate::compute(Complex &c1,Complex &c2,char op){
    switch(op){
    case '+': return c2+c1;
    case '-': return c2-c1;
    case '*': return c2*c1;
    case '/': return c2/c1;
    case '^': return c2^c1;
    }
    return Complex(0,0);
}
string Calculate::calculate_suffix(string str){
//    cout<<str<<endl;
    while(!_operand.empty()){_operand.pop();}
    while(!_operator.empty()){_operator.pop();}
    string pattern=R"(#([^#]+)#)";
    for(auto it=str.begin();it!=str.end();it++){
        if(*it=='#'){
            smatch sm;
            regex_search((string::const_iterator)it,str.cend(),sm,regex(pattern));
            _operand.push(Complex(sm[1]));
            str=sm.suffix();
            it=str.begin()-1;
        } 
        // 操作符
        else{
            if(_operand.empty()){
                is_correct=false;
                error.push_back("操作数数目缺失!");
                return "";
            }
            Complex c1=_operand.top();
//            cout<<"c1="<<c1<<endl;
            _operand.pop();
            if(_operand.empty()){
                is_correct=false;
                error.push_back("操作数数目缺失!");
                return "";
            }
            Complex c2=_operand.top();
//            cout<<"c2="<<c2<<endl;
            _operand.pop();
            // 幂运算的虚部不为0
            if(*it=='^'&&c1.image!=0){
                is_correct=false;
                error.push_back("幂运算的右操作数不能是虚数!");
                return "";
            }
            if(*it=='/'&&c1.real==0&&c1.image==0){
                is_correct=false;
                error.push_back("除法运算的右操作数不能是0!");
                return "";
            }
            _operand.push(compute(c1,c2,*it));
        }
    }
    if(_operand.size()>2){
        is_correct=false;
        error.push_back("操作符数目缺失!");
        cout<<"test1"<<endl;
        return "";
    }
    else if(_operand.size()==2){
//        Complex c1(_operand.top());
//        Complex c2(_operand.top());
        Complex c1(_operand.top());
        if(c1.real!=0||c1.image!=1){
//            cout<<c1<<endl;
//            cout<<"test2"<<endl;
            error.push_back("操作符数目缺失!");
//            cout<<"test"<<endl;
            is_correct=false;
            return "";
        }
        _operand.pop();
        Complex c2(_operand.top());
        _operand.pop();
        if(c2.image!=0){
            is_correct=false;
            error.push_back("虚数的前面不能是虚数!");
            return "";
        }        
        _operand.push(compute(c1,c2,'*'));
    }
    return _operand.top().complex_to_str();
}
bool Calculate::is_complex(string exp){
    string pattern=R"((?:[-]?\d+(?:\.\d+)?i)|(?:[-]?\d+(?:\.\d+)?(?:[+-]\d+(?:\.\d+)?i)?))";
    if(regex_match(exp,regex(pattern))){
        return true;
    }
    return false;
}
string Calculate::recursion(string exp){
    // 伪代码：
    //  是最简单的复数形式，直接返回
    //  匹配绝对值成功，对之间的内容调用递归函数
    //      用得到的结果初始化复数对象，转换成字符串，替换
    //  匹配cjg成功，对之间的内容调用递归函数
    //      用得到的结果初始化复数对象，进行替换
//    cout<<"exp = "<<exp<<endl;
    Complex c;
    smatch sm;
    Check check(exp);
    // 运算过程中出现错误
    if(!check.is_correct()){
        is_correct=false;
    }
    if(!is_correct){
        return "";
    }
    string pattern1=R"(\|([^\|]+)\|)"; // 绝对值
    if(regex_search(exp,sm,regex(pattern1))){
        Complex tmp(recursion(sm[1]));
        return recursion(regex_replace(exp,regex(pattern1),c.mod(tmp).complex_to_str(),regex_constants::format_first_only));
    }
    else if(regex_search(exp,regex(R"(dis\()"))){
       size_t pos=exp.find("dis(")+3;
       int length=len(pos,exp);
       string tmp=exp.substr(pos+1,length-2);
       smatch sm;
       regex_match(tmp,sm,regex(R"(([^,]+),([^,]+))"));
            Complex c1(recursion(sm[1]));
            Complex c2(recursion(sm[2]));
            return recursion(exp.replace(exp.find("dis("),length+3,c.dis(c1,c2).complex_to_str()));
    }
    else if(regex_search(exp,regex(R"(arg\()"))){
        size_t pos=exp.find("arg(")+3;
        int length=len(pos,exp);
        Complex tmp(recursion(exp.substr(pos+1,length-2)));
        if(tmp.real==0&&tmp.image==0){
            error.push_back("不能对0取俯角!");
            is_correct=false;
            return "";
        }
        return recursion(exp.replace(exp.find("arg("),length+3,c.arg(tmp).complex_to_str()));
    }
    else if(regex_search(exp,regex(R"(cjg\()"))){
        size_t pos=exp.find("cjg(")+3;
        int length=len(pos,exp);
        Complex tmp(recursion(exp.substr(pos+1,length-2)));
        return recursion(exp.replace(exp.find("cjg("),length+3,"("+c.cjg(tmp).complex_to_str()+")"));
    }
    else{
//        cout<<exp<<endl;
        
//        exp=regex_replace(exp,regex(R"(([^\d])i)"),"$011i");
        return calculate_suffix(nifix_to_suffix(exp));
    }
}
void Calculate::print_result(){
    result=recursion(nifix_exp);
    cout<<"the result is "<<result<<endl;
}
bool Calculate::isOpat(char c)   //是否是OP[]中的操作符
{
    for (int i = 0; i < 8; i++)
    {
        if (c == OP[i])
            return true;
    }
    return false;
}
int Calculate::getPriority(char c1,char c2)  //比较优先级
{
    int i, j;
    for (int r = 0; r < 8; r++)
    {
        if (c1 == OP[r])
            i = r;
        if (c2 == OP[r])
            j = r;
    }
    return priority[i][j];
}
string Calculate::nifix_to_suffix(string str){
    // 伪代码：
    // 遍历中缀表达式
    // 如果是操作数
    //  直接输出到suffix
    // 如果是右括号
    //  连续出栈直到左括号，左括号不输出
    // 如果是其他操作符
    //  和栈顶操作符比较大小
    //      如果优先级高于栈顶优先级
    //          入站
    //      否则
    //          出栈操作符直到栈顶优先级低
    str+='#';
    string rnt;
    _operator.push('#');
    for(auto it=str.begin();it!=str.end();it++){
        if((*it>='0'&&*it<='9')||*it=='i'){
            string pattern=R"((?:\d*(?:\.\d+)?i)|(?:\d+(?:\.\d+)?))";
//            string pattern=R"((?:\d+(?:\.\d+)?i)|(?:\d+(?:\.\d+)?(?:[+-]\d+(?:\.\d+)?i)?))";
            smatch sm;
            regex_search((string::const_iterator)it,str.cend(),sm,regex(pattern));
            string tmp="#";
            tmp+=sm[0];
//            cout<<str<<endl;
            tmp+="#";
            rnt+=tmp;
//            cout<<"test"<<endl;
//            cout<<sm[0]<<endl;
            str=sm.suffix();
            it=str.begin()-1;
        }
        else if(isOpat(*it)){
            if(*it=='('){
                _operator.push(*it);
                // 判断之后是不是一个负数
                
            }
            else if(*it==')'){
                while(_operator.top()!='('){
                    rnt+=_operator.top();
                    _operator.pop();
                }
                _operator.pop();
            }
            else if(getPriority(*it,_operator.top())){
                _operator.push(*it);
            }
            else if(!getPriority(*it,_operator.top())){
                while(!getPriority(*it,_operator.top())){
                    rnt+=_operator.top();
                    _operator.pop();
                }
                _operator.push(*it);
            }
            else if(*it=='#'){
                while(_operator.top()!='#'){
                    rnt+=_operator.top();
                    _operator.pop();
                }
            }
        }

    }
    return rnt;
}
