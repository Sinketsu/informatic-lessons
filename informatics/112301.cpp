#include <iostream>

int n;
int k, m;
int r;
int t;

int main(int argc, char** argv)
{
    std::ios_base::sync_with_stdio(0);
    std::cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    std::cin >> k >> m;
    k--;
    m--;
    std::cin >> r;
    r %= (m - k + 1);

    for (int j = 0; j < r; j++)
    {
        t = arr[k];
        for (int i = k; i < m; i++)
            arr[i] = arr[i + 1];

        arr[m] = t;
    }

    for (int i = 0; i < n; i++)
        std::cout << arr[i] << ' ';
    return 0;
}
