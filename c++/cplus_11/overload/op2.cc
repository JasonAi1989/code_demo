#include <iostream>
using namespace std;

class Complex {
public:
    double real;
    double imag;
    Complex(double r = 0.0,double i = 0.0);
    Complex(const Complex &a):real(a.real), imag(a.imag){}
    Complex operator+(const Complex&);
    Complex operator-(const Complex&);
    void printcomplex();
};
Complex::Complex(double r ,double i)
{
    real = r;
    imag = i;
}
Complex Complex::operator+(const Complex& c)
{
    return Complex(real+c.real,imag+c.imag);
}
Complex Complex::operator-(const Complex& c)
{
    return Complex(real-c.real,imag-c.imag);
}
void Complex::printcomplex()
{
    cout<<real<<"+"<<imag<<"i"<<endl;
}

int main(int argc, const char * argv[]) {
    Complex a(3,4),b(5,9),c,d;
    c = a + b;
    d = b - a;
    c.printcomplex();
    d.printcomplex();
    return 0;
}
