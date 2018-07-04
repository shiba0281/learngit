#include "File.h"
#include<iostream>
#include<cstring>
const int SIZE = 100;
using namespace std; 
File::File(char *filename, char *model){
	fp = fopen(filename, model);
	if (fp == NULL){
        cout<<"==============="<<endl;
		printf("打开%s失败！\n", filename);
        cout<<"==============="<<endl;
//		exit(-1);
        flag=false;
	}
    else{
        flag=true;
    }
}
File::~File(){ fclose(fp); }
void File::input_tablelist(vector<string*>&tablelist){
	reset();
	char tablename[SIZE] = { '\0' };
	char filename[SIZE] = { '\0' };
	fscanf(fp, "%s", tablename);
    if(!feof(fp)){
	fscanf(fp, "%s", filename);
    }
//	fgetc(fp);
//	string *s = new string[2];
	while (!feof(fp)){
//		cout << "test" << endl;
		string *s = new string[2];
		s[0] = tablename;
		s[1] = filename;
		tablelist.push_back(s);
		fscanf(fp, "%s", tablename);
		fscanf(fp, "%s", filename);
	}
}
void File::print_tablelist(){
	reset();
	char columns[SIZE];
	fgets(columns, SIZE, fp);
	int position = ftell(fp);
	if (position == 0){ 
		cout << "this table is empty!"<< endl;
		return; 
	}
	cout << '(' << get_column_num() << ',' << get_line_num()-1 << ") "
		<< '[';
	reset();
	char temp[SIZE] = { '\0' };
	fscanf(fp, "%s", temp);
	string str;
	while (ftell(fp) < position){
		str += temp;
		str += ',';
		fscanf(fp, "%s", temp);
	}
	str.erase(str.find_last_of(','));
	cout << str;
	cout << ']' << endl;
}
int File::get_column_num(){
	reset();
	char temp[SIZE];
	fgets(temp, SIZE, fp);
	int len = ftell(fp);
	int cnt = 0;
	fseek(fp, 0, SEEK_SET);
	fscanf(fp, "%s", temp);
	while (ftell(fp) < len){
		fscanf(fp, "%s", temp);
		cnt++;
	}
	return cnt;
}
int File::get_line_num(){
	reset();
	int cnt = 0;
	while (!feof(fp)){
		if (fgetc(fp) == '\n'){ cnt++; }
	}
	return cnt;
}
void File::output_tablelist(vector<string*>&tablelist){
	reset();
	char temp[SIZE] = { '\0' };
	for (int i = 0; i < (int)tablelist.size(); i++){
		strcpy(temp, tablelist[i][0].c_str());
		fprintf(fp, "%s\t", temp); 
		strcpy(temp, tablelist[i][1].c_str());
		fprintf(fp, "%s\n", temp);
	}
}
void File::input_table(vector<string*>&table)
{
	int column_num = get_column_num();
	int line_num = get_line_num();
	reset();
//	cout << line_num << endl;
	for (int i = 0; i < line_num; i++){
		string *s = new string[SIZE];
		for (int j = 0; j < SIZE; j++){
			s[j] = " ";
		}
		char temp[SIZE] = { '\0' };
		for (int j = 0; j < column_num; j++){
			fscanf(fp, "%s", temp);
			s[j] = temp;
		}
		table.push_back(s);
	}
	/*reset();
	char temp[SIZE] = { '\0' };
	fgets(temp, SIZE, fp);
	while (!feof(fp)){
		string *s = new string[SIZE];
		for (int j = 0; j < SIZE; j++){
			s[j] = " ";
		}
	}*/
}
void File::output_table(vector<string*>&table){
	reset();
	for (int i = 0; i < (int)table.size(); i++){
		for (int j = 0; table[i][j] != " "; j++){
			fprintf(fp, "%s\t", table[i][j].c_str());
		}
		fputc('\n', fp);
	}
}
void File::reset(){ fseek(fp, 0, SEEK_SET); }
