#include<iostream>
#include<regex>
#include<string>
using namespace std;
int main(){
      string s = "Some people, when confronted with a problem, think "
        "\"I know, I'll use regular expressions.\" "
        "Now they have two problems.";
     // 定义正则表达式
      regex self_regex("CONFRONTED WITH",regex_constants::icase);
      if(regex_search(s,self_regex)){
          cout<<"matched!"<<endl;
      }
        std::string pattern{ "\\d{3}-\\d{8}|\\d{4}-\\d{7}" }; // fixed telephone
    std::regex re(pattern);

    std::vector<std::string> str{ "010-12345678", "0319-9876543", "021-123456789"};

    /* std::regex_match:
        判断一个正则表达式(参数re)是否匹配整个字符序列str,它主要用于验证文本
        注意，这个正则表达式必须匹配被分析串的全部，否则返回false;如果整个序列被成功匹配，返回true
    */

    for (auto tmp : str) {
        bool ret = std::regex_match(tmp, re);
        if (ret) fprintf(stdout, "%s, can match\n", tmp.c_str());
        else fprintf(stderr, "%s, can not match\n", tmp.c_str());
    }
      return 0;
}
