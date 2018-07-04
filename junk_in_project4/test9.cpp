#include <iostream>
#include <iterator>
#include <regex>
#include <string>
using namespace std; 
int main()
{
   std::string text = "Quick brown fox";
   std::regex vowel_re("a|e|i|o|u");
 
   // 写结果到输出迭代器
   std::regex_replace(std::ostreambuf_iterator<char>(std::cout),
                      text.begin(), text.end(), vowel_re, "*");
    cout<<text<<endl;
//    return 0;
   // 构造保有结果的字符串
   std::cout << '\n' << std::regex_replace(text, vowel_re, "[$&]") << '\n';
    cout<<text<<endl;;
}
