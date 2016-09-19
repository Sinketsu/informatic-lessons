#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(6);
    TBitSet g(6);

    std::cout << s.to_string() << std::endl;
    s -= g;
    std::cout << s.to_string() << std::endl;
    std::cout << s.to_int() << std::endl;

    return 0;
}
