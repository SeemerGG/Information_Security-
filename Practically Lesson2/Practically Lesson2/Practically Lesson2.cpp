#include <iostream>

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

	cout << "Введите очтавшиеся цифры:";

	int digit;
	cin >> digit;
	int sum_d = sum_digit(digit);
	int res = sum_d;
	while (res % 9 != 0)
	{
		res++;
	}

	cout << "Зачеркнутая цифра:" << res - sum_d << endl;
}