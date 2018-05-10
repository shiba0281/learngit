#ifndef IO_h
#define IO_h
#include<string>
//const int SIZE = 100;
class IO{
private:
//	static string transaction[SIZE];
    std::string input;
	int order;
    bool is_correct;
//	File *f;
public:
	IO(char *input);
    void preprocess();
	int get_order();
    bool result(){return is_correct;}
    std::string get_filename();
    std::string get_objectname();
    std::string get_tablename();
    std::string get_volumns();
    std::string get_values();
    std::string get_position();
    std::string get_between(int a,int b);	//	获得第a个空格和第b个空格之间的有效信息
    std::string get_sc();
	friend class File;
};
#endif
