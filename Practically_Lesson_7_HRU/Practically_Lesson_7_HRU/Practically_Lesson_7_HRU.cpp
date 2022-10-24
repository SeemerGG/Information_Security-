#include<vector>
#include<string>
#include<set>
#include <iostream>
#include<fstream>

using namespace std;

class HRU
{
private:
    vector<vector<set<char>>> A;
    int n, m;

    void create_obj()
    {
        for (int i = 0; i < n; i++)
        {
            set<char> buf;
            A[i].push_back(buf);
        }
        m++;
    }

    void create_sub()
    {
        vector<set<char>> buf;
        for (int i = 0; i < m; i++)
        {
            set<char> buf_set;
            buf.push_back(buf_set);
        }
        A.push_back(buf);
        n++;
    }

    void destroy_obj(int k)
    {
        for (auto i : A)
        {
            auto iter = i.cbegin();
            i.erase(iter + k);
        }
        m--;
    }

    void destroy_sbj(int k)
    {
        auto iter = A.cbegin();
        A.erase(iter + k);
        n--;

    }

    void enter_p(char p, int k, int l)
    {
        A[k][l].insert(p);
    }

    void delete_p(char p, int k, int l)
    {
        A[k][l].erase(p);
    }

    void determing_op(ifstream &fin, string com)
    {
        if (com == "cco")
        {
            create_obj();
        }
        if (com == "ccs")
        {
            create_sub();
        }
        if (com == "cdo")
        {
            int i;
            fin >> i;
            destroy_obj(i);
        }
        if (com == "cds")
        {
            int i;
            fin >> i;
            destroy_sbj(i);
        }
        if (com == "cer")
        {
            char p;
            int i, j;
            fin >> p >> i >> j;
            enter_p(p, i, j);
        }
        if (com == "cdr")
        {
            char p;
            int i, j;
            fin >> p >> i >> j;
            delete_p(p, i, j);
        }
    }

    void output_res()
    {
        ofstream fout("rzlt.txt");
        for (auto i : A)
        {
            for (auto j : i)
            {
                for (auto l : j)
                {
                    fout << l;
                }
                fout << " ";
            }
            fout << endl;
        }
        fout.close();
    }

public:
    HRU(string file_name) //файл оканчивается табуляцией 
    {   
        ifstream fin("environ.txt");
        if (fin.is_open())
        {
            fin >> n;
            fin >> m;
            char  sym;
            fin.get(sym);
            for (int i = 0; i < n; i++)
            {
                vector<set<char>> buf;
                set<char> buf_set;
                while (true)
                {
                    fin.get(sym);
                    if (sym == '\n')
                    {
                        buf.push_back(buf_set);
                        A.push_back(buf);
                        break;
                    }
                    if (sym == ' ')
                    {
                        buf.push_back(buf_set);
                        buf_set.clear();
                    }
                    else
                    {
                        buf_set.insert(sym);
                    }
                }
            }
        }
        else
        {
            cout << "File not found!";
            exit;
        }
    }

    void interpretator(string file_name)
    {
        ifstream fin(file_name);
        if (fin.is_open())
        {
            int num_cm = 1;
            while (!fin.eof())
            {
                string str;
                fin >> str;
                if (str == "if")
                {
                    char p;
                    int i, j;
                    fin >> p >> i >> j;
                    if (A[i][j].contains(p))
                    {
                        string com;
                        fin >> com;
                        determing_op(fin, com);
                        num_cm++;
                    }
                    else
                    {
                        cout << "Command " << num_cm << "not executed!" << endl;
                        fin.ignore(numeric_limits<streamsize> :: max(), '\n');
                        num_cm++;
                    }
                }
                else
                {
                    determing_op(fin, str);
                    num_cm++;
                }
            }
            output_res();
        }
        else
        {
            cout << "File is not find!" << endl;
            exit;
        }
    }

    void output()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                for (auto i : A[i][j])
                    cout << i;
                cout << " ";
            } 
            cout << endl;
        }
    }

};

int main()
{
    string str = "environ.txt";
    HRU hru1(str);
    hru1.interpretator("prgrm.txt");
    hru1.output();
}