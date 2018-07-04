#ifndef CHECK_H 
#define CHECK_H
#include<string>
#include<vector>
using namespace std;
class Check{
    string exp; // 需要检查的表达式
    vector<pair<string::const_iterator,string::const_iterator>> list;
    bool result;
public:
    Check(string str);
    bool is_correct(); // 返回结果
    bool is_in_list(string::iterator it); // 判断是否在list里面 
    void check_brakets(); // 检查括号
    void check_mod();   // 检查摸
    void check_operator(); // 检查操作符
    void check_real(); // 检查实数
    void check_i(); // 检查i
    void print_result();
};
#endif
