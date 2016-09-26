#include <iostream>
#include <vector>

#define getbit(x,pos) ( ((x) & ( 0x1 << (pos) )) !=0 )

using namespace std;

template<typename T>
void showdump(T* pointer)
{
    size_t size = sizeof(T);
    vector< vector<char> > arr;
    arr.resize(size);
    for (size_t i = 0; i < size; i++)
    {
        for (short int k = 7; k >= 0; k--)
        {
            arr[i].push_back(getbit((*(pointer + i)), k) + 48);
        }
    }

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        for (int k = 0; k < 8; k++)
        {
            cout << arr[i][k];
        }
        cout << ' ';
    }
    cout << endl;
}



int main()
{
    int a;
    a = 10;
    showdump<int>(&a);

    return 0;
}
