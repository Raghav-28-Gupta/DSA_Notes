#include <iostream>

using namespace std;


class Complex
{
public:
    int real;
    int imag;

    Complex()
    {
        real = imag = -1;
    }

    Complex(int r, int i) : real(r), imag(i) {};

    // syntax
    // Ret_type operator <op> (args){
    //     // mlkdmk
    //     return <>
    // }

    Complex operator+(const Complex &B)
    {
        /// this -> A instance
        Complex temp;
        temp.real = this->real + B.real;
        temp.imag = this->imag + B.imag;
        return temp;
    }

    Complex operator-(const Complex &B)
    {
        /// this -> A instance
        Complex temp;
        temp.real = this->real - B.real;
        temp.imag = this->imag - B.imag;
        return temp;
    }

    bool operator==(const Complex &B)
    {
        /// this -> A instance
        return (this->real == B.real) && (this->imag == B.imag);
    }

    void print()
    {
        printf("[%d + i%d]\n", this->real, this->imag);
    }
};

int main()
{
    Complex A(3, 3);
    A.print();
    Complex B(3, 3);
    B.print();

    bool a = A == B;
    cout << a << endl;

    // Complex C = A + B;
    // C.print();

    // Complex D = A - B;
    // D.print();

    // int x = 5, y = 5;
    // int z = 2;

    
    return 0;
}
