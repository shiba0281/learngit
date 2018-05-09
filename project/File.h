#ifndef File_h
#define File_h
#include<vector>
#include<string>
//#include "mySQL.h"
class File{
 private:
     FILE *fp;
    bool flag; 
 public:
     File(char *filename, char *model);
     ~File();
      void input_tablelist(std::vector<std::string*>&tablelist);
      void output_tablelist(std::vector<std::string*>&tablelist);
      void print_tablelist();
  //  void print_table(vector<string*>&table);
      void input_table(std::vector<std::string*>&table);
      void output_table(std::vector<std::string*>&table);
      void input_transaction();
      void reset();
      bool result(){return flag;}
      int get_line_num();
      int get_column_num();
  };
#endif

