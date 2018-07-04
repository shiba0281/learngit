#ifndef Complex_H
#define Complex_H
#include<iostream>
using namespace std;
class Complex{
private:
    double real;
    double image;
    bool is_correct;
public:
    Complex();
    Complex(double real,double image);
    Complex(string exp);
    Complex operator+ (const Complex &c)const;
    Complex operator- (const Complex &c)const;
    Complex operator* (const Complex &c)const;
    Complex operator/ (const Complex &c);
    Complex operator^ (Complex &c);
    bool operator== (const Complex &c)const;
    bool operator!= (const Complex &c)const;
    Complex mod(const Complex &c)const;
    Complex cjg(const Complex &c)const;
    Complex arg(const Complex &c)const;
    Complex power(Complex &c1,Complex &c2)const;
    Complex dis(Complex &c1,Complex &c2)const; 
    string complex_to_str()const;
    bool get_result(){return is_correct;}
    friend ostream& operator << (ostream& out,const Complex &c);
    friend class Calculate;
    friend class equation;
};
#endif
