#ifndef __STEP5_BIGNUM_H__
#define __STEP5_BIGNUM_H__

#define __ull unsigned long long

#include <cstdlib>
#include <cstdio>
#include <iostream>

///Definition
class Bignum
{
public:
    Bignum(int);
    Bignum(long long);
    Bignum(__ull);
    Bignum(const Bignum&);

    Bignum operator=(const Bignum&);

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
Bignum Bignum::operator=(const Bignum& bn_)
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



#endif // __STEP5_BIGNUM_H__
