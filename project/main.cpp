#include "SQL.h"
#include "File.h"
#include "IO.h"
#include<cstring>
#include<iostream>
int main()
{
	char temp[SIZE];
    std::cout << "mysql==>";
    std::cin.getline(temp,SIZE);
	while (strcmp(temp,"quit")!=0){
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
