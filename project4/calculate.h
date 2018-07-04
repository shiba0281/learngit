#ifndef CALCULATE_H
#define CALCULATE_H
#include<string>
#include "complex.h"
using namespace std;
class calculate{
    string expression;
public:
    calculate(string expression);
    string get_result(); // 返回表达式的计算结果
    // 计算两个简单复数的运算
//    string binary_oporation(string exp1,string exp2,char oper); // 计算两个复数的二元运算
    Complex str_to_complex(string str); // 把string转换为complex类型
    string complex_to_str(const Complex &c); // 把complex转换为string类型
//    string calculate_in_order(string str); // 按照顺序进行计算（括号，模运算，arg,cjg)
//    string preproccess(string str); // 消除arg,cjg,模运算和括号
};
#endif
