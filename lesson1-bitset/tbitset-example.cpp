#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(8);
    TBitSet ss(8);
    s = -112;
    std::cout << s.to_string() << std::endl;
    ss = -1;
    std::cout << ss.to_string() << std::endl;
    s += ss;
    std::cout << s.to_string() << std::endl;
    std::cout << s.to_int() << std::endl;
    int n;
    std::cin >> n;
    return 0;
}
