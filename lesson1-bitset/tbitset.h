#ifndef TBITSET_H_INCLUDED
#define TBITSET_H_INCLUDED

#include <iostream>
#include <stdint.h>
#include <string>
#include <math.h>
#include <exception>

#define getbit(x,pos)   ( ((x) & ( 0x1 << (pos) )) !=0 )

class EMALLOCERROR : std::exception
{
    public:
        std::string what()
        {
            return std::string("Length not in 0..64 range.");
        }
};
class EVALUEOVERFLOW : std::exception
{
    public:
        std::string what()
        {
            return std::string("The value requires more space than is available.");
        }
};

class TBitSet
{
    private:
        uint8_t *data;
        uint8_t length;
        bool overflow;
        void to_alt_code();
        void to_direct_code();
        void clear_data();
        void resize(uint8_t);
        void shl(uint8_t);
        void shr(uint8_t);
    public:
        uint8_t getlength();
        TBitSet(uint8_t) throw (EMALLOCERROR);
        std::string to_string();
        int64_t to_int();
        bool get_overflow_flag();
        TBitSet& operator++ (int);
        TBitSet& operator-- (int);
        TBitSet& operator+= (TBitSet&);
        TBitSet& operator-= (TBitSet&);
        TBitSet& operator<< (int);
        TBitSet& operator>> (int);
        uint8_t& operator[] (int);
        TBitSet& operator= (int64_t) throw (EVALUEOVERFLOW);
};

void TBitSet::to_alt_code()
{
    for (uint8_t i = 1; i < length; i++)
            data[i] = (data[i] == 0) ? 1 : 0;
    data[0] = 1;
    this->operator++(1);
}

void TBitSet::to_direct_code()
{

    if (data[0] == 1)
    {
        bool flag = false;
        this->operator--(1);
        for (uint8_t i = 0; i < length; i++)
                data[i] = (data[i] == 0) ? 1 : 0;
        for (uint8_t i = 1; i < length; i++)
            if (data[i] != 0)
            {
                flag = true;
            }
        if (flag)
            data[0] = 0;
    }
}

void TBitSet::shl(uint8_t c)
{
    for (int i = 0; i < length - c; i++)
        data[i] = data[i + c];
    for (int i = length - c; i < length; i++)
        data[i] = 0;
}

void TBitSet::shr(uint8_t c)
{
    for (int i = length - c; i >= 0; i--)
        data[i + c] = data[i];
    for (int i = 0; i < c; i++)
        data[i] = 0;
}

void TBitSet::clear_data()
{
    for (uint8_t i = 0; i < length; i++)
            data[i] = 0;
}

void TBitSet::resize(uint8_t len)
{
    int64_t a = to_int();
    data = new uint8_t[len];
    length = len;
    clear_data();
    this->operator=(a);
}

uint8_t TBitSet::getlength()
{
    return length;
}

bool TBitSet::get_overflow_flag()
{
    return overflow;
}

TBitSet::TBitSet(uint8_t length) throw (EMALLOCERROR)
{
    if (!( (length > 64)))
    {
        this->length = length;
        data = new uint8_t[length];
        overflow = false;
        clear_data();
    }
    else
        throw EMALLOCERROR();
}

std::string TBitSet::to_string()
{
    std::string s = "";
    for (int i = 0; i < length; i++)
        s += char(data[i] + 48);
    return s;
}

int64_t TBitSet::to_int()
{
    if (data[0] == 0)
    {
        int64_t value = 0;
        for (int8_t i = 0; i < length; i++)
        {
            value += (int)data[i] * (int)pow(2, length - i - 1);
        }
        return value;
    }
    else
    {
        int64_t value = 0;
        to_direct_code();
        for (int8_t i = 0; i < length; i++)
        {
            value += (int)data[i] * (int)pow(2, length - i - 1);
        }
        to_alt_code();
        return -value;
    }

}

TBitSet& TBitSet::operator++ (int value)
{
    data[length - 1]++;
    for (int i = length - 1; i >= 0; i--)
    {
        if (data[i] == 2)
        {
            data[i] = 0;
            if (i >= 1)
                data[i - 1]++;
            else
                {overflow = true; return *this;}
        }
    }
    overflow = false;
    return *this;
}

TBitSet& TBitSet::operator-- (int value)
{
    bool flag = true;
    overflow = false;
    for (int i = length - 1; i >= 0; i--)
    {
        if (flag && (data[i] == 1))
        {
            data[i] = 0;
            flag = false;
        }
        else
        if (flag && (data[i] == 0))
        {
            data[i] = 1;
        }
        if (flag == false)
            break;
    }
    if (flag)
        overflow = true;
    return *this;
}

TBitSet& TBitSet::operator+= (TBitSet& value)
{
    if (this == &value)
    {
        shl(1);
        return *this;
    }
    resize(std::max(length, value.getlength()));
    int8_t l = std::min(length, value.getlength());
    int8_t delta = length - value.getlength();
    for (int8_t i = l - 1; i >= 0; i--)
    {
        data[i + delta] += value[i];

        if (data[i + delta] >= 2)
        {
            data[i + delta] -= 2;
            if (i >= 1)
            {
                data[i + delta - 1]++;
            }
            else
            {
                if (length == value.getlength())
                {
                    overflow = true;
                    return *this;
                }
                else
                {
                    data[delta - 1]++;
                    for (int8_t k = delta - 1; k >= 0; k--)
                    {
                        if (data[k] == 2)
                        {
                            data[k] = 0;
                            if (k >= 1)
                                data[k - 1]++;
                            else
                            {
                                overflow = true;
                                return *this;
                            }
                        }
                    }
                }
            }
        }
    }
    overflow = false;
    return *this;
}

TBitSet& TBitSet::operator-=(TBitSet& value)
{
    if (this == &value)
    {
        *this = 0;
        return *this;
    }
    value = -(value.to_int());
    this->operator+=(value);
    return *this;
}

TBitSet& TBitSet::operator<<(int len)
{
    shl(len);
    return *this;
}

TBitSet& TBitSet::operator>>(int len)
{
    shr(len);
    return *this;
}

uint8_t& TBitSet::operator[] (int i)
{
    return data[i];
}

TBitSet& TBitSet::operator= (int64_t value) throw (EVALUEOVERFLOW)
{
    if ((value > 0) && (value > (pow(2, length - 1) - 1) ))
        throw EVALUEOVERFLOW();
    if ((value < 0) && (value < -(pow(2, length - 1)) ))
        throw EVALUEOVERFLOW();

    if (value >= 0)
    {
        for (uint8_t i = 0; i < length; i++){
            data[i] = getbit(value, length - i - 1);
        }
    }
    else
    {
        value = -value;
        for (uint8_t i = 0; i < length; i++)
            data[i] = getbit(value, length - i - 1);
        to_alt_code();
    }
    overflow = false;
}

TBitSet operator+ (TBitSet& left, TBitSet& right)
{
    return TBitSet(left) += right;
}

TBitSet& operator- (TBitSet& left, TBitSet& right)
{
    return TBitSet(left) -= right;
}

#endif // TBITSET_H_INCLUDED
