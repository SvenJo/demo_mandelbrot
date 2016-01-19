#pragma once

#include <perf_tester.h>
#include <mandel/sequentiell.h>

#include <mandel/pixel.h>
#include <mandel/openmp.h>

#ifdef  _MSC_VER
#pragma warning(disable: 4244)
#endif

namespace floatinit_demo {

  template<typename FLOAT_TYPE>
  struct Pixel2
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      do {
        v = 2 * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } while (u2 + v2 < 4 && iter < max_iter);
      return iter;
    }
  };

  template<typename FLOAT_TYPE>
  struct Pixel2f
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      do {
        v = 2.f * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } while (u2 + v2 < 4.f && iter < max_iter);
      return iter;
    }
  };

  template<typename FLOAT_TYPE>
  struct Pixel2_0
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      do {
        v = 2.0 * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } while (u2 + v2 < 4.0 && iter < max_iter);
      return iter;
    }
  };

  template<typename FLOAT_TYPE>
  struct Pixel_FLOAT_TYPE
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      do {
        v = FLOAT_TYPE(2) * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } while (u2 + v2 < FLOAT_TYPE(4) && iter < max_iter);
      return iter;
    }

  };


  inline void test()
  {
    using namespace mandel;

    PerfTest perfTest("Performance Demo(different initializations)");

    perfTest.test<CalcSequentiell<float,  int, Pixel2<float>>>("float  2 (int literal)");
    perfTest.test<CalcSequentiell<double, int, Pixel2<double>>>("double 2 (int literal)");

    perfTest.test<CalcSequentiell<float,  int, Pixel2f<float>>>("float  2.f (float literal) ");
    perfTest.test<CalcSequentiell<double, int, Pixel2f<double>>>("double 2.f (float literal)");

    perfTest.test<CalcSequentiell<float,  int, Pixel2_0<float>>>("float  2.0 (double literal) ");
    perfTest.test<CalcSequentiell<double, int, Pixel2_0<double>>>("double 2.0 (double literal)");

    perfTest.test<CalcSequentiell<float,  int, Pixel_FLOAT_TYPE<float>>>("float  template type cast");
    perfTest.test<CalcSequentiell<double, int, Pixel_FLOAT_TYPE<double>>>("double template type cast");
  }

}
