#include <iostream>
#include <fstream> 
#include <string>
using namespace std;


int main()
{
	ifstream fin("input.txt");
	string old_str;
	fin >> old_str;
	fin.close();



	bool flag = true;
	int i = 0, j = 1;
	while(flag)
	{
		if (old_str[i] == old_str[j])
		{
			old_str.erase(i, 2);
			if (i != 0) {
				i--; j--;
			}
			
		}
		else
		{
			i++; j++;
		}
		if (old_str.size() < j)
			flag = false;
	}
	ofstream fout("output.txt");
	fout << old_str;
	fout.close();
}