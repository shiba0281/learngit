#ifndef CALCULATE_H
#define CALCULATE_H
#include "complex.h"
#include <stack>
#include <vector>
class Calculate{
    string nifix_exp; // 前缀表达式
    string suffix_exp;  // 后缀表达式
    string result; // 返回计算结果
    stack<Complex> _operand; // 操作数栈
    stack<char> _operator; // 操作符栈
    vector<char> operators; // 定义操作付（优先级由顺序决定）
    bool is_correct; // 检查是否出错
    vector<string> error; // 错误类型
public:
    Calculate(string exp);
    bool isOpat(char c); 
    int getPriority(char c1,char c2); // 判断c1是否大于c2
    Complex compute(Complex &c1,Complex &c2,char op);
    string nifix_to_suffix(string str); // 中缀表达式转后缀表达式
    string calculate_suffix(string str);    // 计算后缀表达式
    string recursion(string exp);   // 递归计算表达式
    void print_result();
    string preprocess(string str); // 预处理，修改系数
    bool is_complex(string exp);
    int len(size_t pos,string str); // 求两个匹配括号之间的距离
    int forward_len(size_t pos,string str); // 求右括弧与其匹配的左括弧之间的距离
    string get_result(){return result;}
    // 判断操作符的正确性
    // 比较两个操作符优先级
    // 计算两个复数的运算
    // 中缀表达式转换为后缀表达式（逆波兰式） 
    // 返回计算的结果
};
#endif
