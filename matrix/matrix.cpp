#include "matrix.h"
matrix::matrix(string d[][SIZE]){
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(d[i][j]=="#"){data[i][j]=DBL_MAX;}
            else{data[i][j]=stod(d[i][j]);}
        }
    }
//    print_matrix(data);
    cout<<"the value of the matrix = "<<calculate(data)<<endl;
}
double matrix::calculate(double d[][SIZE]){
    process(d);
//    cout<<"row = "<<get_row(d)<<endl;
    if(get_row(d)==1){
        return d[0][0];
    }
    double rnt=0;
    int sign=1;
    for(int i=0;i<get_row(d);i++){
        double tmp[SIZE][SIZE];
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                tmp[i][j]=d[i][j];
            }
        }
        for(int j=0;j<SIZE;j++){
            tmp[0][j]=DBL_MAX;
            tmp[j][i]=DBL_MAX;
        }
        rnt+=sign*d[0][i]*calculate(tmp);
        sign*=-1;
    }
    return rnt;
}
int matrix::get_row(double d[][SIZE]){
    int rnt=0;
    for(int i=0;i<SIZE;i++,rnt++){
        if(d[0][i]==DBL_MAX){
            break;
        }
    }
    return rnt;
}
void matrix::process(double d[][SIZE]){
    // 新建一个存储临时矩阵数据的二维数组
    double tmp[SIZE][SIZE];
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            tmp[i][j]=DBL_MAX;
        }
    }
    // row代表临时矩阵的行，col代表临时矩阵的列
    int row=0;
    for(int i=0;i<SIZE;i++){
        int col=0;
        for(int j=0;j<SIZE;j++){
            if(d[i][j]!=DBL_MAX){
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
void matrix::print_matrix(double d[][SIZE]){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
//            cout<<d[i][j]<<'\t';
            if(d[i][j]!=DBL_MAX){cout<<d[i][j]<<'\t';}
            else{cout<<"#\t";}
        }
        cout<<endl;
    }
}
