#include "tbitset.h"

int main(int argc, char **argv)
{
    TBitSet s(8);
    try
    {
        s = 12;
    }
    catch (EVALUEOVERFLOW& e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << s.to_string() << std::endl;
    s >> 2;
    std::cout << s.to_string() << std::endl;

    return 0;
}
