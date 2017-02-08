#include <iostream>
#include <map>

using namespace std;

long long n;
int d, k;
map<int, int> m;

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(NULL);
    cin >> n;
    for(long long i = 0; i < n; i++)
    {
        cin >> d >> k;
        k %= d;
        m[k]++;
    }
    m[0] = -1;
    long long Max = 0;
    int result;
    for(map<int, int>::iterator i = m.begin(); i != m.end(); i++)
    {
        if (i->second > Max)
        {
            Max = i->second;
            result = i->first;
        }
        if (i->second == Max)
            if (i->first > result)
                result = i->first;
    }
    cout << (Max != 0 ? result : 0) << endl;

    return 0;
}
