#include "SQL.h"
#include "IO.h"
#include "File.h"
#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
SQL::SQL(char *input){
    flag=true;
	this->input = input;
	io = new IO(input);
	f = new File((char*)"mysql.txt", (char*)"r");
    if(f->result()){
    	f->input_tablelist(tablelist);
    }
    else{
        flag=false;
    }
//	print_tablelist();
	delete f;
    values=io->get_values();
    volumns=io->get_volumns();
	order = io->get_order();
	tablename = io->get_tablename();
	filename = io->get_filename();
	objectname = io->get_objectname();
	if (filename.compare("") == 0 && tablename.compare("") != 0){
		int i=0;
        for (; i < (int)tablelist.size(); i++){
			if (tablelist[i][0] == tablename){
				filename = tablelist[i][1];
				break;
			}
		}
        if((int)tablelist.size()==i){
            flag=false;
            cout<<"========================="<<endl
                <<"请确定输入了正确的TABLE名"<<endl
                <<"-------------------------"<<endl;
        }
	}
	if (filename.compare("") != 0&&order!=0){
		f = new File((char*)filename.c_str(), (char*)"r");
        if(f->result()){
            f->input_table(table);
            width_of_table=0;
            while(table[0][width_of_table++]!=" ");
            width_of_table--;
        }
        else{
            flag=false;
            cout<<"========================="<<endl
                <<"请确定输入了正确的TABLE名"<<endl
                <<"========================="<<endl;
        }
        //  delete f 会出错?
//        delete f;
	}
	position = io->get_position();
	if (io->get_sc().compare("")!=0){
		if (io->get_sc().compare("ASC")==0){
			asc_or_desc = true;
		}
		else{
			asc_or_desc = false;
		}
    }
    if(io->result()==false){
        flag=false;
        cout<<"======================================="<<endl
            <<"输入格式不规范!请输入README参考规范输入"<<endl
            <<"======================================="<<endl;
    }
	delete io;
    if(flag){
        Order();
    }
}
void SQL::print_tablelist(){
	cout << " total=" << tablelist.size() << endl;
	for (int i = 0; i < (int)tablelist.size(); i++){
		cout << '\t' << tablelist[i][0] << ": ";
		f = new File((char*)tablelist[i][1].c_str(), (char*)"r");
		f->print_tablelist();
		delete f;
	}
}
void SQL::save_tablelist(){
	f = new File((char*)"mysql.txt",(char*) "w");
	f->output_tablelist(tablelist);
	delete f;
}
void SQL::save_table(){
	f = new File((char*)filename.c_str(),(char*) "w");
	f->output_table(table);
	delete f;
}
void SQL::CreateFromFile(){
	string *s = new string[2];
	s[0] = tablename;
	s[1] = filename;
	tablelist.push_back(s);
	save_tablelist();
	print_table();
}
void SQL::CreateToFile(){
	string *s = new string[2];
	s[0] = tablename;
	s[1] = filename;
	tablelist.push_back(s);
	save_tablelist();
	table.push_back(str_to(volumns));
    width_of_table=0;
    string *tmp=str_to(volumns);
    while(tmp[width_of_table++]!=" ");
    width_of_table--;
	print_table();
	save_table();
}
void SQL::Drop(){
	bool flag = false;
    auto it=tablelist.begin();
	for (; it != tablelist.end(); it++){
		if (**it == tablename){
			flag = true;
			delete[] *it;
			it=tablelist.erase(it);
            if(it==tablelist.end()){break;}
			if (it != tablelist.begin()){ it--; }
		}
	}
	//for (int i = 0; i < tablelist.size(); i++){
	//	cout << tablelist[i][0] << '\t' << tablelist[i][1] << endl;
	//}
	if (flag){
		save_tablelist();
	}
	else{
		cout << "==========" << endl
			 << "未找到目标！" << endl
			 << "----------" << endl;
	}
}
void SQL::Insert(){
	string *s = str_to(values);
	int len_of_values = 0;
	int len_of_columns = 0;
	while (s[len_of_values++]!= " ");
	while (table[0][len_of_columns++] != " ");
	if (len_of_columns == len_of_values){
		table.push_back(str_to(values));
		save_table();
	}
	else{
		cout << "===============" << endl
			 << "输入与属性不一致！" << endl
			 << "---------------" << endl;
	}
}
void SQL::Insert_p(){
	string *name = str_to(volumns);
	string *temp = str_to(values);
	string *s = new string[SIZE];
	//	init s;
	for (int i = 0; i < SIZE; i++){
		s[i] = " ";
	}
	//	统计列数并且初始化value
	for (int i = 0; table[0][i] != " "; i++){
		bool flag = false;
	//	初始化value
		for (int j = 0; name[j] != " "; j++){
			if (name[j].compare(table[0][i]) == 0){
				s[i] = temp[j];
				flag = true;
				break;
			}
		}
		if (!flag){
			s[i] = "#";
		}
	}
	//	列中找不到的情况
	bool flag = false;
	for (int i = 0; s[i] != " "; i++){
		if (s[i] != "#"){
			flag = true;
			break;
		}
	}
	if (flag){
		table.push_back(s);
		save_table();
	}
	else{
		cout << "===========" << endl
			 << "未找到指定列" << endl
			 << "-----------" << endl;
		delete[] s;
		return;
	}
}
void SQL::Delete(){
	vector<string*>::iterator it = table.begin();
	if (it == table.end()){ return; }
	for (it++; it != table.end(); it++){
		delete[] * it;
		it = table.erase(it);
		it--;
	}
	save_table();
}
void SQL::Delete_p(){
	vector<string*>::iterator it = table.begin();
	bool flag = false;
	if (it == table.end()){ return; }
	//	寻找volumn对应的列，再进行纵向遍历
	int i = 0;
	//	横向遍历
	for (; table[0][i] != " "; i++){
		if (table[0][i].compare(volumns) == 0){
			break;
		}
	}
	//	纵向遍历
	for (; it != table.end(); it++){
		if ((*it)[i] == values){
			flag = true;
			delete[] * it;
			it = table.erase(it);
			it--;
		}
	}
	if (flag){
		save_table();
	}
	else{
		cout << "====================" << endl
			 << "未找到目标，删除失败！" << endl
			 << "--------------------" << endl;
	}
}
void SQL::Update(){
	//	获取columns
//	cout << volumns << '\t' << values << endl;
	string *sc = str_to(volumns);
	string *sv = str_to(values);
	for (int i = 0; sc[i] != " "; i++){
		for (int j = 0; table[0][j] != " "; j++){
			if (table[0][j] == sc[i]){
				for (int k = 1; k < (int)table.size(); k++){
					table[k][j] = sv[i];
				}
			}
		}
	}
	save_table();
}
void SQL::Select(){
	print_table();
}
void SQL::Select_p(){
    int flag[SIZE]={0};
    int cnt=0;
	string *s = str_to(volumns);
	//	确定需要输出的列的编号
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; s[j] != " "; j++){
			if (table[0][i] == s[j]){
				flag[cnt++] = i;
				break;
			}
		}
	}
    int tmp=0;
    while(s[tmp++]!=" ");
    if(--tmp!=cnt){
        cout<<"=========================="<<endl
            <<"输入的列在TABLE不完全存在!"<<endl
            <<"=========================="<<endl;
        return;
    }
	//	输出编号的特征数组里的列
	cout << "ID" << '\t';
	for (int i = 0; i < (int)table.size(); i++){
		if (i > 0){ cout << i << '\t'; }
		for (int j = 0; j < cnt; j++){
			cout << table[i][flag[j]] << '\t';
		}
		cout << endl;
	}
}
void SQL::Update_p(){
	string s[2];
	s[0] = position.substr(0, position.find_first_of('=') - 1);
	s[1] = position.substr(position.find_first_of('=') + 2);
	//	寻找需要修改的目标	
	int i = 0;
	for (; table[0][i] != " "; i++){
		if (table[0][i] == s[0]){ break; }
	}
	//	j为目标所在的行数
	int j = 0;
	for (; j < (int)table.size(); j++){
		if (table[j][i] == s[1]){ break; }
	}
	//	修改这一行的值
	string *sc = str_to(volumns);
	string *sv = str_to(values);

	for (int i = 0; sc[i] != " "; i++){
		for (int k = 0; table[0][k] != " "; k++){
			if (table[0][k] == sc[i]){
				table[j][k] = sv[i];
			}
		}
	}
/*
    for(int i=0;table[0][i]!=" ";i++){
        for(int k=0;sc[k]!=" ";k++){
            if(table[0][i]==sc[k]){
                table[j][i]=sv[k];
            }
        }
    }
    */
	save_table();
}
void SQL::Select_d(){
	string *s = str_to(volumns);
	//	确定需要输出的列数
	int b[SIZE] = { 0 };
	//	确定需要输出的行
	int a[SIZE] = { 0 };
	//	遍历表头，找出所有选择的列的编号
	int cnt = 0;
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; s[j] != " "; j++){
			if (table[0][i] == s[j]){
				b[cnt++] = i;
			}
		}
	}
    int tmp=0;
    while(s[tmp++]!=" ");
    if(--tmp!=cnt){
        cout<<"============================"<<endl
            <<"输入的列在TABLE中不完全存在!"<<endl
            <<"============================"<<endl;
        return;
    }
	int amount = 0;
	//	遍历所有行，找出需要没有重复内容的行标记
	for (int i = 0; i < (int)table.size(); i++){
		//	预设这一行特征行的内容在之前出现过
		bool flag = false;
		//	遍历前面的所有行
		if (i > 1){
			for (int j = i - 1; j > 0; j--){
				flag = true;
				for (int k = 0; k < cnt; k++){
					if (table[i][b[k]] != table[j][b[k]]){ flag = false; break; }
				}
				if (flag){
					break;
				}
			}
		}
		if (!flag){
			a[amount++] = i;
		}
	}
	cout << "ID" << '\t';
	for (int i = 0; i < amount; i++){
		if (i > 0){ cout << i << '\t'; }
		for (int j = 0; j < cnt; j++){
			cout << table[a[i]][b[j]] << '\t';
		}
		cout << endl;
	}
}
void SQL::Select_o(){
	string *sc = str_to(volumns);
	int cnt = 0;
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; sc[j] != " "; j++){
			if (table[0][i] == sc[j]){
				arrary[cnt++] = i;
			}
		}
	}
	arrary[cnt] = -1;
