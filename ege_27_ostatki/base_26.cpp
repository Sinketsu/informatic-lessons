#include<iostream>

int n;
int x;
int m2, m13, m26;
int absolute_max;

int main()
{
    m2 = 0;
    m13 = 0;
    m26 = 0;
    absolute_max = 0;
    std::ios_base::sync_with_stdio(0);

    std::cin >> n;
    for (int i = 0; i < n; i++)
    {
        std::cin >> x;
        if (x % 26 != 0)
        {
            if (x % 13 == 0 && x > m13)
                m13 = x;
            if (x % 2 == 0 && x > m2)
                m2 = x;
            if (x > absolute_max)
                absolute_max = x;
        } else
        {
            if (x > m26)
            {
                if (m26 > absolute_max)
                    absolute_max = m26;
                m26 = x;
            } else
            {
                if (x > absolute_max)
                    absolute_max = x;
            }
        }
    }
    std::cout << std::max(0, std::max(m26 * absolute_max, m2 * m13)) << std::endl;
    return 0;
}