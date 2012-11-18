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

    friend const Bignum operator+ (const Bignum&, const Bignum&);
    friend const Bignum operator- (const Bignum&, const Bignum&);
    friend const Bignum operator* (const Bignum&, const Bignum&);
    friend const Bignum operator/ (const Bignum&, const Bignum&);

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
Bignum::Bignum(int n = 0)
{
    if(n < 0)
    {
        sign_ = 1;
        n= -n;
    }
    else
    {
        sign_ = 0;
    }

    if(n >= 1000000000)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % 1000000000;
        data_[1] = n / 1000000000;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n;
    }
}

//long long
Bignum::Bignum(long long n)
{
    if(n < 0)
    {
        sign_ = 1;
        n= -n;
    }
    else
    {
        sign_ = 0;
    }

    if(n >= 1000000000000000000LL)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n % 1000000000LL;
        n /= 1000000000LL;
        data_[1] = n % 1000000000LL;
        data_[2] = n / 1000000000LL;
    }
    else if(n >= 1000000000LL)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % 1000000000LL;
        data_[1] = n / 1000000000LL;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n;
    }
}

//unsigned long long
Bignum::Bignum(__ull n)
{
    sign_ = 0;

    if(n >= 1000000000000000000ULL)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n % 1000000000ULL;
        n /= 1000000000ULL;
        data_[1] = n % 1000000000ULL;
        data_[2] = n / 1000000000ULL;
    }
    else if(n >= 1000000000ULL)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % 1000000000ULL;
        data_[1] = n / 1000000000ULL;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n;
    }
}

//copy
Bignum::Bignum(const Bignum& bn)
{
    size_ = bn.size_;
    sign_ = bn.sign_;
    data_ = new __ull[size_];
    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn.data_[i];
    }
}

///Destructor
Bignum::~Bignum()
{
    delete [] data_;
}

///Assignment Operator
//Assignment
Bignum& Bignum::operator=(const Bignum& bn)
{
    sign_ = bn.sign_;

    if(size_ != bn.size_)
    {
        delete [] data_;
        size_ = bn.size_;
        data_ = new __ull[size_];
    }

    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn.data_[i];
    }

    return *this;
}

//Assignment from int?

///Comparative Operator
// ==
const bool operator== (const Bignum& an, const Bignum& bn)
{
    if(an.size_ != bn.size_)return false;
    if(an.sign_ != bn.sign_)return false;

    for(int i = 0 ; i < an.size_ ; i++)
    {
        if(an.data_[i] != bn.data_[i])return false;
    }
    return true;
}

// !=
const bool operator!= (const Bignum& an, const Bignum& bn)
{
    return !(an == bn);
}

// <
const bool operator< (const Bignum& an, const Bignum& bn)
{
    if(an.sign_ && !bn.sign_)return true;
    if(!an.sign_ && bn.sign_)return false;

    bool fl = true;
    if(an.sign_ && bn.sign_)fl = false;

    if(an.size_ < bn.size_)return fl;
    if(an.size_ > bn.size_)return !fl;

    for(int i = an.size_ - 1 ; i >= 0 ; i--)
    {
        if(an.data_[i] < bn.data_[i])return fl;
        if(an.data_[i] > bn.data_[i])return !fl;
    }

    return false;
}

// >
const bool operator> (const Bignum& an, const Bignum& bn)
{
    if(an.sign_ && !bn.sign_)return false;
    if(!an.sign_ && bn.sign_)return true;

    bool fl = true;
    if(an.sign_ && bn.sign_)fl = false;

    if(an.size_ > bn.size_)return fl;
    if(an.size_ < bn.size_)return !fl;

    for(int i = an.size_ - 1 ; i >= 0 ; i--)
    {
        if(an.data_[i] > bn.data_[i])return fl;
        if(an.data_[i] < bn.data_[i])return !fl;
    }

    return false;
}

// <=
const bool operator<= (const Bignum& an, const Bignum& bn)
{
    return !(an > bn);
}

// >=
const bool operator>= (const Bignum& an, const Bignum& bn)
{
    return !(an < bn);
}

///Arithmetic operator
// +
const Bignum operator+ (const Bignum& an, const Bignum& bn)
{

}

// -

// *

// /

// convert to int / long long / unsigned long long

///I/O
//Input
istream& operator>> (istream& is, Bignum& bn)
{
    string s;
    is >> s;
    int sl = s.length();
    int now_ptr = 0;

    if(s[0] == '-')
    {
        bn.sign_ = 1;
        now_ptr++;
        sl--;
    }
    else
    {
        bn.sign_ = 0;
    }

    delete [] bn.data_;

    bn.size_ = (sl - 1) / 9 + 1;
    bn.data_ = new __ull[bn.size_]();

    int now_pos = bn.size_ - 1;

    int tmp = 0;
    for(int i = 0; i < (sl - 1) % 9 + 1 ; i++)
    {
        tmp *= 10;
        tmp += (s[now_ptr++] - '0');
    }
    bn.data_[now_pos--] = tmp;

    while(now_pos >= 0)
    {
        tmp = 0;
        for(int i = 0 ; i < 9 ; i++)
        {
            tmp *= 10;
            tmp += (s[now_ptr++] - '0');
        }
        bn.data_[now_pos--] = tmp;
    }

    bn.removeExcessZero_();

    return is;
}

//Output
ostream& operator<< (ostream& os, const Bignum& bn)
{
    int sz = bn.size_;
    int i = sz - 1;
    while(bn.data_[i] == 0ULL && i > 0)i--; // can be removed

    if(bn.sign_)// && bn_ != 0)
    {
        if(os == cout)printf("-");
        else os << "-";
    }

    if(os == cout)printf(__I64u, bn.data_[i--]);
    else os << bn.data_[i--];

    for( ; i >= 0 ; i--)
    {
        if(os == cout)printf(__09I64u, bn.data_[i]);
        else os << setfill('0') << setw(9) << bn.data_[i];
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
