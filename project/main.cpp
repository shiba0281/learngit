#include "mySQL.h"
int main()
{
	char temp[SIZE];
	cout << "musql==>";
    cin.getline(temp,SIZE);
	while (strcmp(temp,"quit")!=0){
		SQL sql(temp);
		cout << "mysql==>";
		cin.getline(temp,SIZE);
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
