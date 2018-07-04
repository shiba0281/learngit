#define DEBUG
#ifndef SQL_h
#define SQL_h
#include<string>
#include<vector>
const int SIZE = 100;
class IO;
class File;
class SQL{
private:
    std::vector<std::string*>tablelist;
	//static int cnt;
    std::vector<std::string*>table;
    std::string filename;
    std::string objectname;
    std::string tablename;
    std::string volumns;
    std::string values;
    std::string position;
	bool asc_or_desc;
    bool flag;
    int width_of_table;
    int order;
	int arrary[SIZE];
	char *input;
	File *f;
	IO *io;
public:
	SQL(char *input);
//	~SQL();
    std::string* str_to(std::string str);
	bool result();
    void print_line();
    void readme();
    void print_tablelist();
	void print_table();
	void save_tablelist();
	void save_table();
	void Order();
	void CreateFromFile();
	void CreateToFile();
	void Drop();
	void Insert();
	void Insert_p();
	void Delete();
	void Delete_p();
	void Update();
	void Update_p();
	void Select();
    void Select_m(bool flag);
	void Select_p();
	void Select_d();
	void Select_o();
	void Select_t();
	void Select_pp();
	bool cmp(std::string *a,std::string *b);
	friend class File;
};
#endif
