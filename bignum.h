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
#include <exception>
#include <stdexcept>
#include <cmath>

using namespace std;

///Definition
class Bignum
{
public:
    //constructor
    Bignum(int);
    Bignum(long long);
    Bignum(unsigned long long);
    Bignum(const Bignum&);
    //destructor
    ~Bignum();

    //assignment
    Bignum& operator=(const Bignum&);

    //comparison
    friend const bool operator== (const Bignum&, const Bignum&);
    friend const bool operator!= (const Bignum&, const Bignum&);
    friend const bool operator< (const Bignum&, const Bignum&);
    friend const bool operator> (const Bignum&, const Bignum&);
    friend const bool operator<= (const Bignum&, const Bignum&);
    friend const bool operator>= (const Bignum&, const Bignum&);

    //arithmetic
    friend const Bignum operator+ (const Bignum&, const Bignum&);
    friend const Bignum operator- (const Bignum&, const Bignum&);
    friend const Bignum operator* (const Bignum&, const Bignum&);
    friend const Bignum operator/ (const Bignum&, const Bignum&);
    friend const Bignum operator% (const Bignum&, const Bignum&);

    const Bignum operator+ () const;
    const Bignum operator- () const;

    //compound assignment
    Bignum& operator+= (const Bignum&);
    Bignum& operator-= (const Bignum&);
    Bignum& operator*= (const Bignum&);
    Bignum& operator/= (const Bignum&);
    Bignum& operator%= (const Bignum&);

    //increment/decrement
    Bignum& operator++ ();
    Bignum& operator-- ();
    const Bignum operator++ (int);
    const Bignum operator-- (int);

    //I/O
    friend istream& operator>> (istream&, Bignum&);
    friend ostream& operator<< (ostream&, const Bignum&);

    //Conversion
    bool toBool() const;
    int toInt() const;
    long long toLL() const;
    unsigned long long toULL() const;

    //Other mathematic functions
    friend const double log(const Bignum&); // natural log
    friend const Bignum pow(const Bignum&, int); // integer power
    friend const Bignum abs(const Bignum&); // absolute value

    //Other functions
    const Bignum shift(int) const; //data block shift, positive=left shift
    const int getDigit() const; // get how many digits (0 => 0)
    const bool getSign() const; // get sign (positive or zero : 0 / negative : 1)
    const Bignum getAbs() const; // get absolute value

private:
    int size_; // number of block
    bool sign_; // true:negative | false:positive or zero
    __ull* data_;
    // data blocks. Every blocks is __BIGNUM__SEP at max. data_[0] is low bit.

    void removeExcessZero(); //remove excess zero on high bit. Remove "-0".
    void resizeZero(const int); //resize data_, set every entry to zero.

    //Arithmetic implementation
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
        resizeZero(bn.size_);
    }

    for(int i = 0 ; i < size_ ; i++)
    {
        data_[i] = bn.data_[i];
    }

    return *this;
}

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
const Bignum operator* (const Bignum& an, const Bignum& bn)
{
    Bignum tmpb;
    if((an.sign_ && !bn.sign_) || (!an.sign_ && bn.sign_))
    {
        tmpb.sign_ = true;
    }
    tmpb.resizeZero(an.size_ + bn.size_);

    for(int i = 0 ; i < bn.size_ ; i++)
    {
        if(bn.data_[i] == 0LL)continue;
        for(int j = 0 ; j < an.size_ ; j++)
        {
            tmpb.data_[i+j] += bn.data_[i] * an.data_[j];
            tmpb.data_[i+j+1] += tmpb.data_[i+j] / __BIGNUM_SEP;
            tmpb.data_[i+j] %= __BIGNUM_SEP;
        }
    }

    tmpb.removeExcessZero();
    return tmpb;
}

// /
const Bignum operator/ (const Bignum& an, const Bignum& bn)
{
    Bignum tmpb;
    if((an.sign_ && !bn.sign_) || (!an.sign_ && bn.sign_))
    {
        tmpb.sign_ = true;
    }
    if(bn == 0)
    {
        domain_error r("Bignum::DevideByZero");
        throw(r);
        return bn;
    }
    if(an.size_ < bn.size_)
    {
        tmpb = 0;
    }
    else
    {
        Bignum ap(an), bp(bn);
        ap.sign_ = bp.sign_ = false;
        int maxl = bp.size_ - 1;

        tmpb.resizeZero(ap.size_ - bp.size_ + 1);

        for(int i = ap.size_ - bp.size_ ; i >= 0 ; i--)
        {
            if(ap == 0)break;

            Bignum shiftbp = bp.shift(i);
            double logEst = log(ap) - log(shiftbp);
            long long beilu = ceil(exp(logEst) + 0.1);
            ap -= shiftbp * beilu;

            while(ap.sign_)
            {
                ap += shiftbp;
                beilu--;
            }
            tmpb.data_[i] = beilu;
        }
    }

    tmpb.removeExcessZero();
    return tmpb;
}

