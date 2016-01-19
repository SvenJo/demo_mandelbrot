// compile with g++ -std=c++11 test.cpp -I../extern/vectorclass -O3 -o test -ffast-math
#pragma once

#include <complex>

#include <perf_tester.h>
#include <mandel/pixel.h>
#include <mandel/sequentiell.h>
#include <mandel/openmp.h>
#include <mandel/complex.h>

namespace perf_demo {

  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelComplexAbs
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      using namespace std;

      const COMPLEX_TYPE c = { re, im };
      COMPLEX_TYPE z = { 0. };
      int iter{ 0 };
      do {
        z = z * z + c;
        ++iter;
      } while (abs(z) < FLOAT_TYPE(2.0) && iter < max_iter);

      return iter;
    }
  };

  template<typename FLOAT_TYPE, int SHIFT = 1000>
  struct PixelFloatLikeInt
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 };
      const FLOAT_TYPE rm_ = re * FLOAT_TYPE(SHIFT);
      const FLOAT_TYPE im_ = im * FLOAT_TYPE(SHIFT);
      int iter{ 0 };

      do {
        const FLOAT_TYPE uold = u;
        u = (u*u - v*v) / SHIFT + rm_;
        v = (FLOAT_TYPE(2) * uold*v) / SHIFT + im_;
        ++iter;
      } while ((u*u + v*v) < FLOAT_TYPE(4) * SHIFT * SHIFT && iter < max_iter);
      return iter;
    }
  };

  template<typename FLOAT_TYPE, int SHIFT = 1000>
  struct PixelFloatLikeIntReverse
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 };
      const FLOAT_TYPE rm_ = re / FLOAT_TYPE(SHIFT);
      const FLOAT_TYPE im_ = im / FLOAT_TYPE(SHIFT);
      int iter{ 0 };

      do {
        const FLOAT_TYPE uold = u;
        u = (u*u - v*v) * SHIFT + rm_;
        v = (FLOAT_TYPE(2) * uold*v) * SHIFT + im_;
        ++iter;
      } while ((u*u + v*v) < FLOAT_TYPE(4.0 / (SHIFT * SHIFT)) && iter < max_iter);
      return iter;
    }
  };


  inline void test()
  {
    using namespace mandel;

    PerfTest perfTest("Performance Demo (different float types)");

    perfTest.test<CalcSequentiell<float, int, PixelComplex<std::complex<float>>>>("std::complex float");
    perfTest.test<CalcSequentiell<double, int, PixelComplex<std::complex<double>>>>("std::complex double");
    perfTest.test<CalcSequentiell<long double, int, PixelComplex<std::complex<long double>>>>("std::complex long double");

    perfTest.test<CalcSequentiell<float, int, Pixel1989<float>>>("float (1)");
    perfTest.test<CalcSequentiell<double, int, Pixel1989<double>>>("double (1)");
    perfTest.test<CalcSequentiell<long double, int, Pixel1989<long double>>>("long double (1)");
        
    perfTest.test<CalcSequentiell<float, int, Pixel<float>>>("float (2)");
    perfTest.test<CalcSequentiell<double, int, Pixel<double>>>("double (2)");
    perfTest.test<CalcSequentiell<long double, int, Pixel<long double>>>("long double (2)");

    perfTest.test<CalcSequentiell<double, int, PixelInt<int, 1000>>>("int");
    perfTest.test<CalcSequentiell<double, int, PixelInt<int64_t, 10000>>>("int64");
    perfTest.test<CalcSequentiell<double, int, PixelInt<long long, 10000>>>("long long");

    perfTest.test<CalcSequentiell<float, int, PixelComplex<Complex<float>>>>("mandel::Complex float");
    perfTest.test<CalcSequentiell<double, int, PixelComplex<Complex<double>>>>("mandel::Complex double");
    perfTest.test<CalcSequentiell<long double, int, PixelComplex<Complex<long double>>>>("mandel::Complex long double");
  }

  inline void test_int()
  {
    using namespace mandel;

    PerfTest perfTest("Performance Demo (use different int types)");

    perfTest.test<CalcSequentiell<float, int, Pixel<float>>>("float");
    perfTest.test<CalcSequentiell<double, int, Pixel<double>>>("double");

    perfTest.test<CalcSequentiell<double, int, PixelInt<int, 1000>>>("int");
    perfTest.test<CalcSequentiell<double, int, PixelInt<int64_t, 10000>>>("int64");
    perfTest.test<CalcSequentiell<double, int, PixelInt<long long, 10000>>>("long long");

    perfTest.test<CalcSequentiell<float, int, PixelFloatLikeInt<float, 1000>>>("same as int, but with float");
    perfTest.test<CalcSequentiell<double, int, PixelFloatLikeInt<double, 1000>>>("same as int, but with double");

    perfTest.test<CalcSequentiell<float, int, PixelFloatLikeIntReverse<float, 1000>>>("use mul instead of div (float)");
    perfTest.test<CalcSequentiell<double, int, PixelFloatLikeIntReverse<double, 1000>>>("use mul instead of div (double)");
  }


  inline void test_complex()
  {
    using namespace mandel;

    PerfTest perfTest("Performance Demo (use std::abs)");

    //*
    // std::complex
    perfTest.test<CalcSequentiell<float, int, PixelComplex<std::complex<float>>>>("std::complex float");
    perfTest.test<CalcSequentiell<double, int, PixelComplex<std::complex<double>>>>("std::complex double");
    perfTest.test<CalcSequentiell<long double, int, PixelComplex<std::complex<long double>>>>("std::complex long double");

    perfTest.test<CalcSequentiell<float, int, PixelComplexAbs<std::complex<float>>>>("std::complex float (abs())");
    perfTest.test<CalcSequentiell<double, int, PixelComplexAbs<std::complex<double>>>>("std::complex double (abs())");
    perfTest.test<CalcSequentiell<long double, int, PixelComplexAbs<std::complex<long double>>>>("std::complex long double (abs())");
    
    /*/
    // Complex
    perfTest.test<CalcSequentiell<float, int, PixelComplex<Complex<float>>>>("mandel::Complex float");
    perfTest.test<CalcSequentiell<double, int, PixelComplex<Complex<double>>>>("mandel::Complex double");
    perfTest.test<CalcSequentiell<long double, int, PixelComplex<Complex<long double>>>>("mandel::Complex long double");

    perfTest.test<CalcSequentiell<float, int, PixelComplexAbs<Complex<float>>>>("mandel::Complex float (abs())");
    perfTest.test<CalcSequentiell<double, int, PixelComplexAbs<Complex<double>>>>("mandel::Complex double (abs())");
    perfTest.test<CalcSequentiell<long double, int, PixelComplexAbs<Complex<long double>>>>("mandel::Complex long double (abs())");
    //*/
  }

}
