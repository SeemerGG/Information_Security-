#include<map>
#include<set>
#include<fstream>
#include<iostream>
#include<vector>

using namespace std;

class TAM
{
private:
    
    map<pair<int, int>, set<char>> A;
    map<pair<int, int>, set<char>> A_old;
    set<int> active_sbj;
    int n, m;

public:

    TAM(string file_name)
    {
        try
        {
            ifstream fin(file_name);
            if (fin.is_open())
            {
                fin >> n >> m;
                if (n >= 3 && m >= 3 && n <= 10000 && m <= 10000)
                {
                    int i, j;
                    string rules;
                    set<char> buf;
                    while (!fin.eof())
                    {
                        fin >> i >> j >> rules;
                        if (!active_sbj.contains(i))
                        {
                            active_sbj.insert(i);
                        }
                        if (rules.size() == 2)
                        {
                            buf.insert(rules[0]);
                            buf.insert(rules[1]);
                        }
                        else
                        {
                            buf.insert(rules[0]);
                        }
                        A[pair(i, j)] = buf;
                        fin.ignore(1, '\n');
                        buf.clear();
                    }
                    A_old = A;
                }
                else
                {
                    cout << "Incorrect size matrix!";
                    terminate();
                }
            }
            else
            {
                cout << "File not found!";
                terminate();
            }
        }
        catch (...)
        {
            cout << "Error!!!" << "\n" << "Check the entered data!";
            terminate();
        }
    }

    void add_rule(int i, int j, char p)
    {
        if (A_old[pair(i, j)].contains(p) && active_sbj.contains(i))
        {
            A[pair(i, j)].insert(p);
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void del_rule(int i, int j, char p)
    {
        if (active_sbj.contains(i) && A.contains(pair(i, j)))
        {
             A[pair(i, j)].erase(p);
             cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void add_sub(string name)
    {
        for (int i = 0; i < n;i++)
        {
            if (!active_sbj.contains(i))
            {
                active_sbj.insert(i);
                cout << name << " has been registrated as " << i;
                return;
            }
        }
        cout << name << " has not registreted!" << endl;
    }

    void delete_sub(int i)
    {
        if (active_sbj.contains(i))
        {
            for (int j = 0; j < m; j++)
            {
                if (A.contains(pair(i, j)))
                {
                    A[pair(i, j)].clear();
                }
            }
            active_sbj.erase(i);
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not execute!" << endl;
        }
    }

    int out_n()
    {
        return n;
    }

    int out_m()
    {
        return m;
    }

    int count_active_sbj()
    {
        return active_sbj.size();
    }

    vector<int> users_obj_t(int t)
    {
        vector<int> buf;
        for (auto i : active_sbj)
        {
            if (A.contains(pair(i, t)))
            {
                if (!A[pair(i, t)].empty())
                {
                    buf.push_back(i);
                }
            }
        }
        if (!buf.empty())
        {
            return buf;
        }
        else
        {
            cout << "It not had access." << endl;
        }
    }

};

float perc_occupancy(TAM sys)
{
    return sys.count_active_sbj() * 100.0 / (sys.out_n() * sys.out_m());
}


int main()
{
    TAM chw1("input.txt");
    //chw1.add_sub("Bell");
    //vector<int> fjd = chw1.users_obj_t(1);
}
