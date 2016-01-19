#pragma once
 
#include <perf_tester.h>
#include <mandel/sequentiell.h>

#include <mandel/pixel.h>
#include <mandel/openmp.h>

namespace do_while_compare {

  template<typename FLOAT_TYPE>
  struct PixelDoLoop
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
  
  template<typename FLOAT_TYPE>
  struct PixelWhileLoop
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      while (u2 + v2 < FLOAT_TYPE(4) && iter < max_iter) {
        v = FLOAT_TYPE(2) * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } 
      return iter;
    }
  };

  template<typename FLOAT_TYPE>
  struct PixelForLoop
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };

      for (int iter{0}; iter < max_iter; ++iter) {
        v = FLOAT_TYPE(2) * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        if (u2 + v2 >= FLOAT_TYPE(4)) return iter+1;
      }
      return max_iter;
    }

  };

  inline void test_default()
  {
    using namespace mandel;

    PerfTest perfTest("compare while loop vs. do loop\n" "test: default range [-1.8,1.2; -1.5,1.5]");

    perfTest.test<CalcSequentiell<float,  int, PixelDoLoop<float>>>("Do loop (float) ");
    perfTest.test<CalcSequentiell<double, int, PixelDoLoop<double>>>("Do loop (double)");
    
    perfTest.test<CalcSequentiell<float,  int, PixelWhileLoop<float>>>("While loop (float) ");
    perfTest.test<CalcSequentiell<double, int, PixelWhileLoop<double>>>("While loop (double)");

    perfTest.test<CalcSequentiell<float, int, PixelForLoop<float>>>("For loop (float) ");
    perfTest.test<CalcSequentiell<double, int, PixelForLoop<double>>>("For loop (double)");
  }
  
  inline void test_100()
  {
    using namespace mandel;

    PerfTest perfTest("compare while loop vs. do loop\n" "test: 100 iterations");

    // run 100 iterations [-0.1,0.1; -0.1, 0.1]
    perfTest.test<CalcSequentiell<float,  int, PixelDoLoop<float>>>("Do loop (float) ", -0.1, 0.1, -0.1, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelDoLoop<double>>>("Do loop (double)", -0.1, 0.1, -0.1, 0.1);
    
    perfTest.test<CalcSequentiell<float,  int, PixelWhileLoop<float>>>("While loop (float) ", -0.1, 0.1, -0.1, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelWhileLoop<double>>>("While loop (double)", -0.1, 0.1, -0.1, 0.1);

    perfTest.test<CalcSequentiell<float,  int, PixelForLoop<float>>>("For loop (float) ", -0.1, 0.1, -0.1, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelForLoop<double>>>("For loop (double)", -0.1, 0.1, -0.1, 0.1);
  }
  
  inline void test_2()
  {
    using namespace mandel;

    PerfTest perfTest("compare while loop vs. do loop\n" "test: 1 iteration");

    // run 100 iterations [2.0,2.1;  0.0, 0.1]
    perfTest.test<CalcSequentiell<float,  int, PixelDoLoop<float>>>("Do-Loop (float) ", 2.0, 2.1, 0.0, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelDoLoop<double>>>("Do-Loop (double)", 2.0, 2.1, 0.0, 0.1);
    
    perfTest.test<CalcSequentiell<float,  int, PixelWhileLoop<float>>>("While loop (float) ", 2.0, 2.1, 0.0, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelWhileLoop<double>>>("While loop (double)", 2.0, 2.1, 0.0, 0.1);

    perfTest.test<CalcSequentiell<float,  int, PixelForLoop<float>>>("For loop (float) ", 2.0, 2.1, 0.0, 0.1);
    perfTest.test<CalcSequentiell<double, int, PixelForLoop<double>>>("For loop (double)", 2.0, 2.1, 0.0, 0.1);
  }

}
