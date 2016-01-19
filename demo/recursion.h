#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <algorithm>

#include <perf_tester.h>
#include <mandel/pixel.h>
#include <mandel/sequentiell.h>
#include <mandel/openmp.h>

/*
In work...
*/

namespace recursion_demo
{
  using namespace std;
  using namespace mandel;

  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelRecComplex
  {
    static int inner(int iter, COMPLEX_TYPE z, const COMPLEX_TYPE c, const int max_iter) 
    {
      if (iter < max_iter) {
        z = z * z + c;
        if ((z.imag() * z.imag() + z.real() * z.real() < FLOAT_TYPE(4.0)))
          return inner(iter + 1, z, c, max_iter);
      }
      return iter;
    }

    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      return inner(1, COMPLEX_TYPE{ 0 }, COMPLEX_TYPE{ re, im }, max_iter);
    }
  };


  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelRecComplexTailOpt
  {
    static int inner(int iter, COMPLEX_TYPE z, const COMPLEX_TYPE c, const int max_iter)
    {
      if (iter == max_iter) return max_iter;
      z = z * z + c;
      if ((z.imag() * z.imag() + z.real() * z.real() >= FLOAT_TYPE(4.0))) return iter;

      return inner(iter + 1, z, c, max_iter);
    }

    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      return inner(1, COMPLEX_TYPE{ 0 }, COMPLEX_TYPE{ re, im }, max_iter);
    }
  };



  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelRecComplexConstMember
  {
    struct Inner
    {
      const COMPLEX_TYPE c_;
      const int max_iter_;

      Inner(const COMPLEX_TYPE c, const int max_iter)
        : c_(c)
        , max_iter_(max_iter)
      {}

      int operator()(int iter, COMPLEX_TYPE z) const
      {
        if (iter == max_iter_) return max_iter_;
        z = z * z + c_;
        if ((z.imag() * z.imag() + z.real() * z.real() >= FLOAT_TYPE(4.0))) return iter;

        return operator()(iter + 1, z);
      }
    };

    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      Inner inner{ COMPLEX_TYPE{ re, im }, max_iter };
      return inner(1, COMPLEX_TYPE{ 0 });
    }
  };

  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelRecComplexLambda
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      const COMPLEX_TYPE c{ re, im };

      std::function<int(int, COMPLEX_TYPE z)> inner;
      inner = [&inner, &c, &max_iter](int iter, COMPLEX_TYPE z) -> int {
        if (iter == max_iter) return max_iter;
        z = z * z + c;
        if ((z.imag() * z.imag() + z.real() * z.real() >= FLOAT_TYPE(4.0))) return iter;

        return inner(iter + 1, z);
      };
      return inner(1, COMPLEX_TYPE{ 0 });
    }
  };

  template<typename FLOAT_TYPE>
  struct PixelRecursion
  {
    static int inner(int iter, const FLOAT_TYPE re, const FLOAT_TYPE im, FLOAT_TYPE v, FLOAT_TYPE u2, FLOAT_TYPE v2, const int max_iter = 100)
    {
      if (iter < max_iter) {
        const FLOAT_TYPE u = u2 - v2 + re;
        v = FLOAT_TYPE(2) * v * u + im;
        u2 = u*u;
        v2 = v*v;
        if (u2 + v2 < FLOAT_TYPE(4))
          return inner(iter + 1, re, im, v, u2, v2);
      }
      return iter;
    }

    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      return inner(1, re, im, FLOAT_TYPE(0), FLOAT_TYPE(0), FLOAT_TYPE(0), max_iter);
    }
  };

  template<typename FLOAT_TYPE>
  struct PixelTailRecursion
  {
    static int inner(int iter, const FLOAT_TYPE re, const FLOAT_TYPE im, FLOAT_TYPE v, FLOAT_TYPE u, FLOAT_TYPE u2, FLOAT_TYPE v2, const int max_iter = 100)
    {
      if (iter == max_iter) return max_iter;

      /*const auto*/ u = u2 - v2 + re;
      v = FLOAT_TYPE(2) * v * u + im;
      u2 = u*u;
      v2 = v*v;
      if (u2 + v2 >= FLOAT_TYPE(4)) return iter;

      return inner(iter + 1, re, im, v, u, u2, v2);
    }

    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      return inner(1, re, im, FLOAT_TYPE(0), FLOAT_TYPE(0), FLOAT_TYPE(0), FLOAT_TYPE(0), max_iter);
    }
  };




  void test()
  {
    {
      PerfTest perfTest("Performance Demo (use recursion with complex type)", false, false, false);

      perfTest.test<CalcSequentiell<float, int, mandel::PixelComplex<mandel::Complex<float>>>>("Complex float");
      perfTest.test<CalcSequentiell<double, int, mandel::PixelComplex<mandel::Complex<double>>>>("Complex double");
      
      perfTest.test<CalcSequentiell<float, int, PixelRecComplex<mandel::Complex<float>>>>("Complex float recursion");
      perfTest.test<CalcSequentiell<double, int, PixelRecComplex<mandel::Complex<double>>>>("Complex double recursion");

      perfTest.test<CalcSequentiell<float, int, PixelRecComplexTailOpt<mandel::Complex<float>>>>("Complex float recursion tail opt");
      perfTest.test<CalcSequentiell<double, int, PixelRecComplexTailOpt<mandel::Complex<double>>>>("Complex double recursion tail opt");

      perfTest.test<CalcSequentiell<float, int, PixelRecComplexConstMember<mandel::Complex<float>>>>("Complex float tail recursion (const member)");
      perfTest.test<CalcSequentiell<double, int, PixelRecComplexConstMember<mandel::Complex<double>>>>("Complex double tail recursion (const member)");

      perfTest.test<CalcSequentiell<float, int, PixelRecComplexLambda<mandel::Complex<float>>>>("Complex float tail recursion lambda");
      perfTest.test<CalcSequentiell<double, int, PixelRecComplexLambda<mandel::Complex<double>>>>("Complex double tail recursion lambda");
    }
    {
      PerfTest perfTest("Performance Demo (use recursion)", false, false, false);

      perfTest.test<CalcSequentiell<float, int, mandel::Pixel<float>>>("float");
      perfTest.test<CalcSequentiell<double, int, mandel::Pixel<double>>>("double");

      perfTest.test<CalcSequentiell<float, int, PixelRecursion<float>>>("float Recursion");
      perfTest.test<CalcSequentiell<double, int, PixelRecursion<double>>>("double  Recursion");

      perfTest.test<CalcSequentiell<float, int, PixelTailRecursion<float>>>("float tail recursion");
      perfTest.test<CalcSequentiell<double, int, PixelTailRecursion<double>>>("double  tail recursion");
    }

  }

}