//	sort(table.begin()+1, table.end(), cmp);
	for (int i = 1; i < (int)table.size(); i++){
		for (int j = 1; j < (int)table.size() - i; j++){
			bool flag = cmp(table[j], table[j + 1]);
			if (!asc_or_desc){
				flag = !flag;
			}
			if (flag){
				string *temp = table[j];
				table[j] = table[j + 1];
				table[j + 1] = temp;
			}
		}
	}
//	print_table();
    if(values=="*"){print_table();}
    else{
        string *sv=str_to(values);
        int tmp[SIZE];
        int cnt=0;
        for(int i=0;table[0][i]!=" ";i++){
            for(int j=0;sv[j]!=" ";j++){
                if(table[0][i]==sv[j]){
                    tmp[cnt++]=i;
                }
            }
        }
        cout<<cnt<<endl;
        for(int i=0;i<(int)table.size();i++){
            for(int j=0;j<cnt;j++){
                cout<<table[i][tmp[j]]<<'\t';
            }
            cout<<endl;
        }
    }
}
bool SQL::cmp(string *a,string *b){
	for (int i = 0; arrary[i] != -1; i++){
		int i_a = stoi(a[arrary[i]]);
		int i_b = stoi(b[arrary[i]]);
		if (i_a > i_b){
			return true;
		}
		else if (i_a<i_b){
			return false;
		}
	}
	return false;
}
void SQL::Select_t(){
	string *s = str_to(volumns);
	for (int i = 0; table[0][i] != " "; i++){
		int j = 0;
		//	如果这一列没有在输入序列中出现过则s[j]=" "
		for (; s[j] != " "; j++){
			if (table[0][i] == s[j]){ break; }
		}
		if (s[j] == " "){
			//	把后面的每一列向左移
			for (int k = i + 1;k<SIZE; k++){
				for (int l = 0; l < (int)table.size(); l++){
					table[l][k - 1] = table[l][k];
				}
			}
			i--;
		}
	}
	width_of_table=0;
    while(table[0][width_of_table++]!=" ");
    width_of_table--;
    print_table();
	f = new File((char*)objectname.c_str(), (char*)"w");
	f->output_table(table);
	delete f;
}
void SQL::Select_pp(){
	/*cout << volumns << endl;
	cout << tablename << endl;
	cout << position << endl;*/
	string s[2];
    //  寻找关键字
    string key;
    if(position.find("!=")!=string::npos){
        key="!=";
    }
    else if(position.find(">=")!=string::npos){
        key=">=";
    }
    else if(position.find("<=")!=string::npos){
        key="<=";
    }
    else if(position.find('=')!=string::npos){
        key="=";
    }
    else if(position.find('<')!=string::npos){
        key="<";
    }
    else if(position.find('>')!=string::npos){
        key=">";
    }
	s[0] = position.substr(0, position.find_first_of(key) - 1);
	s[1] = position.substr(position.find_first_of(key) + key.size()+1);
       string *sc = str_to(volumns);
	//	存储标记列
	int cnt = 0;
	int a = 0;
	for (int i = 0; table[0][i] != " "; i++){
        if(table[0][i]==s[0]){
            a=i;
        }
        if(volumns=="*"){
            arrary[cnt++]=i;
            continue;
        }
        for (int j = 0; sc[j] != " "; j++){
            if (table[0][i] == sc[j]){
				arrary[cnt++] = i;
				break;
			}
		}
	}
	//	寻找指定行
	int flag[SIZE] = { 0 };
	int amount = 1;
/*	for (int i = 0; i < (int)table.size(); i++){
		if (table[i][a] == s[1]){
			flag[amount++] = i;
		}
	}
*/  
    if(key=="="){
        for(int i=0;i<(int)table.size();i++){
            if(table[i][a]==s[1]){
                flag[amount++]=i;
            }
        }      
    }
    else if(key=="!="){
        for(int i=0;i<(int)table.size();i++){
            if(table[i][a]!=s[1]){
                flag[amount++]=i;
            }
        }
    }
    else{
        int standard=stoi(s[1]);
        if(key==">"){
            for(int i=1;i<(int)table.size();i++){
                int tmp=stoi(table[i][a]);
                if(tmp>standard){
                    flag[amount++]=i;
                }
            }
        }
        else if(key=="<"){
            for(int i=1;i<(int)table.size();i++){
                int tmp=stoi(table[i][a]);
                if(tmp<standard){
                    flag[amount++]=i;
                }
            }
        }
        else if(key==">="){
           for(int i=1;i<(int)table.size();i++){
                int tmp=stoi(table[i][a]);
                if(tmp>=standard){
                    flag[amount++]=i;
                }
            }
         }
        else if(key=="<="){
           for(int i=1;i<(int)table.size();i++){
                int tmp=stoi(table[i][a]);
                if(tmp<=standard){
                    flag[amount++]=i;
                }
            }
        }
    }
	//	flag行为目标行的数组
	cout << "ID\t";
	for (int i = 0; i < amount; i++){
		if (flag[i] > 0){ cout << i << '\t'; }
		for (int j = 0; j < cnt; j++){
			cout << table[flag[i]][arrary[j]] << '\t';
		}
		cout << endl;
	}	
}
void SQL::readme(){
    ifstream in;
    in.open("README.txt",ios::in);
    if(!in){
        cout<<"==================="<<endl
            <<"打开README.txt失败!"<<endl
            <<"==================="<<endl;
        return;
    }
    char tmp[SIZE];
    in.getline(tmp,SIZE);
    cout<<"-----------------指令集------------------"<<endl;
    while(!in.eof()){
        cout<<tmp<<endl;
        in.getline(tmp,SIZE);
    }
    in.close();
    cout<<"========================================="<<endl;
}
void SQL::print_line(){
    for(int i=0;i<width_of_table*11;i++){cout<<'-';}
    cout<<endl;
}
void SQL::Select_m(bool flag){
    int column=0;
    for(;table[0][column]!=" ";column++){
        if(table[0][column]==volumns){
            break;
        }
    }
    if(table[0][column]==" "){
        cout<<"============="<<endl
            <<"未找到指定列!"<<endl
            <<"============="<<endl;
        return;
    }
    int max_id=1;
    for(int i=1;i<(int)table.size();i++){
        int tmp=stoi(table[i][column]);
        if(tmp>max_id&&flag){
            max_id=i;
        }
        else if(tmp<max_id&&!flag){
            max_id=i;
        }
    }
    print_line();
    cout<<'|';
    for(int i=0;table[0][i]!=" ";i++){
        cout<<setw(10)<<table[0][i]<<'|';
    }
    cout<<endl;
    print_line();
    cout<<'|';
    for(int i=0;table[max_id][i]!=" ";i++){
        cout<<setw(10)<<table[max_id][i]<<'|';
    }
    cout<<endl;
    print_line();
}

