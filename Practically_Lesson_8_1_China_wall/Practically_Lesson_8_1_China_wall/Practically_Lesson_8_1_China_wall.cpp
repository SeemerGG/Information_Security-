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
            ifstream fin(file_name + ".txt");
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
                        //fin.ignore(1, '\n');
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
        pair<int, int> pair = make_pair(i, j);
        if (A_old[pair].contains(p) && active_sbj.contains(i))
        {
            A[pair].insert(p);
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void del_rule(int i, int j, char p)
    {
        pair<int, int> pair = make_pair(i, j);
        if (active_sbj.contains(i) && A.contains(pair))
        {
             A[pair].erase(p);
             if (A[pair].empty())
             {
                 A.erase(pair);
             }
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
                cout << name << " has been registrated as " << i << endl;
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
                pair<int, int> pair = make_pair(i, j);
                if (A.contains(pair))
                {
                    A.erase(pair);
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

    int out_size()
    {
        return A.size();
    }

    vector<int> users_obj_t(int t)
    {
        vector<int> buf;
        for (auto i : active_sbj)
        {
            pair<int, int> pair = make_pair(i, t);
            if (A.contains(pair))
            {
                if (!A[pair].empty())
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

    friend ostream& operator<<(ostream& out, TAM sys)
    {
        for (auto i : sys.A)
        {
            out << i.first.first << " " << i.first.second << " ";
            for (auto j : i.second)
            {
                out << j;
            }
            out << endl;
        }
        return out;
    }

    void output_file(string file_name)
    {
        ofstream fout(file_name + ".txt");
        fout << *this;
        fout.close();
    }

};

float perc_occupancy(TAM sys)
{
    return sys.out_size() * 100.0 / (sys.out_n() * sys.out_m());
}

int main()
{
    TAM chw1("input");
    cout << chw1;
    chw1.delete_sub(1);
    cout << chw1;
    chw1.add_sub("Van");
    cout << chw1;
    chw1.add_rule(1, 1, 'w');
    cout << chw1;
    chw1.del_rule(0, 1, 'w');
    cout << chw1;
    chw1.output_file("rezult");
    vector<int> vector = chw1.users_obj_t(2);
    for (auto i : vector)
    {
        cout << i << " ";
    }
    cout << endl;
    cout << "Filling is the matrix: " << perc_occupancy(chw1) << "%";

}
