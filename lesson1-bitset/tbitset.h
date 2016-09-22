#ifndef TBITSET_H_INCLUDED
#define TBITSET_H_INCLUDED

#include <iostream>
#include <stdint.h>
#include <string>
#include <sstream>
#include <math.h>
#include <exception>

#define getbit(x,pos)   ( ((x) & ( 0x1 << (pos) )) !=0 )

class EMallocException : std::exception
{
    private: int length_;
    public:
        EMallocException(int64_t i) : length_(i) {};
        std::string what()
        {
            std::stringstream ss;
            ss << "Your length_ " << length_ << " not in range 1..64.";
            return ss.str();
        }
};

class EValueoverflow_Exception : std::exception
{
    private: int64_t value;
    public:
        EValueoverflow_Exception(int64_t i) : value(i) {};
        std::string what()
        {
            std::stringstream ss;
            ss << "Your value " << value << " is too large.";
            return ss.str();
        }
};

class Elength_DiscrepancyException : std::exception
{
    public:
        std::string what()
        {
            std::stringstream ss;
            ss << "The discrepancy between the length_s.";
            return ss.str();
        }
};

class TBitSet
{
    private:
        uint8_t *data_;
        uint8_t length_;
        bool overflow_;
        void to_alt_code();
        void to_direct_code();
        void clear_data();
        void resize(uint8_t);
        void shl(uint8_t);
        void shr(uint8_t);
    public:
        uint8_t get_length() const;
        TBitSet(uint8_t) throw (EMallocException);
        TBitSet(const TBitSet&);
        std::string to_string();
        int64_t to_int();
        bool get_overflow_flag();
        TBitSet& operator++ (int);
        TBitSet& operator-- (int);
        TBitSet& operator+= (TBitSet&) throw (Elength_DiscrepancyException);
        TBitSet& operator-= (TBitSet&);
        TBitSet& operator<< (int);
        TBitSet& operator>> (int);
        uint8_t& operator[] (int) const;
        TBitSet& operator= (int64_t) throw (EValueoverflow_Exception);
};

void TBitSet::to_alt_code()
{
    for (uint8_t i = 1; i < length_; i++)
            data_[i] = (data_[i] == 0) ? 1 : 0;
    data_[0] = 1;
    this->operator++(1);
}

void TBitSet::to_direct_code()
{

    if (data_[0] == 1)
    {
        bool flag = false;
        this->operator--(1);
        for (uint8_t i = 0; i < length_; i++)
                data_[i] = (data_[i] == 0) ? 1 : 0;
        for (uint8_t i = 1; i < length_; i++)
            if (data_[i] != 0)
            {
                flag = true;
            }
        if (flag)
            data_[0] = 0;
    }
}

void TBitSet::shl(uint8_t c)
{
    for (int i = 1; i < length_ - c; i++)
        data_[i] = data_[i + c];
    for (int i = length_ - c; i < length_; i++)
        data_[i] = 0;
}

void TBitSet::shr(uint8_t c)
{
    for (int i = length_ - c; i >= 1; i--)
        data_[i + c] = data_[i];
    for (int i = 1; i < c; i++)
        data_[i] = 0;
}

void TBitSet::clear_data()
{
    for (uint8_t i = 0; i < length_; i++)
            data_[i] = 0;
}

void TBitSet::resize(uint8_t len)
{
    if (length_ != len)
    {
        int64_t a = to_int();
        data_ = new uint8_t[len];
        length_ = len;
        clear_data();
        *this = a;
    }
}

uint8_t TBitSet::get_length() const
{
    return length_;
}

bool TBitSet::get_overflow_flag()
{
    return overflow_;
}

TBitSet::TBitSet(uint8_t len) throw (EMallocException)
{
    if ((len > 0) && (len <= 64))
    {
        length_ = len;
        data_ = new uint8_t[length_];
        overflow_ = false;
        clear_data();
    }
    else
        throw EMallocException(len);
}

TBitSet::TBitSet(const TBitSet& object)
{
    length_ = object.get_length();
    data_ = new uint8_t[length_];
    for (int8_t i = 0; i < length_; i++)
        data_[i] = object[i];
    overflow_ = false;
}

std::string TBitSet::to_string()
{
    std::string s = "";
    for (int i = 0; i < length_; i++)
        s += char(data_[i] + 48);
    return s;
}

int64_t TBitSet::to_int()
{
    if (data_[0] == 0)
    {
        int64_t value = 0;
        for (int8_t i = 0; i < length_; i++)
        {
            value += (int)data_[i] * (int)pow(2, length_ - i - 1);
        }
        return value;
    }
    else
    {
        int64_t value = 0;
        to_direct_code();
        for (int8_t i = 0; i < length_; i++)
        {
            value += (int)data_[i] * (int)pow(2, length_ - i - 1);
        }
        to_alt_code();
        return -value;
    }

}

TBitSet& TBitSet::operator++ (int value)
{
    data_[length_ - 1]++;
    for (int i = length_ - 1; i >= 0; i--)
    {
        if (data_[i] == 2)
        {
            data_[i] = 0;
            if (i >= 1)
                data_[i - 1]++;
            else
                {overflow_ = true; return *this;}
        }
    }
    overflow_ = false;
    return *this;
}

TBitSet& TBitSet::operator-- (int value)
{
    bool flag = true;
    overflow_ = false;
    for (int i = length_ - 1; i >= 0; i--)
    {
        if (flag && (data_[i] == 1))
        {
            data_[i] = 0;
            flag = false;
        }
        else
        if (flag && (data_[i] == 0))
        {
            data_[i] = 1;
        }
        if (flag == false)
            break;
    }
    if (flag)
        overflow_ = true;
    return *this;
}

TBitSet& TBitSet::operator+= (TBitSet& value) throw(Elength_DiscrepancyException)
{
    if (length_ > value.get_length())
        throw Elength_DiscrepancyException();

    if (this == &value)
    {
        shl(1);
        return *this;
    }

    resize(std::max(length_, value.get_length()));
    int8_t l = std::min(length_, value.get_length());
    int8_t delta = length_ - value.get_length();
    for (int8_t i = l - 1; i >= 0; i--)
    {
        data_[i + delta] += value[i];

        if (data_[i + delta] >= 2)
        {
            data_[i + delta] -= 2;
            if (i >= 1)
            {
                data_[i + delta - 1]++;
            }
            else
            {
                overflow_ = true;
                return *this;
            }
        }
    }
    overflow_ = false;
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

uint8_t& TBitSet::operator[] (int i) const
{
    return data_[i];
}

TBitSet& TBitSet::operator= (int64_t value) throw (EValueoverflow_Exception)
{
    if ((value > 0) && (value > (pow(2, length_ - 1) - 1) ))
        throw EValueoverflow_Exception(value);
    if ((value < 0) && (value < -(pow(2, length_ - 1)) ))
        throw EValueoverflow_Exception(value);

    if (value == -(pow(2, length_ - 1)))
    {
        clear_data();
        data_[0] = 1;
        overflow_ = false;
        return *this;
    }

    if (value >= 0)
    {
        for (uint8_t i = 0; i < length_; i++){
            data_[i] = getbit(value, length_ - i - 1);
        }
    }
    else
    {
        value = -value;
        for (uint8_t i = 0; i < length_; i++)
            data_[i] = getbit(value, length_ - i - 1);
        to_alt_code();
    }
    overflow_ = false;
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
