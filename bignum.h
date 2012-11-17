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

using namespace std;

///Definition
class Bignum
{
public:
    Bignum(int);
    Bignum(long long);
    Bignum(__ull);
    Bignum(const Bignum&);

    Bignum& operator=(const Bignum&);

    friend ostream& operator<< (ostream&, const Bignum&);

private:
    int size_;
    bool sign_;
    __ull* data_;

};

///Constructor
//default; int
Bignum::Bignum(int n_ = 0ULL)
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

///Operator
//Assignment
Bignum& Bignum::operator=(const Bignum& bn_)
{
    delete [] data_;

    size_ = bn_.size_;
    sign_ = bn_.sign_;
    data_ = new __ull[size_];
    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn_.data_[i];
    }

    return *this;
}

//Assignment from int?

///Input

///Output
ostream& operator << (ostream& os, const Bignum& bn_)
{
    int sz_ = bn_.size_;
    int i = sz_ - 1;
    while(bn_.data_[i] == 0LL && i > 0)i--;

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


#endif // __STEP5_BIGNUM_H__
