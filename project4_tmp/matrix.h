#ifndef MATRIX_H
#define MATRIX_H
#define SIZE 100 
#include<cfloat>
#include<string>
#include<iostream>
#include<vector>
#include "calculate.h"
using namespace std;
class matrix{
    Complex data[SIZE][SIZE]; // 使用二维数组来存储矩阵的数据（表示为空的数据为DBL_MAX
    vector<string> input;// 记录用户输入的数据
    size_t order; // 行列式的阶数
    Complex result;
public:
    matrix(vector<string> input); // 使用二维数组初始化
    void process(Complex d[][SIZE]); // 移动矩阵的数据
    Complex calculate(Complex d[][SIZE]); // 计算行列式值
    int get_row(Complex d[][SIZE]); // 统计行数
    void print_matrix(); // 输出行列式
    bool get_order(); // 通过用户输入的数据统计行列式的阶数
    Complex get_result(){return result;}
};
#endif
