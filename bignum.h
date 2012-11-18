/******************************
 *  STEP5 Algorithm Template  *
 *  Big number (bignum.h)     *
 *  2012/11/17 ~ 2012/11/18   *
 ******************************/

#ifndef __STEP5_BIGNUM_H__
#define __STEP5_BIGNUM_H__

#define __ull long long
#define __BIGNUM_SEP 1000000000LL

#ifdef __WINDOWS__
#define __I64u "%I64d"
#define __09I64u "%09I64d"
#else
#define __I64u "%lld"
#define __09I64u "%09lld"
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
    Bignum(unsigned long long);
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

    const Bignum operator+ () const;
    const Bignum operator- () const;

    Bignum& operator+= (const Bignum&);
    Bignum& operator-= (const Bignum&);

    friend istream& operator>> (istream&, Bignum&);
    friend ostream& operator<< (ostream&, const Bignum&);

private:
    int size_;
    bool sign_;
    __ull* data_;

    void removeExcessZero();

    void addeq(const Bignum&);
    const Bignum add(const Bignum&) const;
    void subeq(const Bignum&);
};

///Global declaration

///Public
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

    if(n >= __BIGNUM_SEP)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % __BIGNUM_SEP;
        data_[1] = n / __BIGNUM_SEP;
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

    if(n >= __BIGNUM_SEP * __BIGNUM_SEP)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n % __BIGNUM_SEP;
        n /= __BIGNUM_SEP;
        data_[1] = n % __BIGNUM_SEP;
        data_[2] = n / __BIGNUM_SEP;
    }
    else if(n >= __BIGNUM_SEP)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % __BIGNUM_SEP;
        data_[1] = n / __BIGNUM_SEP;
    }
    else
    {
        size_ = 1;
        data_ = new __ull[size_];
        data_[0] = n;
    }
}

//unsigned long long
Bignum::Bignum(unsigned long long n)
{
    sign_ = 0;

    if(n >= __BIGNUM_SEP * __BIGNUM_SEP)
    {
        size_ = 3;
        data_ = new __ull[size_];
        data_[0] = n % __BIGNUM_SEP;
        n /= __BIGNUM_SEP;
        data_[1] = n % __BIGNUM_SEP;
        data_[2] = n / __BIGNUM_SEP;
    }
    else if(n >= __BIGNUM_SEP)
    {
        size_ = 2;
        data_ = new __ull[size_];
        data_[0] = n % __BIGNUM_SEP;
        data_[1] = n / __BIGNUM_SEP;
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
    if(!an.sign_ && !bn.sign_)return an.add(bn);
    else if(an.sign_ && bn.sign_)
    {
        Bignum tmpb = an.add(bn);
        tmpb.sign_ = true;
        return tmpb;
    }
    else if(!an.sign_ && bn.sign_)
    {
        Bignum tmpb(bn);
        tmpb.sign_ = false;
        return an - tmpb;
    }
    else
    {
        Bignum tmpb(bn);
        tmpb.sign_ = true;
        return an - tmpb;
    }
}

// -
const Bignum operator- (const Bignum& an, const Bignum& bn)
{
    Bignum tmpb(an);
    tmpb -= bn;
    return tmpb;
}

// *

// /

// unary +
const Bignum Bignum::operator+ () const
{
    return *this;
}
// unary -
const Bignum Bignum::operator- () const
{
    Bignum tmpb(*this);
    tmpb.sign_ = !tmpb.sign_;
    tmpb.removeExcessZero();
    return tmpb;
}
// +=
Bignum& Bignum::operator+= (const Bignum& bn)
{
    if(!sign_ && !bn.sign_)
    {
        addeq(bn);
    }
    else if(sign_ && bn.sign_)
    {
        addeq(bn);
        sign_ = true;
    }
    else if(!sign_ && bn.sign_)
    {
        Bignum tmpb(bn);
        tmpb.sign_ = false;
        *this -= tmpb;
    }
    else
    {
        Bignum tmpb(bn);
        tmpb.sign_ = true;
        *this -= tmpb;
    }
    return *this;
}

// -=
Bignum& Bignum::operator-= (const Bignum& bn)
{
    if(!sign_ && !bn.sign_)
    {
        if(*this >= bn)subeq(bn);
        else
        {
            Bignum tmpbn(bn);
            tmpbn.subeq(*this);
            *this = tmpbn;
            sign_ = true;
        }
    }
    else if(sign_ && bn.sign_)
    {
        if(*this <= bn)subeq(bn);
        else
        {
            Bignum tmpbn(bn);
            tmpbn.subeq(*this);
            *this = tmpbn;
            sign_ = false;
        }
    }
    else if(!sign_ && bn.sign_)
    {
        addeq(bn);
        sign_ = false;
    }
    else
    {
        addeq(bn);
        sign_ = true;
    }
    removeExcessZero();
    return *this;
}


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

    bn.removeExcessZero();

    return is;
}

