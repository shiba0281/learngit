#ifndef Complex_H
#define Complex_H
#include<iostream>
using namespace std;
class Complex{
private:
    double real;
    double image;
public:
    Complex();
    Complex(double real,double image);
    Complex operator+ (const Complex &c)const;
    Complex operator- (const Complex &c)const;
    Complex operator* (const Complex &c)const;
    Complex operator/ (const Complex &c)const;
    Complex mod(const Complex &c)const;
    Complex cjg (const Complex &c)const;
    string complex_to_str()const;
    friend ostream& operator << (ostream& out,const Complex &c);
};
#endif
