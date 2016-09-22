#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(6);
    TBitSet g(5);
    TBitSet t(3);
    s = -12;
    g = -6;
    std::cout << s.to_string() << std::endl;
    std::cout << g.to_string() << std::endl;
    g += s;
    std::cout << g.to_int() << std::endl;
    //std::cout << t.to_string() << std::endl;
    std::cout << s.to_string() << std::endl;
    std::cout << g.to_string() << std::endl;

    return 0;
}
