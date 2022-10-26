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
            terminate();
        }
    }

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

    friend ostream& operator<<(ostream& out, HRU& h) {
        for (auto i : h.A)
        {
            for (auto j : i)
            {
                for (auto l : j)
                {
                    out << l;
                }
                out << " ";
            }
            out << endl;
        }

        return out;
    }

    void output_res()
    {
        ofstream fout("rzlt.txt");
        fout << *this;
        fout.close();
    }

    set<char> output_p(int i, int j)
    {
        return A[i][j];
    }

};

void determing_op(ifstream& fin, string com, HRU& obj)
{
    if (com == "cco")
    {
        obj.create_obj();
    }
    if (com == "ccs")
    {
        obj.create_sub();
    }
    if (com == "cdo")
    {
        int i;
        fin >> i;
        obj.destroy_obj(i);
    }
    if (com == "cds")
    {
        int i;
        fin >> i;
        obj.destroy_sbj(i);
    }
    if (com == "cer")
    {
        char p;
        int i, j;
        fin >> p >> i >> j;
        obj.enter_p(p, i, j);
    }
    if (com == "cdr")
    {
        char p;
        int i, j;
        fin >> p >> i >> j;
        obj.delete_p(p, i, j);
    }
}

void interpretator(string file_name, HRU &obj)
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
                if (obj.output_p(i,j).contains(p))
                {
                    string com;
                    fin >> com;
                    determing_op(fin, com, obj);
                }
                else
                {
                    fin.ignore(numeric_limits<streamsize> ::max(), '\n');
                }
            }
            else
            {
                determing_op(fin, str, obj);
            }
        }
        obj.output_res();
    }
    else
    {
        cout << "File is not find!" << endl;
        terminate();
    }
}

int main()
{
    HRU hru1("environ.txt");
    cout << hru1;
    interpretator("prgrm.txt", hru1); 
    cout << hru1;
}