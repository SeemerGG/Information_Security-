#include <iostream>
#include <fstream> 

using namespace std;

int count_lette_replay(char letter, string str)
{
	int count = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (letter == str[i])
			count++;
	}
	return count;
}

int string_diversity(string str)
{
	int diversity = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (count_lette_replay(str[i], str) < 2)
			diversity++;
	}
	return diversity;
}

int main()
{
	ifstream fin("input.txt");
	string old_str;
	fin >> old_str;
	fin.close();

	int diversity = string_diversity(old_str);
	string max_diversity_str = old_str;
	string old_str_copy = old_str;

	while (!old_str_copy.empty())
	{
		old_str_copy.erase(0,1);
		int new_diversity = string_diversity(old_str_copy);

		if (new_diversity > diversity)
		{
			diversity = new_diversity;
			max_diversity_str = old_str_copy;
		}
	}

	old_str_copy = old_str;

	while (!old_str_copy.empty())
	{
		old_str_copy.pop_back();
		int new_diversity = string_diversity(old_str_copy);

		if (new_diversity > diversity)
		{
			diversity = new_diversity;
			max_diversity_str = old_str_copy;
		}
	}

	ofstream fout("output.txt");
	fout << max_diversity_str;
	fout.close();
}