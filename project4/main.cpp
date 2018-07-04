#include "calculate.h"
using namespace std;
int main(){
    Complex c1(1,2);
    Complex c2(1,3);
/*    cout<<c1<<"+"<<c2<<"="<<c1+c2<<endl
        <<c1<<"-"<<c2<<"="<<c1-c2<<endl
        <<c1<<"*"<<c2<<"="<<c1*c2<<endl
        <<c1<<"/"<<c2<<"="<<c1/c2<<endl
        <<"|"<<c2<<"|"<<"="<<c1.mod(c2)<<endl;
        */
    string str="2+3i";
    calculate tmp(str);
    cout<<tmp.complex_to_str(c1)<<endl;
    cout<<tmp.str_to_complex(str)<<endl;
    cout<<c1.complex_to_str()<<endl;
    return 0;
}
    