//Output
ostream& operator<< (ostream& os, const Bignum& bn)
{
    int sz = bn.size_;
    int i = sz - 1;
    while(bn.data_[i] == 0LL && i > 0)i--; // can be removed

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

///Private
///Other operation
void Bignum::removeExcessZero()
{
    int i = size_ - 1;
    while(data_[i] == 0LL && i > 0)i--;
    size_ = i + 1;
    if(size_ == 1 && data_[0] == 0LL)sign_ = 0;
}

///Operation Implementation
// +=
void Bignum::addeq(const Bignum& bn) //Add absolute value part
{
    if(bn.size_ >= size_)
    {
        *this = add(bn);
        return;
    }

    for(int i = 0 ; i < bn.size_ ; i++)
    {
        data_[i] += bn.data_[i];
    }
    for(int i = 0 ; i < size_ - 1 ; i++)
    {
        if(data_[i] >= __BIGNUM_SEP)
        {
            data_[i] -= __BIGNUM_SEP;
            data_[i+1]++;
        }
        else if(i >= bn.size_)break;
    }

    if(data_[size_-1] >= __BIGNUM_SEP)
    {
        size_++;
        __ull* tmpdata = new __ull[size_];
        for(int i = 0 ; i < size_ - 1 ; i++)
        {
            tmpdata[i] = data_[i];
            tmpdata[size_-1] = 1LL;
            tmpdata[size_-2] -= __BIGNUM_SEP;
        }
        delete [] data_;
        data_ = tmpdata;
    }
}

// +
const Bignum Bignum::add(const Bignum& bn) const // Add absolute value part
{
    Bignum tmpb;
    tmpb.size_ = max(size_, bn.size_) + 1;
    delete [] tmpb.data_;
    tmpb.data_ = new __ull[tmpb.size_]();

    for(int i = 0 ; i < size_ ; i++)
    {
        tmpb.data_[i] += data_[i];
    }
    for(int i = 0 ; i < bn.size_ ; i++)
    {
        tmpb.data_[i] += bn.data_[i];
    }
    for(int i = 0 ; i < tmpb.size_ - 1 ; i++)
    {
        if(tmpb.data_[i] >= __BIGNUM_SEP)
        {
            tmpb.data_[i] -= __BIGNUM_SEP;
            tmpb.data_[i+1]++;
        }
    }
    tmpb.removeExcessZero();

    return tmpb;
}

// -=
void Bignum::subeq(const Bignum& bn) //Subtract absolute value part, Big - Small
{
    for(int i = 0 ; i < bn.size_ ; i++)
    {
        data_[i] -= bn.data_[i];
    }
    for(int i = 0 ; i < size_ - 1 ; i++)
    {
        if(data_[i] < 0LL)
        {
            data_[i] += __BIGNUM_SEP;
            data_[i+1]--;
        }
        else if(i >= bn.size_)break;
    }
    removeExcessZero();
}

#endif // __STEP5_BIGNUM_H__
