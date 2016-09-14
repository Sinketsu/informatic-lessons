#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(8);
    s = -11;
    std::cout << s.to_string() << std::endl;
    //s++;
    int n;
    std::cout << s.to_string() << std::endl;
    std::cin >> n;
    return 0;
}
