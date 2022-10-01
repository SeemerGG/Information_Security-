#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int frequency(char x, string number)
{
	int count = 0;

	for (int i = 0; i < number.size(); i++) {
		if (x == number[i])
			count++;
	}
	return count; 
}

bool next_set(int *answer, int n, int m)
{
	int j = m - 1;
	while (j >= 0 && answer[j] == n) j--;
	if (j < 0) return false;
	answer[j]++;
	if (j == m - 1) return true;
	for (int k = j + 1;k < m; k++)
	{
		answer[k] = 1;
	}
	return true;
}

bool check(int* answer, int m)
{
	int count7 = 0, count5 = 0, count2 = 0;
	for (int i = 0; i < m; i++)
	{
		if (answer[i] == 1)
			count7++;
		if (answer[i] == 2)
			count5++;
		if (answer[i] == 3)
			count2++;
	}
	if (count7 == 4 && count5 == 2 && count2 == 2)
		return true;
	return false;
}

void print(ofstream &fout, int *answer, int m)
{
	for (int i = 0; i < m; i++)
		if (answer[i] == 1)
			fout << 7;
		else
			if (answer[i] == 2)
				fout << 5;
			else
				fout << 2;
	fout << endl;
}

int main()
{
	ofstream fout("output.txt");

	string alf = "0123456789ABCDEF";
	
	int answer[8] = {1,1,1,1,1,1,1,1};

	while (next_set(answer, 3, 8))
	{
		if(check(answer, 8))
			print(fout, answer, 8);
	}
	
	fout.close();
}