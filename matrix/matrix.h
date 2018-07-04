#ifndef MATRIX_H
#define MATRIX_H
#define SIZE 100 
#include<cfloat>
#include<string>
#include<iostream>
using namespace std;
class matrix{
    double data[SIZE][SIZE]; // 使用二维数组来存储矩阵的数据（表示为空的数据为DBL_MAX
public:
    matrix(string d[][SIZE]); // 使用二维数组初始化
    void process(double d[][SIZE]); // 移动矩阵的数据
    double calculate(double d[][SIZE]); // 计算行列式值
    int get_row(double d[][SIZE]); // 统计行数
    void print_matrix(double d[][SIZE]); // 输出行列式
};
#endif
