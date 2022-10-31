#include<vector>
#include<iostream>
#include<set>
#include<map>
#include<fstream>
using namespace std;

class chinese_wall
{
private:

    int n, m, f_count;
    map<string, set<int>> f;
    vector<set<string>> cl;
    map<pair<int, int>, set<char>> history;
    

public:

    chinese_wall(int n, int m, int f_count, map<string, set<int>> f, vector<set<string>> cl)
    {
        this->n = n;
        this->m = m;
        this->f = f;
        this->cl = cl;
        this->f_count;
    }

    chinese_wall(string file_name)
    {
        try
        {
            ifstream fin(file_name + ".txt");
            if (fin.is_open())
            {
                fin >> n >> m >> f_count;
                string name_company;
                set<int> buf;
                int num_obj;
                for (int i = 0; i < f_count;i++)
                {
                    fin >> name_company;
                    while(fin.get() != '\n')
                    {
                        fin >> num_obj;
                        buf.insert(num_obj);
                    }
                    f[name_company] = buf;
                    buf.clear();
                }
                set<string> buf1;
                int cl_count;
                fin >> cl_count;
                if (cl_count != 0)
                {
                    for (int i = 0; i < cl_count; i++)
                    {
                        fin >> name_company;
                        buf1.insert(name_company);
                        while (fin.get() != '\n')
                        {
                            fin >> name_company;
                            buf1.insert(name_company);
                        }
                        cl.push_back(buf1);
                        buf1.clear();
                    }
                }
            }
            else
            {
                cout << "File not found!" << endl;
                terminate();
            }
        }
        catch (...)
        {
            cout << "Error!";
            terminate();
        }
    }

    void start()
    {
        history.clear();
    }

    bool check_read(int i, int j)
    {
        pair<int, int> pair1(pair(i, j));
        if (history.contains(pair1))
        {
            return true;
        }
        else
        {
            string name_com_j = get_name_company(j);
            string name_com_k;
            for (int k = 0; k < m; k++)
            {
                name_com_k = get_name_company(k);
                if (history.contains(pair(i, k)))

                {
                    if (name_com_k != name_com_j && get_num_cl(name_com_j) == get_num_cl(name_com_j))
                    {
                        return false;
                    }
                    if (name_com_k == name_com_j)
                    {
                        return true;
                    }
                }
            }
            return true;
        }
    }

    void read(int i, int j)
    {
        if (check_read(i, j))
        {
            history[pair(i, j)].insert('r');
            cout << "accepted\n";
        }
        else
        {
            cout << "refused\n";
        }
    }

    string get_name_company(int j)
    {
        try
        {
            for (auto k : f)
            {
                if (k.second.contains(j))
                {
                    return k.first;
                }
            }
        }
        catch (...)
        {
            cout << "Error!";
            terminate();
        }
        
    }

    int get_num_cl(string name_com)
    {
        try 
        {
            for (int i = 0; i < cl.size(); i++)
            {
                if (cl[i].contains(name_com))
                {
                    return i;
                }
            }
        }
        catch (...)
        {
            cout << "Error!";
            terminate();
        }
    }

    void write(int i, int j)
    {
        if (check_read(i, j))
        {
            history[pair(i, j)].insert('w');
            cout << "accepted\n";
        }
        else
        {
            cout << "refused\n";
        }
    }

    void report_sbj(int i)
    {
        pair<int, int> pair1;
        for (int j = 0; j < m; j++)
        {   
            pair1 = pair(i, j);
            if (history.contains(pair1))
            {
                string name_com = get_name_company(j);
                for (auto k : history[pair1])
                {
                    cout << k << " - " << "Obj number: " << j << " from " << name_com << endl;
                }
            }
        }
    }

    void report_obj(int j)
    {
        pair<int, int> pair1;
        for (int i = 0; i < n; i++)
        {
            pair1 = pair(i, j);
            if (history.contains(pair1))
            {
                for (auto k : history[pair1])
                {
                    cout << "Sbj number " << i << " - " << k << endl;
                }
            }
        }
    }

    void report_brief_case(string name_com)
    {
        for (auto i : f[name_com])
        {
            cout << i << " ";
        }
        cout << endl;
    }

};
int main()
{
    chinese_wall cw1("input1");

    cw1.report_brief_case("GasProm");
    cw1.read(1, 1);
    cw1.write(1, 1);
    cw1.write(1, 2);
    cw1.report_sbj(1);
    cw1.report_obj(1);
    cw1.start();
    cw1.write(1, 2);
    cw1.report_sbj(1);
}