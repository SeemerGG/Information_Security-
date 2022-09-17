#include <iostream>
#include <fstream>

using namespace std;

int sum_digit(int i)
{
	int b = i;
	int sum = 0;

	while (b != 0)
	{
		sum += b % 10;
		b /= 10;
	}
	return sum;
}

int main()
{
	setlocale(LC_ALL, "rus");

	ifstream fin("input.txt");
	
	int digit;
	fin >> digit;
	int sum_d = sum_digit(digit);
	int res = sum_d;
	while (res % 9 != 0)
	{
		res++;
	}

	ofstream fout("output.txt");

	fout << "Зачеркнутая цифра:" << res - sum_d << endl;
	fout.close();
}