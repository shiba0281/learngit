#include "matrix.h"
#include <iomanip>
matrix::matrix(vector<string> input){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            data[i][j]=Complex(DBL_MAX,DBL_MAX);
        }
    }
    this->input=input;
    if(!get_order()){cout<<"行列式输入有误！\n";}
    else{
        int index=0;
        for(int i=0;i<(int)order;i++){
            for(int j=0;j<(int)order;j++){
                Calculate tmp(input[index++]);
                data[i][j]=tmp.get_complex_result();
            }
        }
    }
    result = calculate(data);
}
bool matrix::get_order(){
    for(size_t i=0;i*i<=input.size();i++){
        if(i*i==input.size()){
            order=i;
            return true;
        }
    }
    return false;
}
Complex matrix::calculate(Complex d[][SIZE]){
    process(d);
//    cout<<"row = "<<get_row(d)<<endl;
    if(get_row(d)==1){
        return d[0][0];
    }
    Complex rnt(0,0);
    int sign=1;
    for(int i=0;i<get_row(d);i++){
        Complex tmp[SIZE][SIZE];
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                tmp[i][j]=d[i][j];
            }
        }
        for(int j=0;j<SIZE;j++){
            tmp[0][j]=Complex(DBL_MAX,DBL_MAX);
            tmp[j][i]=Complex(DBL_MAX,DBL_MAX);
        }
        rnt=rnt+Complex(sign,0)*d[0][i]*calculate(tmp);
        sign*=-1;
    }
    return rnt;
}
int matrix::get_row(Complex d[][SIZE]){
    int rnt=0;
    for(int i=0;i<SIZE;i++,rnt++){
        if(d[0][i]==Complex(DBL_MAX,DBL_MAX)){
            break;
        }
    }
    return rnt;
}
void matrix::process(Complex d[][SIZE]){
    // 新建一个存储临时矩阵数据的二维数组
    Complex tmp[SIZE][SIZE];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            tmp[i][j]=Complex(DBL_MAX,DBL_MAX);
        }
    }
    // row代表临时矩阵的行，col代表临时矩阵的列
    int row=0;
    for(int i=0;i<SIZE;i++){
        int col=0;
        for(int j=0;j<SIZE;j++){
            if(d[i][j]!=Complex(DBL_MAX,DBL_MAX)){
                tmp[row][col++]=d[i][j];
            }
        }
        if(col!=0){row++;}
    }
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            d[i][j]=tmp[i][j];
        }
    }
}
void matrix::print_matrix(){
    cout<<"你输入的行列式为：\n";
    for(int i=0;i<(int)order;i++){
        cout<<"|";
        for(int j=0;j<(int)order-1;j++){
            cout<<data[i][j]<<'\t';
        }
        cout<<data[i][(int)order-1]<<"|"<<endl;
    }
}
