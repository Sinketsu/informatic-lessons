#include <iostream>
#include <string>

using namespace std;

string s;
int local_max;
int char_count = 'Z' - 'A' + 1;

bool is_big_char(char c)
{
    return (c >= 'A' && c <= 'Z');
}

bool is_small_char(char c)
{
    return (c >= 'a' && c <= 'z');
}

void find_max(string s)
{
    local_max = 0;
    string temp = "";
    for (int i = 0; i < s.length(); i++)
    {
        if ((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z'))
            temp += s[i];
        else
        {
            if (temp.length() > local_max)
                local_max = temp.length();
            temp.clear();
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    getline(cin, s);
    find_max(s);
    for (int i = 0; i < s.length(); i++)
    {
        if (is_big_char(s[i]))
            s[i] = (((s[i] - 'A') +    // номер буквы в алфавите
                    char_count +       // количество букв в англ. алфавите для операции %
                    local_max) % char_count) + // производим расшифровку
                    'A';
        if (is_small_char(s[i]))
            s[i] = (((s[i] - 'a') +    // номер буквы в алфавите
                    char_count +       // количество букв в англ. алфавите для операции %
                    local_max) % char_count) + // производим расшифровку
                    'a';
    }
    cout << s << endl;
    return 0;
}