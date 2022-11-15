#ifndef FRACTIONLIBRARY_FRACTION_H
#define FRACTIONLIBRARY_FRACTION_H

#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>
#include <limits>


long long int m=std::numeric_limits<long long int>::min();
long long int M=std::numeric_limits<long long int>::max();
long double E=1e-10;

class Fraction{
    long long int numerator,denominator;
    static long long int LCD(long long int p, long long int q){
        while(q!=0){
            long long int mod=p%q;
            p=q; q=mod;
        }
        return p;
    }
    static bool CheckMultiplication(long long int x, long long int y){
        if(y>0){
            if(x<m/y || x>M/y) return true;
        }
        if(y==-1){ if(x==m) return true;}
        else if(y<0){
            if(x==m || -x>M/(-y) || -x<m/(-y)) return true;
        }
        return false;
    }
    static bool CheckSum(long long int x, long long y){
        if(y>0){
            if(x>M-y) return true;
        }
        if(y<0){
            if(x<m-y) return true;
        }
        return false;
    }
    static bool CheckDifference(long long int x, long long y){
        if(y>0){
            if(x>M-y) return true;
        }
        if(y<0){
            if(x<m-y) return true;
        }
        return false;
    }
public:
    Fraction(long long int numerator, long long int denominator);
    explicit Fraction(long long int numerator): numerator(numerator), denominator(1){}
    Fraction(): numerator(0), denominator(1){}
    long long int GetNumerator() const{
        return numerator;
    }
    long long int GetDenominator() const{
        return denominator;
    }
    long double GetDecimal() const{
        long double decimal=numerator;
        decimal/=denominator;
        return decimal;
    }
    friend std::ostream &operator <<(std::ostream &tok, const Fraction &x);
    friend std::istream &operator >>(std::istream &tok, Fraction &x);
    friend Fraction operator+(const Fraction &x, const Fraction &y);
    friend Fraction operator-(const Fraction &x, const Fraction &y);
    friend Fraction operator*(const Fraction &x, const Fraction &y);
    friend Fraction operator/(const Fraction &x, const Fraction &y);
    friend Fraction operator-(const Fraction &x){
        if(CheckMultiplication(x.numerator, -1)) throw std::overflow_error("Impossible to get an exact result");
        return {-x.numerator, x.denominator};
    }
    friend Fraction operator+(const Fraction &x){
        return x;
    }
    friend Fraction &operator+=(Fraction &x, const Fraction &y){
        x=x+y;
        return x;
    }
    friend Fraction &operator-=(Fraction &x, const Fraction &y){
        x=x-y;
        return x;
    }
    friend Fraction &operator*=(Fraction &x, const Fraction &y){
        x=x*y;
        return x;
    }
    friend Fraction &operator/=(Fraction &x, const Fraction &y){
        x=x/y;
        return x;
    }
    friend Fraction &operator++(Fraction &x){
        Fraction one(1, 1);
        x=x+one;
        return x;
    }
    friend Fraction &operator--(Fraction &x){
        Fraction one(1, 1);
        x=x-one;
        return x;
    }
    friend Fraction operator++(Fraction &x, int){
        auto pom(x);
        Fraction one(1, 1);
        x=x+one;
        return pom;
    }
    friend Fraction operator--(Fraction &x, int){
        auto pom(x);
        Fraction one(1, 1);
        x=x-one;
        return pom;
    }
    friend bool operator<(const Fraction &x, const Fraction &y){
        long double decimal1= x.GetDecimal(),decimal2= y.GetDecimal();
        if(decimal1<decimal2) return true;
        return false;
    }
    friend bool operator>(const Fraction &x, const Fraction &y){
        long double decimal1= x.GetDecimal(),decimal2= y.GetDecimal();
        if(decimal1>decimal2) return true;
        return false;
    }
    friend bool operator==(const Fraction &x, const Fraction &y){
        long double decimal1= x.GetDecimal(),decimal2= y.GetDecimal();
        if(std::fabs(decimal1-decimal2)<E) return true;
        return false;
    }
    friend bool operator<=(const Fraction &x, const Fraction &y){
        if(x<y || x==y) return true;
        return false;
    }
    friend bool operator>=(const Fraction &x, const Fraction &y){
        if(x>y || x==y) return true;
        return false;
    }
    friend bool operator!=(const Fraction &x, const Fraction &y){
        if(x==y) return false;
        return true;
    }
    operator long double() const{
        long double b=numerator,n=denominator;
        long double x=b/n;
        return x;
    }
};

