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
    friend const Bignum fact(int, int = 1); //Factoria (n!)
    friend const Bignum perm(int, int); //Permutation number P(m,n)
    friend const Bignum comb(int, int); //Combination number C(m,n)

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
    const Bignum divide(const Bignum&, bool isRmd = false) const;
};

///Global declaration

#endif // __STEP5_BIGNUM_H__
