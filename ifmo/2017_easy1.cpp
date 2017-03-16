#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

string get_pattern(string in)
{
    return in.replace(1,      // position
                      2,      // length
                      "??");  // fill_buffer
}

int get_int(string in)
{
    return (int)(in[1] - '0') * 10 + (int)(in[2] - '0');
}

string fill_to_normal(int a)
{
    if (a < 10)
        return "0" + to_string(a);
    return to_string(a);
}

int next_int(vector<bool>& v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == false)
        {
            v[i] = true;
            return i;
        }
    }
    return -1;
}

int n;
int c;

string s;

bool flag = true;

vector<string> arr;
map<string, vector<bool> > m;

ifstream in("input.txt");
ofstream out("output.txt");

int main()
{
    in >> n;
    for(int i = 0; i < n; i++)
    {
        in >> s;
        arr.push_back(s);
        if (s.find('?') == string::npos)
        {
            c = get_int(s);
            s = get_pattern(s);
            if (m[s].empty()) // if the first time arrival
            {
                m[s].resize(100, false);
                m[s][c] = true;
            }
            else
            {
                if (m[s][c] == true)
                {
                    flag = false;
                    break;
                }
                m[s][c] = true;
            }
        }
        else
        {
            if (m[s].empty())
                m[s].resize(100, false); // only for convenience
        }
    }
    in.close();

    for(int i = 0; i < arr.size(); i++)
    {
        s = arr[i];
        if (s.find('?') != string::npos)
        {
            c = next_int(m[s]);
            if (c == -1)
            {
                flag = false;
                break;
            }

            s = s[0] + fill_to_normal(c) + s[3] + s[4] + s[5] + s[6]; // because we cant write s[3:] :(
            arr[i] = s;
        }
    }
    if (!flag)
    {
        out << "NO" << endl;
        out.flush();
        out.close();
        return 0;
    }

    out << "YES" << endl;
    for(int i = 0; i < arr.size(); i++)
        out << arr[i] << endl;
    out.flush();
    out.close();

    return 0;
}



















