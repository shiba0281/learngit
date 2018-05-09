#include "mySQL.h"
SQL::SQL(char *input){
	this->input = input;

	io = new IO(input);
	f = new File("mysql.txt", "r");
	f->input_tablelist(tablelist);
//	print_tablelist();
	delete f;
	order = io->get_order();
	tablename = io->get_tablename();
	filename = io->get_filename();
	objectname = io->get_objectname();
	if (filename.compare("") == 0 && tablename.compare("") != 0){
		for (int i = 0; i < tablelist.size(); i++){
			if (tablelist[i][0] == tablename){
				filename = tablelist[i][1];
				break;
			}
		}
	}
	if (filename.compare("") != 0&&order!=0){
		f = new File((char*)filename.c_str(), "r");
		f->input_table(table);
		delete f;
	}
	volumns = io->get_volumns();
	values = io->get_values();
	position = io->get_position();
	if (io->get_sc().compare("")!=0){
		if (io->get_sc().compare("ASC")==0){
			asc_or_desc = true;
		}
		else{
			asc_or_desc = false;
		}
	}
	delete io;
	Order();
}
void SQL::print_tablelist(){
	cout << " total=" << tablelist.size() << endl;
	for (int i = 0; i < tablelist.size(); i++){
		cout << '\t' << tablelist[i][0] << ": ";
		f = new File((char*)tablelist[i][1].c_str(), "r");
		f->print_tablelist();
		delete f;
	}
}
void SQL::save_tablelist(){
	f = new File("mysql.txt", "w");
	f->output_tablelist(tablelist);
	delete f;
}
void SQL::save_table(){
	f = new File((char*)filename.c_str(), "w");
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
	print_table();
	save_table();
}
void SQL::Drop(){
	bool flag = false;
	for (vector<string*>::iterator it = tablelist.begin(); it != tablelist.end(); it++){
		if (**it == tablename){
			flag = true;
			delete[] *it;
			it=tablelist.erase(it);
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
			 << "δ�ҵ�Ŀ�꣡" << endl
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
			 << "���������Բ�һ�£�" << endl
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
	//	ͳ���������ҳ�ʼ��value
	for (int i = 0; table[0][i] != " "; i++){
		bool flag = false;
	//	��ʼ��value
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
	//	�����Ҳ��������
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
			 << "δ�ҵ�ָ����" << endl
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
	//	Ѱ��volumn��Ӧ���У��ٽ����������
	int i = 0;
	//	�������
	for (; table[0][i] != " "; i++){
		if (table[0][i].compare(volumns) == 0){
			break;
		}
	}
	//	�������
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
			 << "δ�ҵ�Ŀ�꣬ɾ��ʧ�ܣ�" << endl
			 << "--------------------" << endl;
	}
}
void SQL::Update(){
	//	��ȡcolumns
//	cout << volumns << '\t' << values << endl;
	string *sc = str_to(volumns);
	string *sv = str_to(values);
	for (int i = 0; sc[i] != " "; i++){
		for (int j = 0; table[0][j] != " "; j++){
			if (table[0][j] == sc[i]){
				for (int k = 1; k < table.size(); k++){
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
	string *s = str_to(volumns);
	//	ȷ����Ҫ������еı��
	int flag[SIZE] = { 0 };
	int cnt = 0;
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; s[j] != " "; j++){
			if (table[0][i] == s[j]){
				flag[cnt++] = i;
				break;
			}
		}
	}
	//	�����ŵ��������������
	cout << "ID" << '\t';
	for (int i = 0; i < table.size(); i++){
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
	//	Ѱ����Ҫ�޸ĵ�Ŀ��	
	int i = 0;
	for (; table[0][i] != " "; i++){
		if (table[0][i] == s[0]){ break; }
	}
	//	jΪĿ�����ڵ�����
	int j = 0;
	for (; j < table.size(); j++){
		if (table[j][i] == s[1]){ break; }
	}
	//	�޸���һ�е�ֵ
	string *sc = str_to(volumns);
	string *sv = str_to(values);
	for (int i = 0; sc[i] != " "; i++){
		for (int k = 0; table[0][k] != " "; k++){
			if (table[0][k] == sc[i]){
				table[j][k] = sv[i];
			}
		}
	}
	save_table();
}
void SQL::Select_d(){
	string *s = str_to(volumns);
	//	ȷ����Ҫ���������
	int b[SIZE] = { 0 };
	//	ȷ����Ҫ�������
	int a[SIZE] = { 0 };
	//	������ͷ���ҳ�����ѡ����еı��
	int cnt = 0;
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; s[j] != " "; j++){
			if (table[0][i] == s[j]){
				b[cnt++] = i;
			}
		}
	}
	int amount = 0;
	//	���������У��ҳ���Ҫû���ظ����ݵ��б��
	for (int i = 0; i < table.size(); i++){
		//	Ԥ����һ�������е�������֮ǰ���ֹ�
		bool flag = false;
		//	����ǰ���������
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
	for (int i = 1; i < table.size(); i++){
		for (int j = 1; j < table.size() - i; j++){
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
	print_table();
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
		//	�����һ��û�������������г��ֹ���s[j]=" "
		for (; s[j] != " "; j++){
			if (table[0][i] == s[j]){ break; }
		}
		if (s[j] == " "){
			//	�Ѻ����ÿһ��������
			for (int k = i + 1;k<SIZE; k++){
				for (int l = 0; l < table.size(); l++){
					table[l][k - 1] = table[l][k];
				}
			}
			i--;
		}
	}
	print_table();
	f = new File((char*)objectname.c_str(), "w");
	f->output_table(table);
	delete f;
}
void SQL::Select_pp(){
	/*cout << volumns << endl;
	cout << tablename << endl;
	cout << position << endl;*/
	string s[2];
	s[0] = position.substr(0, position.find_first_of('=') - 1);
	s[1] = position.substr(position.find_first_of('=') + 2);
	string *sc = str_to(volumns);
	//	�洢�����
	int cnt = 0;
	int a = 0;
	for (int i = 0; table[0][i] != " "; i++){
		for (int j = 0; sc[j] != " "; j++){
			if (table[0][i] == sc[j]){
				arrary[cnt++] = i;
				break;
			}
		}
		if (table[0][i] == s[0]){
			a = i;
		}
	}
	//	Ѱ��ָ����
	int flag[SIZE] = { 0 };
	int amount = 1;
	for (int i = 0; i < table.size(); i++){
		if (table[i][a] == s[1]){
			flag[amount++] = i;
		}
	}
	//	flag��ΪĿ���е�����
	cout << "ID\t";
	for (int i = 0; i < amount; i++){
		if (flag[i] > 0){ cout << i << '\t'; }
		for (int j = 0; j < cnt; j++){
			cout << table[flag[i]][arrary[j]] << '\t';
		}
		cout << endl;
	}	
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
	case 14:
		Select();
		break;
	default:
		cout << "��������" << endl;
	}
	if (order >= 4&&order<=9){ print_table(); }
}
void SQL::print_table(){
	cout << "ID" << '\t';
	for (int i = 0; i < table.size(); i++){
		if (i > 0){ cout << i << '\t'; }
		for (int j = 0; table[i][j] != " "; j++){
			if (table[i][j] == "#"){
				cout << " ";
			}
			else{
				cout << table[i][j];
			}
			cout << '\t';
		}
		cout << endl;
	}
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

//SQL::~SQL(){
//	if (tablelist.begin() == tablelist.end()){ return; }
//	for (vector<string*>::iterator it = tablelist.begin(); it != tablelist.end(); it++){
//		delete[] * it;
//		it = tablelist.erase(it);
//		it--;
//	}
//}