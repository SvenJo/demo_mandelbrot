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

// n from 1 to 100
#define UNROLL(n) \
v = FLOAT_TYPE(2) * v * u + im; \
u = u2 - v2 + re; \
u2 = u*u; \
v2 = v*v; \
if (u2 + v2 >= FLOAT_TYPE(4)) return (n)

// m from 0 to 95, step 5
#define UNROLL5(m) \
UNROLL((2 * m) + 1); \
UNROLL((2 * m) + 2); \
UNROLL((2 * m) + 3); \
UNROLL((2 * m) + 4); \
UNROLL((2 * m) + 5)

// m from 0 to 90, step 10
#define UNROLL10(m) \
UNROLL((m) + 1); \
UNROLL((m) + 2); \
UNROLL((m) + 3); \
UNROLL((m) + 4); \
UNROLL((m) + 5); \
UNROLL((m) + 6); \
UNROLL((m) + 7); \
UNROLL((m) + 8); \
UNROLL((m) + 9); \
UNROLL((m) + 10)

namespace unroll
{
  namespace details
  {
      
    template<typename FLOAT_TYPE>
    struct PixelFullUnroll
    {
      int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, int=100) const
      {
        FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };

        UNROLL10(0);
        UNROLL10(10);
        UNROLL10(20);
        UNROLL10(30);
        UNROLL10(40);
        UNROLL10(50);
        UNROLL10(60);
        UNROLL10(70);
        UNROLL10(80);
        UNROLL10(90);
        return 100;
      }
    };

    template<typename FLOAT_TYPE>
    struct PixelUnroll10
    {
      int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, int=100) const
      {
        FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };

        for (int i = 0; i < 91; i += 10) {
          UNROLL10(i);
        }
        return 100;
      }
    };

    template<typename FLOAT_TYPE>
    struct PixelUnroll5
    {
      int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, int=100) const
      {
        FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };

        for (int i = 0; i < 96; i += 5) {
          UNROLL5(i);
        }
        return 100;
      }
    };

  }
}

#undef UNROLL
#undef UNROLL5
#undef UNROLL10

  namespace unroll
  {
    using namespace std;
    using namespace mandel;
    using namespace details;

  void demo()
  {
    PerfTest perfTest("Unroll Performance Demo");

    perfTest.test<CalcSequentiell<float, int, mandel::Pixel<float>>>("(float)");
    perfTest.test<CalcSequentiell<float, int, PixelUnroll5< float>>>("unroll  5 (float)");
    perfTest.test<CalcSequentiell<float, int, PixelUnroll10<float>>>("unroll 10 (float)");
    perfTest.test<CalcSequentiell<float, int, PixelFullUnroll<float>>>("unroll full (float)");

    perfTest.test<CalcSequentiell<double, int, mandel::Pixel<double>>>("(double)");
    perfTest.test<CalcSequentiell<double, int, PixelUnroll5< double>>>("unroll  5 (double)");
    perfTest.test<CalcSequentiell<double, int, PixelUnroll10<double>>>("unroll 10 (double)");
    perfTest.test<CalcSequentiell<double, int, PixelFullUnroll<double>>>("unroll full (double)");
  }

}
