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
    vector<set<int>> f;
    map<int, set<int>> cl;

public:
    chinese_wall(string file_name)
    {
        try
        {
            ifstream fin(file_name + ".txt");
            if (fin.is_open())
            {
                fin >> n >> m >> f_count;
                set<int> buf;
                int num;
                for (int i = 0; i < f_count; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        fin >> num;
                        buf.insert(num);
                    }
                    f.push_back(buf);
                    buf.clear();
                }
                fin.ignore(1);
                char buf1;
                int  num_sbj = 0;
                while (!fin.eof())
                {
                    fin.get(buf1);
                    if (buf1 == '\n')
                    {
                        cl[num_sbj] = buf;
                        buf.clear();
                        num_sbj++;
                    }
                    else
                    {
                        if (buf1 != ' ')
                        {
                            buf.insert(buf1 - '0');
                        }
                        else
                        {
                            fin.ignore(1);
                        }
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


};
int main()
{
    
}


