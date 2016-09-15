#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(8);
    s = -16;
    std::cout << s.to_string() << std::endl;
    s++;
    std::cout << s.to_string() << std::endl;
    int n;
    std::cout << s.to_int() << std::endl;
    std::cin >> n;
    return 0;
}
