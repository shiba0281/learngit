#include "calculate.h"
#include<regex>
calculate::calculate(string expression){
    this->expression=expression;
}
string calculate::get_result(){
    return expression;
}
// 把string转换为complex类型
Complex calculate::str_to_complex(string str){
    string pattern=R"((\d*)[+-]*(\d*)i)";
    smatch sm;
    regex_match(str,sm,regex(pattern));
    return Complex(stod(sm[1]),stod(sm[2]));
}
string calculate::complex_to_str(const Complex &c){
    return c.complex_to_str(); 
}
/*
oid calculate::calculate_in_order(string str){
    // 如果已经是一个最简的复数，直接返回结果
    if(regex_match(str,regex(R"(\d*[+-]*\d*i)"))){
        return str;
    };
    // 如果不是一个最简的复数，按照顺序进行计算
    
}
*/