Fraction::Fraction(long long int numerator, long long int denominator){
    if(denominator==0) throw std::logic_error("Improper fraction");
    long long int nzd= LCD(numerator, denominator);
    numerator/=nzd;
    denominator/=nzd;
    if(denominator<0){
        numerator*=-1;
        denominator*=-1;
    }
    Fraction::numerator=numerator;
    Fraction::denominator=denominator;
}
std::ostream &operator <<(std::ostream &tok, const Fraction &x){
    if(x.denominator != 1) tok << x.numerator << "/" << x.denominator;
    else tok<<x.numerator;
    return tok;
}
std::istream &operator >>(std::istream &tok, Fraction &x){
    char symbol{};
    long long int numerator{},denominator=1;
    tok>>std::ws;
    if(isdigit(tok.peek())==false && tok.peek()!='-') tok.setstate(std::ios::failbit);
    else{
        tok>>numerator;
        if(tok.peek()!='/'){
            if(tok.peek()==' ' ||
               tok.peek()=='\n' ||
               tok.peek()=='\r' ||
               tok.peek()=='\f' ||
               tok.peek()=='\v' ||
               tok.peek()=='\t' ||
               tok.peek()==EOF) denominator=1;
            else tok.setstate(std::ios::failbit);
        }
        else{
            tok>>symbol>>denominator;
            if(symbol!='/' || (tok.peek()!=' ' &&
                               tok.peek()!='\n' &&
                               tok.peek()!='\r' &&
                               tok.peek()!='\f' &&
                               tok.peek()!='\v' &&
                               tok.peek()!='\t' &&
                               tok.peek()!=EOF)) tok.setstate(std::ios::failbit);
        }
    }
    //if(!tok.fail()){//on ovdje ipak radi sa nekim vrijednostima, UPITNO!
    long long int nzd= Fraction::LCD(numerator, denominator);
    x.numerator= numerator / nzd; x.denominator= denominator / nzd;
    //}
    return tok;
}
Fraction operator+(const Fraction &x, const Fraction &y){
    long long int r= Fraction::LCD(x.denominator, y.denominator),numerator,denominator;
    if(Fraction::CheckMultiplication(x.numerator, y.denominator / r) ||
       Fraction::CheckMultiplication(y.numerator, x.denominator / r)
       || Fraction::CheckSum(x.numerator * (y.denominator / r), y.numerator * (x.denominator / r))
       || Fraction::CheckMultiplication(x.denominator, y.denominator / r)) throw std::overflow_error("Impossible to get an exact result");
    numerator= x.numerator * (y.denominator / r) + y.numerator * (x.denominator / r);
    denominator= x.denominator * (y.denominator / r);
    Fraction z(numerator, denominator);
    return z;
}
Fraction operator-(const Fraction &x, const Fraction &y){
    long long int r= Fraction::LCD(x.denominator, y.denominator),numerator,denominator;
    if(Fraction::CheckMultiplication(x.numerator, y.denominator / r) ||
       Fraction::CheckMultiplication(y.numerator, x.denominator / r)
       || Fraction::CheckDifference(x.numerator * (y.denominator / r), y.numerator * (x.denominator / r))
       || Fraction::CheckMultiplication(x.denominator, y.denominator / r)) throw std::overflow_error("Impossible to get an exact result");
    numerator=x.numerator*(y.denominator/r)-y.numerator*(x.denominator/r);
    denominator=x.denominator*(y.denominator/r);
    Fraction z(numerator,denominator);
    return z;
}
Fraction operator*(const Fraction &x,const Fraction &y){
    long long int s=Fraction::LCD(x.numerator,y.denominator),t=Fraction::LCD(y.numerator,x.denominator),numerator,denominator;
    if(Fraction::CheckMultiplication(x.numerator / s, y.numerator / t) ||
       Fraction::CheckMultiplication(x.denominator / t, y.denominator / s)) throw std::overflow_error("Impossible to get an exact result");
    numerator=(x.numerator/s)*(y.numerator/t);
    denominator=(x.denominator/t)*(y.denominator/s);
    Fraction z(numerator,denominator);
    return z;
}
Fraction operator/(const Fraction &x,const Fraction &y){
    long long int r=Fraction::LCD(x.denominator,y.denominator),u=Fraction::LCD(x.numerator,y.numerator),numerator,denominator;
    if(Fraction::CheckMultiplication(x.numerator / u, y.denominator / r) ||
       Fraction::CheckMultiplication(x.denominator / r, y.numerator / u))
        throw std::overflow_error("Impossible to get an exact result");
    numerator=(x.numerator/u)*(y.denominator/r);
    denominator=(x.denominator/r)*(y.numerator/u);
    Fraction z(numerator,denominator);
    return z;
}

#endif //FRACTIONLIBRARY_FRACTION_H
