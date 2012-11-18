#ifndef __STEP5_BIGNUM_H__
#define __STEP5_BIGNUM_H__

#define __ull unsigned long long

#ifdef __WINDOWS__
#define __I64u "%I64u"
#define __09I64u "%09I64u"
#else
#define __I64u "%llu"
#define __09I64u "%09llu"
#endif


#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

///Definition
class Bignum
{
public:
    Bignum(int);
    Bignum(long long);
    Bignum(__ull);
    Bignum(const Bignum&);
    ~Bignum();

    Bignum& operator=(const Bignum&);

    friend const bool operator== (const Bignum&, const Bignum&);
    friend const bool operator!= (const Bignum&, const Bignum&);
    friend const bool operator< (const Bignum&, const Bignum&);
    friend const bool operator> (const Bignum&, const Bignum&);
    friend const bool operator<= (const Bignum&, const Bignum&);
    friend const bool operator>= (const Bignum&, const Bignum&);

    friend istream& operator>> (istream& is, Bignum& bn_);
    friend ostream& operator<< (ostream&, const Bignum&);

private:
    int size_;
    bool sign_;
    __ull* data_;

    void removeExcessZero_();
};

///Global declaration


///Constructor
//default; int
Bignum::Bignum(int n_ = 0)
{
    if(n_ < 0)
    {
        sign_ = 1;
        n_= -n_;
    }
    else
    {
        sign_ = 0;
    }

    if(n_ >= 1000000000)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n_ % 1000000000;
        data_[1] = n_ / 1000000000;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n_;
    }
}

//long long
Bignum::Bignum(long long n_)
{
    if(n_ < 0)
    {
        sign_ = 1;
        n_= -n_;
    }
    else
    {
        sign_ = 0;
    }

    if(n_ >= 1000000000000000000LL)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n_ % 1000000000LL;
        n_ /= 1000000000LL;
        data_[1] = n_ % 1000000000LL;
        data_[2] = n_ / 1000000000LL;
    }
    else if(n_ >= 1000000000LL)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n_ % 1000000000LL;
        data_[1] = n_ / 1000000000LL;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n_;
    }
}

//unsigned long long
Bignum::Bignum(__ull n_)
{
    sign_ = 0;

    if(n_ >= 1000000000000000000ULL)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n_ % 1000000000ULL;
        n_ /= 1000000000ULL;
        data_[1] = n_ % 1000000000ULL;
        data_[2] = n_ / 1000000000ULL;
    }
    else if(n_ >= 1000000000ULL)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n_ % 1000000000ULL;
        data_[1] = n_ / 1000000000ULL;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n_;
    }
}

//copy
Bignum::Bignum(const Bignum& bn_)
{
    size_ = bn_.size_;
    sign_ = bn_.sign_;
    data_ = new __ull[size_];
    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn_.data_[i];
    }
}

///Destructor
Bignum::~Bignum()
{
    delete [] data_;
}

///Assignment Operator
//Assignment
Bignum& Bignum::operator=(const Bignum& bn_)
{
    sign_ = bn_.sign_;

    if(size_ != bn_.size_)
    {
        delete [] data_;
        size_ = bn_.size_;
        data_ = new __ull[size_];
    }

    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn_.data_[i];
    }

    return *this;
}

//Assignment from int?

///Comparative Operator
// ==
const bool operator== (const Bignum& an_, const Bignum& bn_)
{
    if(an_.size_ != bn_.size_)return false;
    if(an_.sign_ != bn_.sign_)return false;

    for(int i = 0 ; i < an_.size_ ; i++)
    {
        if(an_.data_[i] != bn_.data_[i])return false;
    }
    return true;
}

// !=
const bool operator!= (const Bignum& an_, const Bignum& bn_)
{
    return !(an_ == bn_);
}

// <
const bool operator< (const Bignum& an_, const Bignum& bn_)
{
    if(an_.sign_ && !bn_.sign_)return true;
    if(!an_.sign_ && bn_.sign_)return false;

    bool fl = true;
    if(an_.sign_ && bn_.sign_)fl = false;

    if(an_.size_ < bn_.size_)return fl;
    if(an_.size_ > bn_.size_)return !fl;

    for(int i = an_.size_ - 1 ; i >= 0 ; i--)
    {
        if(an_.data_[i] < bn_.data_[i])return fl;
        if(an_.data_[i] > bn_.data_[i])return !fl;
    }

    return false;
}

// >
const bool operator> (const Bignum& an_, const Bignum& bn_)
{
    if(an_.sign_ && !bn_.sign_)return false;
    if(!an_.sign_ && bn_.sign_)return true;

    bool fl = true;
    if(an_.sign_ && bn_.sign_)fl = false;

    if(an_.size_ > bn_.size_)return fl;
    if(an_.size_ < bn_.size_)return !fl;

    for(int i = an_.size_ - 1 ; i >= 0 ; i--)
    {
        if(an_.data_[i] > bn_.data_[i])return fl;
        if(an_.data_[i] < bn_.data_[i])return !fl;
    }

    return false;
}

// <=
const bool operator<= (const Bignum& an_, const Bignum& bn_)
{
    return !(an_ > bn_);
}

// >=
const bool operator>= (const Bignum& an_, const Bignum& bn_)
{
    return !(an_ < bn_);
}

// +

// -

// *

// /

// convert to int / long long / unsigned long long

///I/O
//Input
istream& operator>> (istream& is, Bignum& bn_)
{
    string s_;
    is >> s_;
    int sl_ = s_.length();
    int now_ptr_ = 0;

    if(s_[0] == '-')
    {
        bn_.sign_ = 1;
        now_ptr_++;
        sl_--;
    }
    else
    {
        bn_.sign_ = 0;
    }

    delete [] bn_.data_;

    bn_.size_ = (sl_ - 1) / 9 + 1;
    bn_.data_ = new __ull[bn_.size_]();

    int now_pos_ = bn_.size_ - 1;

    int tmp_ = 0;
    for(int i = 0; i < (sl_ - 1) % 9 + 1 ; i++)
    {
        tmp_ *= 10;
        tmp_ += (s_[now_ptr_++] - '0');
    }
    bn_.data_[now_pos_--] = tmp_;

    while(now_pos_ >= 0)
    {
        tmp_ = 0;
        for(int i = 0 ; i < 9 ; i++)
        {
            tmp_ *= 10;
            tmp_ += (s_[now_ptr_++] - '0');
        }
        bn_.data_[now_pos_--] = tmp_;
    }

    bn_.removeExcessZero_();

    return is;
}

//Output
ostream& operator<< (ostream& os, const Bignum& bn_)
{
    int sz_ = bn_.size_;
    int i = sz_ - 1;
    while(bn_.data_[i] == 0ULL && i > 0)i--; // can be removed

    if(bn_.sign_)// && bn_ != 0)
    {
        if(os == cout)printf("-");
        else os << "-";
    }

    if(os == cout)printf(__I64u, bn_.data_[i--]);
    else os << bn_.data_[i--];

    for( ; i >= 0 ; i--)
    {
        if(os == cout)printf(__09I64u, bn_.data_[i]);
        else os << setfill('0') << setw(9) << bn_.data_[i];
    }
    return os;
}

///Other operation
void Bignum::removeExcessZero_()
{
    int i = size_ - 1;
    while(data_[i] == 0ULL && i > 0)i--;
    size_ = i + 1;
    if(size_ == 1 && data_[0] == 0ULL)sign_ = 0;
}

#endif // __STEP5_BIGNUM_H__