void SQL::Order(){
	switch (order){
	case 0:
		CreateToFile();
		break;
	case 1:
		CreateFromFile();
		break;
	case 2:
		Drop();
		break;
	case 3:
		print_tablelist();
		break;
	case 4:
		Insert();
		break;
	case 5:
		Insert_p();
		break;
	case 6:
		Delete_p();
		break;
	case 7:
		Delete();
		break;
	case 8:
		Update_p();
		break;
	case 9:
		Update();
		break;
	case 10:
		Select_d();
		break;
	case 11:
		Select_o();
		break;
	case 12:
		Select_pp();
		break;
	case 13:
		Select_t();
		break;
	case 15:
		Select_p();
		break;
    case 16:
        Select_m(true);
        break;
    case 17:
        Select_m(false);
        break;
    case 18:
        readme();
        break;
    case 14:
		Select();
		break;
	default:
		cout<<"=========="<<endl;
        cout<< "输入有误!" << endl;
        cout<<"----------"<<endl;
	}
	if (order >= 4&&order<=9&&flag){ print_table(); }
}
void SQL::print_table(){
    int *a=new int[width_of_table];
    for(int i=0;i<width_of_table;i++){
        a[i]=0;
        for(int j=0;j<(int)table.size();j++){
            if((int)table[j][i].size()>a[i]){
                a[i]=(int)table[j][i].size();
            }
        }
    }
    int len=0;
    for(int i=0;i<width_of_table;i++){
        len+=a[i];
    }
    len+=width_of_table*2;
    for(int i=0;i<len;i++){cout<<"-";}
    cout<<endl;
	cout<<'|'<<setw(3)<<"ID"<<'|';
	for (int i = 0; i < (int)table.size(); i++){
		if (i > 0){ 
            for(int i=0;i<len;i++){cout<<'-';}
            cout<<endl;
            cout<<'|'<< setw(3)<<i<<'|';
        }
		for (int j = 0; table[i][j] != " "; j++){
//			cout<<"|  ";
            if (table[i][j] == "#"){
				cout<<setw(a[j]) << " ";
			}
			else{
				cout<<setw(a[j]) << table[i][j];
			}
            cout<<'|';
		}
        cout<<endl;   
//		cout<<'|'<<endl;
	}
    for(int i=0;i<len;i++){cout<<'-';}
    cout<<endl;
}
string* SQL::str_to(string str){
	string *s = new string[SIZE];
	for (int i = 0; i < SIZE; i++){
		s[i] = " ";
	}
	for (int i = 0; true; i++){
		if (str.find_first_of(',') == string::npos){
			s[i] = str;
			break;
		}
		s[i] = str.substr(0, str.find_first_of(','));
		str.erase(0, str.find_first_of(',') + 1);
	}
	return s;
}
bool SQL::result(){return flag;}

//SQL::~SQL(){
//	if (tablelist.begin() == tablelist.end()){ return; }
//	for (vector<string*>::iterator it = tablelist.begin(); it != tablelist.end(); it++){
//		delete[] * it;
//		it = tablelist.erase(it);
//		it--;
//	}
//}
