#include "IO.h"
#include<iostream>
#include<cstring>
const int SIZE = 100;
using namespace std;
//string IO::transaction[SIZE];
IO::IO(char *input){
	this->input = input;
//	string temp = this->input.substr(0, this->input.find_first_of(" "));
	/*
		order list:
		0:CREATE TABLE tablename (column1,column2,¡­¡­,columnT) TO filename
		1:CREATE TABLE tablename FROM file
		2:TABLE LIST
		3:DROP TABLE tablename
		4:INSERT INTO tablename VALUES (¡­¡­£©
		5:INSERT INTO tablename (columns) VALUES (¡­¡­£©
		6:DELETE FROM filename WHERE column = value
		7:DELETE * FROM tablename
		8.UPDATE name SET columni = valuei, 
		9.UPDATE name SET columni = valuei WHERE column = value

	*/
	string temp = get_between(0, 2);
//	cout << temp << endl;
	if (temp.compare("CREATE TABLE") == 0){
		if (this->input.find("TO") != string::npos){
			order = 0;	//	CREATE TABLE TO FILE
		}
		else{
			order = 1;	//	CREATE TABLE FROM FILE
		}
	}
	else if (temp.compare("DROP TABLE") == 0){
		order = 2;	//	DROP TABLE
	}
	else if (temp.compare("TABLE LIST") == 0){
		order = 3;	//	TABLE LIST
	}
	else if (temp.compare("INSERT INTO") == 0){
		int cnt = 0;
		bool flag = false;
		for (int i = 0; input[i] != '\0'; i++){
			if (input[i] == '('){
				cnt++;
			}
			if (cnt >= 2){
				flag = true;
				break;
			}
		}
		if (!flag){
			order = 4;	//	INSERT INTO name VALUES
		}
		else{
			order = 5;	//	INSERT INTO name volumns VALUES
		}
	}
	else if (temp.compare("DELETE FROM") == 0){
		order = 6;	//	DELETE FROM name WHERE column = value
	}
	else if (temp.compare("DELETE *") == 0){
		order = 7;	//	DELETE * FROM name
	}
	else{
		temp = get_between(0, 1);
		if (temp.compare("UPDATE") == 0){
			if (this->input.find("WHERE") != string::npos){
				order = 8;	//	UPDATE SET WHERE ¡­¡­
			}
			else{
				order = 9;	//	UPDATE SET
			}
		}
		else if (temp.compare("SELECT") == 0){
			if (this->input.find("DISTINCT")!=string::npos){
				order = 10;	//	SELECT DISTINCT columns FROM tablename
			}
			else if (this->input.find("ORDER")!=string::npos){
				order = 11;	//	SELECT * FROM tablename ORDER BY columns ASC|DESC
			}
			else if (this->input.find("WHERE") != string::npos){
				order = 12;	//	SELECT columns FROM tablename WHERE column = value
			}
			else if (this->input.find("TO") != string::npos){
				order = 13;	//	SELECT colmns tablename TO file
			}
			else if (this->input.find('*') != string::npos){
				order = 14;	//	SELECT * FROM tablename
			}
			else{
				order = 15;	//	SELECT column1,column2,column3 FROM tablename
			}
		}
		else{
			order = -1;	//	ÊäÈë´íÎó
		}
	}
	
}
string IO::get_filename(){
	switch (order){
	case 0:
		return get_between(5, 6);
		break;
	case 1:
		return get_between(4, 5);
		break;
	default:
		return "";
	}
}
string IO::get_objectname(){
	switch (order){
	case 13:
		return this->input.substr(input.find("TO") + 3);
		break;
	default:
		return "";
	}
}
string IO::get_tablename(){
	switch (order){
	case 0:case 1:case 2:case 4:case 5:case 6:
		return get_between(2, 3);
		break;
	case 7:
		return get_between(3,4);
		break;
	case 8:case 9:
		return get_between(1, 2);
		break;
	case 10:case 11:case 12:case 13:case 14:case 15:{
		string str = this->input;
		str.erase(0, str.find("FROM") + 5);
		return str.substr(0, str.find_first_of(' '));
	}
		break;
	default:
		return "";
	}
}
string IO::get_values(){
	string str;
	switch (order){
	case 4:
		return input.substr(input.find_first_of('(') + 1, input.find_first_of(')') - input.find_first_of('(') - 1);
		break;
	case 5:
		str = input;
		str.erase(str.find_first_of('('), str.find_first_of(')') - str.find_first_of('(') + 1);
		return str.substr(str.find_first_of('(') + 1, str.find_first_of(')') - str.find_first_of('(') - 1);
		break;
	case 6:
		return get_between(6,7);
		break;
	case 8:case 9:
		str = input;
		if (str.find("WHERE") != string::npos){
			str.erase(str.find("WHERE"));
		}
		str.erase(0, str.find_first_of('=') + 2);
		while (str.find('=') != string::npos){
			str.erase(str.find_first_of(','), str.find_first_of('=') - str.find_first_of(',') + 1);
		}
		for (string::iterator it = str.begin(); it != str.end(); it++){
			if (*it == ' '){
				*it = ',';
			}
		}
		return str;
		break;
	default:
		return "";
	}
}
string IO::get_volumns(){
	string str = input;
	switch (order){
	case 0:case 5:
		return input.substr(input.find_first_of('(') + 1, input.find_first_of(')') - input.find_first_of('(') - 1);
		break;
	case 6:
		return get_between(4, 5);
		break;
	case 8:case 9:
		if (str.find("WHERE") != string::npos){
			str.erase(str.find("WHERE"));
		}
		str.erase(0, str.find("SET") + 4);
		while (str.find_first_of('=') != string::npos){
			str.erase(str.find_first_of('=') - 1, str.find_first_of(',') - str.find_first_of('=') + 2);
		}
		for (string::iterator it = str.begin(); it != str.end(); it++){
			if (*it == ' '){
				*it = ',';
			}
		}
		return str;
		break;
	case 10:
		return get_between(2, 3);
		break;
	case 11:
		return get_between(6, 7);
		break;
	case 12:
		return get_between(1, 2);
		break;
	case 13:
		return get_between(1, 2);
		break;
	case 15:
		return get_between(1, 2);
		break;
	default:
		return "";
	}
}
string IO::get_sc(){
	switch (order){
	case 11:
		return this->input.substr(this->input.find_last_of(' ') + 1);
	default:
		return "";
	}
}
string IO::get_position(){
	switch (order){
	case 8:case 12:
		return input.substr(input.find("WHERE")+6);
		break;
	default:
		return "";
	}
}

string IO::get_between(int a, int b){
	char temp[SIZE] = { '\0' };
	strcpy(temp, input.c_str());
	int begin, end;
	int cnt = 0;
	bool flag = false;
	for (int i = 0; temp[i] != '\0'; i++){
		if (temp[i] == ' ' || temp[i] == '\t'){
			cnt++;
		}
		if (cnt == a && !flag){
			if (i == 0){
				begin = i;
			}
			else{
				begin = i + 1;
			}
			flag = true;
		}
		if (cnt == b){
			end = i;
			break;
		}
	}
	return input.substr(begin, end - begin);
}
int IO::get_order(){ return order; }
