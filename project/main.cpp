#include "SQL.h"
#include "File.h"
#include "IO.h"
#include<cstring>
#include<iostream>
#include<fstream>
//#include<string>
//#include<vector>
int main()
{
    std::vector<std::string>orders;
    char temp[SIZE];
    std::cout << "mysql==>";
    std::cin.getline(temp,SIZE);
	while (strcmp(temp,"quit")!=0){
        std::string str=temp;
        orders.push_back(str);
        if(strcmp(temp,"reflog")==0){
            std::cout<<"==========================\n";
            int i=0;
            for(auto it=orders.begin();it!=orders.end();it++){
                std::cout<<i++<<':'<<*it<<std::endl;
            }
            std::cout<<"==========================\n";
            std::cout<<"mysql==>";
            std::cin.getline(temp,SIZE);
            continue;
        }
        else if(strcmp(temp,"auto execute")==0){
            std::ifstream in;
            in.open("README.txt",std::ios::in);
            if(!in){
                std::cout<<"=================\n"
                        <<"打开README.txt失败!\n"
                        <<"==================\n";
                continue;
            }
            in.getline(temp,SIZE);
            while(!in.eof()){
                std::cout<<"mysql==>"<<temp<<std::endl;;
                SQL sql(temp);
                in.getline(temp,SIZE);
            }
            in.close();
            std::cout<<"mysql==>";
            std::cin.getline(temp,SIZE);
            continue;
        }
		SQL sql(temp);
        std::cout << "mysql==>";
        std::cin.getline(temp,SIZE);
	}
	return 0;
}
//int cmp(int a, int b){ return a < b; }
//int main(){
//	vector<int>a = { 1, 2, 3, 4, 5, 6 };
//	sort(a.begin(), a.end(), cmp);
//	for (int i = 0; i < a.size(); i++){
//		cout << a[i] << endl;
//	}
//}
