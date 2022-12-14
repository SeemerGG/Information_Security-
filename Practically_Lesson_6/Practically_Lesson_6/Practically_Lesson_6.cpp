#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;

// s[i] >= o[j] - можно читать  s[i] <= o[j] - можно писать; A[i][j] = "r" or "w"

bool check_CS(int n, int m, vector<vector<string>>  A, vector<int> LO, vector<int> LS)
{
    bool flag = 1;
    vector<string> error;
    int num = 0;
    for (int i = 0;i < n; i++)
    {
        for (int j = 0;j < m; j++)
        {
            if ((LS[j] <= LO[i] && A[i][j] != "r") || (LS[j] > LO[i] && A[i][j] != "w"))
            {
                num++;
                error.push_back("Error security " + to_string(num) + ": NumS = " + to_string(j) + " NumO = " + to_string(i));
                flag = false;
            }
        }
    }
    
    if (flag == false)
    {
        for (int i = 0; i < error.size(); i++)
        {
            cout << error[i] << endl;
        }
    }
    return flag;
}

bool search_LO_LS(int n, int m, vector<vector<string>>& A, vector<int>& LO, vector<int>& LS)
{
    LO.clear();
    LS.clear();

    for (int i = 0; i < m; i++)
    {
        int level_s = 1;
        for (int j = 0; j < n; j++)
        {
            if (!(A[j][i] == "r"))
            {
                level_s++;
            }
        }

        LS.push_back(level_s);

    }

    for (int i = 0; i < n; i++)
    {
        int level_o = 1;
        for (int j = 0; j < m; j++)
        {
            if ((A[i][j] == "r") && LS[j] > level_o)
            {
                level_o = LS[j];
            }
        }

        LO.push_back(level_o);
    }

    return check_CS(n, m, A, LO, LS);

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
    cout << check_CS(n, m, A, LO, LS) << endl;
    cout << search_LO_LS(n, m, A, LO, LS) << endl;
    for (int i = 0; i < m; i++)
        cout << LS[i];
    cout << endl;
    for (int i = 0; i < n; i++)
        cout << LO[i];


}


