#include <iostream>
#include <climits>

int n;  // count of elements
int c;  // count of chain
int z;  // value of chain elem
int c2; // second counter
int z2; // second value of chain
int t;  // temp

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin >> n;

    c ^= c;
    z = INT_MIN;
    c2 ^= c2;
    z2 = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        std::cin >> t;
        if (t != z2)
        {
            if (c2 > c)
            {
                c = c2;
                z = z2;
            }

            c2 ^= c2;
            c2++;
            z2 = t;
        }
        else
            c2++;
    }
    if (c != 0) // != works quickly then == in most cases
        std::cout << z << ' ' << c << std::endl;
    else
        std::cout << z2 << ' ' << c2 << std::endl;
    return 0;
}




