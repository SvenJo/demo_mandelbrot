#include <complex>
#include <iostream>

#include "complex.h"

namespace print_iterations
{
  inline int Pixel(const float re, const float im)
  {
    using namespace std;

    const std::complex<float> c1 = { re, im };
    std::complex<float> z1 = { 0. };
    const mandel::Complex<float> c2 = { re, im };
    mandel::Complex<float> z2 = { 0. };

    int iter{ 0 };

    cout << "Z.re()\tZ.im\tZ.re()*Z.re()\tZ.im*Z.im()\n";
    do {
      cout << "Z1\t" << z1.real() << '\t' << z1.imag() << '\t' << z1.real()*z1.real() << '\t' << z1.imag()*z1.imag() << '\t' << endl;
      cout << "Z2\t" << z2.real() << '\t' << z2.imag() << '\t' << z2.real()*z2.real() << '\t' << z2.imag()*z2.imag() << '\t' << endl;
      z1 = z1 * z1 + c1;
      z2 = z2 * z2 + c2;

      ++iter;

    } while ((z1.imag() * z1.imag() + z1.real() * z1.real() < 4.0f) && (iter < 100));

    return iter;
  }


  inline void tester()
  {
    std::cout << "print inner state of pixel()\n";

    std::cout << "Pixel(-1,0i) = " << Pixel(-1.f, 0.f) << std::endl;
  }
}
