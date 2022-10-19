﻿#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;

// s[i] >= o[j] - можно читать  s[i] <= o[j] - можно писать; A[i][j] = "r" or "w" or "rw"

bool check_CS(int n, int m, vector<vector<string>>  A, vector<int> LO, vector<int> LS)
{
    for (int i = 0;i < n; i++)
    {
        for (int j = 0;j < m; j++)
        {
            if ((LS[j] == LO[i] && A[i][j] != "rw") || (LS[j] < LO[i] && A[i][j] != "r") || (LS[j] > LO[i] && A[i][j] != "w"))
            {
                return false;
            }
        }
    }
    return true;
}

bool search_LO_LS(int n, int m, vector<vector<string>>& A, vector<int>& LO, vector<int>& LS)
{
    LO.clear();
    LS.clear();


}
int main()
{
    int n, m;
    cin >> n;
    cin >> m;

    vector<vector<string>> A;
    
    vector<int> LS, LO;
    string str;
    vector<string> strs;
    for (int i = 0; i < n; i++)
    {
        vector<string> strs;
        for (int j = 0; j < m; j++)
        {
            cin >> str;
            strs.push_back(str);
        }
        A.push_back(strs);
        strs.clear();
    }
    int k;
    for (int i = 0; i < m; i++)
    {

        cin >> k;
        LS.push_back(k);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> k;
        LO.push_back(k);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << check_CS(n, m, A, LO, LS);

}

