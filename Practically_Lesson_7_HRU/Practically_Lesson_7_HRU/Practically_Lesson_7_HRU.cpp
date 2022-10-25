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
    vector<vector<set<char>>> A_old;
    int n, m;

    void create_obj()
    {
        if (m + 1 <= A_old[0].size())
        {
            for (int i = 0; i < n; i++)
            {
                set<char> buf;
                A[i].push_back(buf);
            }
            m++;
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void create_sub()
    {
        if (n + 1 <= A_old.size())
        {
            vector<set<char>> buf;
            for (int i = 0; i < m; i++)
            {
                set<char> buf_set;
                buf.push_back(buf_set);
            }
            A.push_back(buf);
            n++;
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void destroy_obj(int k)
    {
        if (k < m) 
        {
            for (auto i : A)
            {
                auto iter = i.cbegin();
                i.erase(iter + k);
            }
            m--;
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
        
    }

    void destroy_sbj(int k)
    {
        if (k < n)
        {
            auto iter = A.cbegin();
            A.erase(iter + k);
            n--;
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }

    }

    void enter_p(char p, int k, int l)
    {
        if (A_old[k][l].contains(p))
        {
            A[k][l].insert(p);
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not executed!" << endl;
        }
    }

    void delete_p(char p, int k, int l)
    {
        if (A[k][l].contains(p))
        {
            A[k][l].erase(p);
            cout << "Command executed!" << endl;
        }
        else
        {
            cout << "Command not execeted!" << endl;
        }
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

    //Задание 2
    vector<int> a()
    {
        bool flag;
        vector<int> buf;
        for (int j = 0; j < m; j++)
        {
            flag = true;
            for (int i = 0; i < n; i++)
            {
                if (!A[i][j].empty())
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                buf.push_back(j);
            }
        }
        return buf;
    }

    vector<int> b()
    {
        bool flag;
        vector<int> buf;
        for (int i = 0; i < n; i++)
        {
            flag = true;
            for (int j = 0; j < m; j++)
            {
                if (!A[i][j].empty())
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                buf.push_back(i);
            }
        }
        return buf;
    }

    vector<int> c()
    {
        bool flag;
        vector<int> buf;
        for (int i = 0; i < n; i++)
        {
            flag = true;
            for (int j = 0; j < m; j++)
            {
                if (A[i][j].empty() || (A[i][j].contains('w') && !A[i][j].contains('r')) || (!A[i][j].contains('w') && A[i][j].contains('r')))
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
            {
                buf.push_back(i);
            }
        }
        return buf;
    }

    vector<vector<int>> d()
    {
        vector<vector<int>> buf;
        for (int j = 0; j < m; j++)
        {
            vector<int> buf1;
            for (int i = 0; i < n; i++)
            {
                if (A[i][j].contains('w'))
                {
                    buf1.push_back(i);
                }
            }
            buf.push_back(buf1);
        }
        return buf;
    }

    vector<int> e()
    {
        bool flag;
        vector<int> buf;
        for (int i = 0; i < n; i++)
        {
            flag = true;
            int count = 0;
            for (int j = 0; j < m; j++)
            {
                if (A[i][j].contains('w') && A[i][j].contains('r'))
                {
                    count++;
                }
                else if (A[i][j].contains('w'))
                {
                    flag = false;
                }
            }
            if (flag && count == 1)
            {
                buf.push_back(i);
            }
        }
        return buf;
    }
    void output_vector_int(vector<int> buf)
    {
        for (int i = 0; i < buf.size(); i++)
        {
            cout << buf[i] << " ";
        }
        cout << endl;
    }

public:
    HRU(string file_name) //файл оканчивается табуляцией 
    {   
        ifstream fin(file_name);
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
            copy(A.begin(), A.end(), back_inserter(A_old));
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
                    }
                    else
                    {
                        fin.ignore(numeric_limits<streamsize> :: max(), '\n');
                    }
                }
                else
                {
                    determing_op(fin, str);
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

    void task2()
    {
        vector<int> buf = a();
        cout << "a) ";
        output_vector_int(buf);
        buf = b();
        cout << "b) ";
        output_vector_int(buf);
        buf = c();
        cout << "c) ";
        output_vector_int(buf);
        vector<vector<int>> buf2 = d();
        cout << "d) " << endl;
        for (int i = 0; i < buf2.size(); i++)
        {
            output_vector_int(buf2[i]);
        }
        buf = e();
        cout << "e) ";
        output_vector_int(buf);
    }

};

int main()
{
    HRU hru1("environ.txt");
    hru1.interpretator("prgrm.txt");
    //hru1.output();
    HRU ne_hru("access_matr.txt");
    ne_hru.task2();
    
}