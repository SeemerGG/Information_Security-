#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream fin("input.txt");

	string str;
	fin >> str;

	int count = 1;

	ofstream fout("output.txt");

	for (int i = 0; i < str.size(); i++)
	{
		if (i < str.size() - 1)
		{
			if (str[i] == str[i + 1])
			{
				count++;
			}
			else
				if (count == 1)
					fout << str[i];
				else
				{
					fout << count;
					fout << str[i];
					count = 1;
				}
		}
		else 
			if (count == 1)
				fout << str[i];
			else
			{
				fout << count;
				fout << str[i];
				count = 1;
			}
	}

	fout.close();

}