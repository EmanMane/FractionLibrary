#include "fraction.h"

#include <iostream>

int main ()
{
    Fraction r1(1,2); Fraction r2(2,3);  Fraction r3;
    std::cout << "First: " << r1.GetNumerator() << "/" << r1.GetDenominator() << "=" << r1.GetDecimal() << std::endl;
    std::cout << "Second: " << r2.GetNumerator() << "/" << r2.GetDenominator() << "=" << r2.GetDecimal() << std::endl;
    std::cout<<"First>Second--->";if(r1>r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"First<Second--->";if(r1<r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"First==Second--->";if(r1==r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"First!=Second--->";if(r1!=r2) std::cout<<true<<std::endl; else std::cout<<false<<std::endl;
    std::cout<<"First+Second--->"; r3=r1+r2; std::cout<<r3<<std::endl;
    std::cout<<"First-=Second--->"; r1-=r2; std::cout<<r1<<std::endl;
    std::cout<<"(First++)--->"; r1++; std::cout<<r1<<std::endl;
    std::cout<<"First*=Second--->"; r1*=r2; std::cout<<r1<<std::endl;
    r1++; ++r1; auto decimal=static_cast<long double>(r1);
    std::cout<<"R1++; ++R1; R1="<<decimal;
    return 0;
}
