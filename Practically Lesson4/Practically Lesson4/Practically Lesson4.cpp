#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream fin("alarm.txt");
	int n;
	fin >> n;

	vector<vector<int>> matr_adj(n);
	
	for (int i = 0; i < n; i++)
		matr_adj[i].resize(n);

	vector<int> mas_power(n);

	for (int i = 0; i < n; i++)
		fin >> mas_power[i];

	while (!fin.eof())
	{
		int a, b, c;
		fin >> a; fin >> b; fin >> c;
		matr_adj[a-1][b-1] = c;
	}
	
	vector<int> check(n);
	for (int i = 0; i < n; i++)
	{

	}


}