#ifndef TBITSET_H_INCLUDED
#define TBITSET_H_INCLUDED

#define EMALLOCERROR 0

#include <iostream>
#include <stdint.h>
#include <string>

class TBitSet
{
    private:
        uint8_t *data;
        uint8_t length;
        bool overflow;
        void to_alt_code();
    public:
        uint8_t getlength() const;
        TBitSet(uint8_t) throw (int);
        ~TBitSet();
        std::string to_string() const;
        int to_int() const;
        const TBitSet& operator+ (const TBitSet&);
        const TBitSet& operator- (const TBitSet&);

};

void TBitSet::to_alt_code()
{
    for (int i = 0; i < length - 1; i++)
        data[i] = (data[i] == 0) ? 1 : 0;
//    this += 1;
}

uint8_t TBitSet::getlength() const
{
    return length;
}

TBitSet::TBitSet(uint8_t length) throw (int)
{
    if (!( (length > 64) || (length % 8 != 0)))
    {
        data = new uint8_t[length];
        overflow = false;
        for (uint8_t i = 0; i < length; i++)
            data[i] = 0;
    }
    else
        throw EMALLOCERROR;
}

TBitSet::~TBitSet()
{
    delete data;
}

std::string TBitSet::to_string() const
{
    return "string";
}

int TBitSet::to_int() const
{
    return 10;
}

const TBitSet& operator+ (const TBitSet& i)
{
    return i;
}

const TBitSet operator- (const TBitSet& i)
{
    TBitSet r( i.getlength() );
    r = -i.to_int();
    return r;
}

#endif // TBITSET_H_INCLUDED
