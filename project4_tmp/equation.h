#ifndef EQUATION_H
#define EQUATION_H
#define SIZE 100
#include<vector>
#include<string>
#include<regex>
#include "complex.h"
class equation{
    vector<string> input;   // 用户输入
    vector<string> variable;    // 变量表
    string data[SIZE][SIZE]; // 存储系数，和变量表一一对应
    vector<string> result; // 保存结果:
    bool is_correct; // 输入的正确性
public:
    equation();
    void calculate(); // 计算
    void preprocess(); // 预处理，恢复省略的1
    void process(); // 再进行处理
    void get_variable();
    void get_data();
    vector<string> trans(string s[][SIZE]); // 二维数组转换为一维数组
};
#endif
