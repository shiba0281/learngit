#include "complex.h"
#include<cmath>
#include<regex>
Complex::Complex(){
    real=image=0;
}
Complex::Complex(double real,double image){
    this->real=real;
    this->image=image;
    is_correct=true;
}
Complex::Complex(string exp){
    // a+bi型
    // a型
    // bi型
//    string pattern=R"("(\d+(?:\.\d+)?)(?:([+-]\d+(?:\.\d+))?i)?")";
    if(exp=="i"){exp="1i";}
    exp=regex_replace(exp,regex(R"(([^\d])i)"),"$011i");
    string pattern=R"((-?\d+(?:\.\d+)?)i)";
    smatch sm;
    if( regex_match(exp,sm,regex(pattern))){
        real=0;
        image=stod(sm[1]);
    }
    pattern=R"((-?\d+(?:\.\d+)?)(?:([+-]\d+(?:\.\d+)?)i)?)";
    if(regex_match(exp,sm,regex(pattern))){
        if(sm[1].str().size()==0)
            real=0;
        else real=stod(sm[1]);
        if(sm[2].str().size()==0)
            image=0;
        else image=stod(sm[2]);
    }
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
Complex Complex::operator/ (const Complex &c){
//    return Complex((real*c.real+image*c.image)/(pow(c.real,2)+pow(c.image,2))
//                   ,(image*c.real-real*c.image)/(pow(c.real,2)+pow(c.image,2)));
    // 递归终止条件：如果是复数与实数相除，直接返回结果
    // 如果实部虚部都为0.返回errpr
    if(c.image==0&&c.real==0){
        cout<<"除数不能为0!!"<<endl;
        is_correct=false;
    }
    if(c.image==0){
        return Complex(real/c.real,image/c.real);
    }
    return Complex((*this)*cjg(c)/(c*cjg(c)));
}
Complex Complex::operator^ (Complex &c){
    if(c.real==0){return Complex(1,0);}
    if(c.real<0){
        Complex tmp=Complex(1,0)/Complex(real,image);
        real=tmp.real;
        image=tmp.image;
//        c1=Complex(1,0)/c1;
        c=Complex(0,0)-c;
    }
    Complex rnt(real,image);
    while(c.real>1){
        rnt=rnt*Complex(real,image);
        c.real--;
    }
    return rnt; 
}
bool Complex::operator==(const Complex &c)const{
    return (c.real==real&&c.image==image);
}
bool Complex::operator!=(const Complex &c)const{
    return (c.real!=real||c.image!=image);
}
Complex Complex::mod(const Complex &c)const{
    return Complex(sqrt(pow(c.real,2)+pow(c.image,2)),0);
}
Complex Complex::cjg(const Complex &c)const{
    return Complex(c.real,-c.image);
}
Complex Complex::arg(const Complex &c)const{
    return Complex(acos(c.real/mod(c).real),0);
}
Complex Complex::power(Complex &c1,Complex &c2)const{
    if(c2.real==0){return Complex(1,0);}
    if(c2.real<0){
        c1=Complex(1,0)/c1;
        c2=Complex(0,0)-c2;
    }
    Complex rnt=c1;
    while(c2.real>1){
        rnt=rnt*c1;
        c2.real--;
    }
    return rnt;
}
Complex Complex::dis(Complex &c1,Complex &c2)const{
    return Complex(sqrt(pow(c1.real-c2.real,2)+pow(c1.image-c2.image,2)),0);
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
        else if(image>0){
            rnt+=to_string(real)+"+"+to_string(image)+"i";
        }
        else{
            rnt+=to_string(real)+to_string(image)+"i";
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
        else if(c.image==1){
            out<<"i";
        }
        else{
            out<<c.image<<"i";
        }
    }
    else{
        if(c.image==0){
            out<<c.real;
        }
        else if(c.image==1){
            out<<c.real<<"+i";
        }
        else if(c.image>0){
            out<<c.real<<"+"<<c.image<<"i";
        }
        else if(c.image==-1){
            out<<c.real<<"-i";
        }
        else{
            out<<c.real<<c.image<<"i";
        }
    }
    return out;
}
