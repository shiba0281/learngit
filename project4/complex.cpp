#include "complex.h"
#include<cmath>
Complex::Complex(){
    real=image=0;
}
Complex::Complex(double real,double image){
    this->real=real;
    this->image=image;
}
Complex Complex::operator+ (const Complex &c)const{
    return Complex(real+c.real,image+c.image);
}
Complex Complex::operator- (const Complex &c)const{
    return Complex(real-c.real,image-c.image);
}
Complex Complex::operator* (const Complex &c)const{
    return Complex(real*c.real-image*c.image,real*c.image+image*c.real);
}
Complex Complex::operator/ (const Complex &c)const{
//    return Complex((real*c.real+image*c.image)/(pow(c.real,2)+pow(c.image,2))
//                   ,(image*c.real-real*c.image)/(pow(c.real,2)+pow(c.image,2)));
    // 递归终止条件：如果是复数与实数相除，直接返回结果
    if(c.image==0){
        return Complex(real/c.real,image/c.real);
    }
    return Complex((*this)*cjg(c)/(c*cjg(c)));
}
Complex Complex::mod(const Complex &c)const{
    return Complex(sqrt(pow(c.real,2)+pow(c.image,2)),0);
}
Complex Complex::cjg(const Complex &c)const{
    return Complex(c.real,-c.image);
}
string Complex::complex_to_str()const{
    string rnt="";
    if(real==0){
        if(image==0){
            rnt+="0";
        }
        else{
            rnt+=to_string(image)+"i";
        }
    }
    else{
        if(image==0){
            rnt+=to_string(real);
        }
        else{
            rnt+=to_string(real)+"+"+to_string(image)+"i";
        }
    }
    return rnt;
}
ostream& operator <<(ostream& out, const Complex &c){
//    out<<c.real<<"+"<<c.image<<"i";
    if(c.real==0){
        if(c.image==0){
            out<<"0";
        }
        else{
            out<<c.image<<"i";
        }
    }
    else{
        if(c.image==0){
            out<<c.real;
        }
        else if(c.image>0){
            out<<c.real<<"+"<<c.image<<"i";
        }
        else{
            out<<c.real<<c.image<<"i";
        }
    }
    return out;
}
