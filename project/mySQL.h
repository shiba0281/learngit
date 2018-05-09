#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<string>
#include<algorithm>
#define DEBUG
const int SIZE = 100;
using namespace std;

class File;
class IO;
class SQL;

class File{
private:
	FILE *fp;
public:
	File(char *filename, char *model);
	~File();
	void input_tablelist(vector<string*>&tablelist);
	void output_tablelist(vector<string*>&tablelist);
	void print_tablelist();
//	void print_table(vector<string*>&table);
	void input_table(vector<string*>&table);
	void output_table(vector<string*>&table);
	void input_transaction();
	void reset();
	int get_line_num();
	int get_column_num();
};

class SQL{
private:
	vector<string*>tablelist;
	//static int cnt;
	vector<string*>table;
	string filename;
	string objectname;
	string tablename;
	string volumns;
	string values;
	string position;
	bool asc_or_desc;
	int order;
	int arrary[SIZE];
	char *input;
	File *f;
	IO *io;
public:
	SQL(char *input);
//	~SQL();
	string* str_to(string str);
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
	void Select_p();
	void Select_d();
	void Select_o();
	void Select_t();
	void Select_pp();
	bool cmp(string *a, string *b);
	friend class File;
};

class IO{
private:
//	static string transaction[SIZE];
	string input;
	int order;
//	File *f;
public:
	IO(char *input);
	int get_order();
	string get_filename();
	string get_objectname();
	string get_tablename();
	string get_volumns();
	string get_values();
	string get_position();
	string get_between(int a,int b);	//	获得第a个空格和第b个空格之间的有效信息
	string get_sc();
	friend class File;
};