// %


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

// *=
Bignum& Bignum::operator*= (const Bignum& bn)
{
    return (*this = (*this * bn));
}

// /=
Bignum& Bignum::operator/= (const Bignum& bn)
{
    return (*this = (*this / bn));
}

// ++a
Bignum& Bignum::operator++ ()
{
    return (*this += 1);
}

// --a
Bignum& Bignum::operator-- ()
{
    return (*this -= 1);
}

// a++
const Bignum Bignum::operator++ (int x)
{
    Bignum tmpb(*this);
    ++*this;
    return tmpb;
}

// a--
const Bignum Bignum::operator-- (int x)
{
    Bignum tmpb(*this);
    --*this;
    return tmpb;
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

    bn.resizeZero((sl - 1) / 9 + 1);

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

///Conversion (currently alternative solution)
//bool
bool Bignum::toBool() const
{
    return (*this == 0);
}

//int
int Bignum::toInt() const
{
    long long tmp = data_[0];
    if(size_ >= 2)tmp += data_[1] * __BIGNUM_SEP;
    if(sign_) tmp *= -1;
    int ret = tmp;
    return ret;
}

//long long
long long Bignum::toLL() const
{
    long long tmp = data_[0];
    if(size_ >= 2)tmp += data_[1] * __BIGNUM_SEP;
    if(size_ >= 3)tmp += data_[2] * __BIGNUM_SEP * __BIGNUM_SEP;
    if(sign_) tmp *= -1LL;
    return tmp;
}

//unsigned long long
unsigned long long Bignum::toULL() const
{
    unsigned long long tmp = (unsigned long long)data_[0];
    if(size_ >= 2)tmp += (unsigned long long)data_[1] * (unsigned long long)__BIGNUM_SEP;
    if(size_ >= 3)tmp += (unsigned long long)data_[2] * (unsigned long long)__BIGNUM_SEP * (unsigned long long)__BIGNUM_SEP;
    return tmp;
}

///Other mathematic function
//natural log
const double log(const Bignum& bn)
{
    double ans;
    if(bn <= 0)
    {
        domain_error r("Bignum::LogZeroNegative");
        throw(r);
        return 0.0;
    }
    double lead = bn.data_[bn.size_-1];
    if(bn.size_ >= 2)lead += (double)bn.data_[bn.size_-2] / (double)__BIGNUM_SEP;
    if(bn.size_ >= 3)lead += (double)bn.data_[bn.size_-3] / (double)(__BIGNUM_SEP * __BIGNUM_SEP);

    ans = (double)(bn.size_ - 1) * log((double)__BIGNUM_SEP) + log(lead);
    return ans;
}

//integer power
const Bignum pow(const Bignum& bn, int ex)
{
    Bignum tmpb(0);
    if(ex >= 0)
    {
        tmpb = 1;
        for(int i = 0 ; i < ex ; i++)
        {
            tmpb *= bn;
        }
    }
    return tmpb;
}

//absolute value
const Bignum abs(const Bignum& bn)
{
    Bignum tmpb(bn);
    tmpb.sign_ = false;
    return tmpb;
}

///Other function
//shift
const Bignum Bignum::shift(int offset) const
{
    Bignum tmpb(0);
    if(offset > -size_)
    {
        tmpb.resizeZero(size_ + offset);
        for(int i = size_ - 1 ; i >= 0 ; i--)
        {
            if(i + offset < 0)break;
            tmpb.data_[i+offset] = data_[i];
        }
    }
    return tmpb;
}

//getDigit
const int Bignum::getDigit() const
{
    if(*this == 0)return 1;

    long long x = data_[size_-1];
    int dig = (size_ - 1) * 9;
    while(x > 0)
    {
        dig++;
        x /= 10LL;
    }
    return dig;
}

//getSign
const bool Bignum::getSign() const
{
    return sign_;
}

//getAbs
const Bignum Bignum::getAbs() const
{
    return abs(*this);
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

void Bignum::resizeZero(const int sz)
{
    size_ = sz;
    delete [] data_;
    data_ = new __ull[size_]();
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
    tmpb.resizeZero(max(size_, bn.size_) + 1);

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
