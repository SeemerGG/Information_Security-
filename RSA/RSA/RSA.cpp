#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

vector<int> EncriptRsa(vector<int> t, int e, int n)
{
	vector<int> res;
	for (int i = 0; i < t.size(); i++)
	{
		res.push_back((int)(pow(t[i], e)) % n);
	}
	return res;
}

vector<int> TraanslateOn(string mess)
{
	vector<int> res;
	for (int i = 0; i < mess.size(); i++)
	{
		res.push_back(mess[i] - 'A');
	}
	return res;
}

void PrintVec(vector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
}
int main()
{
	string message = "Iron Man";
	vector<int> ironMan= { 73, 114, 111, 110, 0, 77, 97, 110 };
	vector<int> encriptMess = EncriptRsa(ironMan, 5, 35);
	PrintVec(encriptMess);
}