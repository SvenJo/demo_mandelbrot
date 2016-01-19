#include "stdafx.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#pragma warning(push)
#pragma warning(disable: 4702)
#include "../extern/catch/catch.hpp"
#pragma warning(pop)

#include <functional>
#include <vector>
#include <cstdint>

#include <mandel/pixel.h>
#include <mandel/sequentiell.h>
#include <mandel/complex.h>

#include <easy/viewinfo.h>
#include <easy/picture.h>

#include "../demo/doloopdemo.h"
#include "../demo/floatinitdemo.h"
#include "../demo/perfdemo.h"
#include "../demo/recursion.h"

#include "test_helper.h"

namespace mandel
{
  using namespace easy;

  namespace unittest 
  {
    TEST_CASE("Pixel convergence for do_while_compare")
    {
      SECTION("PixelDoLoop")
      {
        do_while_compare::PixelDoLoop<float> pixelf;
        TestPixelConvergence(pixelf);
        do_while_compare::PixelDoLoop<double> pixeld;
        TestPixelConvergence(pixeld);
        do_while_compare::PixelDoLoop<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("PixelWhileLoop")
      {
        do_while_compare::PixelWhileLoop<float> pixelf;
        TestPixelConvergence(pixelf);
        do_while_compare::PixelWhileLoop<double> pixeld;
        TestPixelConvergence(pixeld);
        do_while_compare::PixelWhileLoop<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("PixelForLoop")
      {
        do_while_compare::PixelForLoop<float> pixelf;
        TestPixelConvergence(pixelf);
        do_while_compare::PixelForLoop<double> pixeld;
        TestPixelConvergence(pixeld);
        do_while_compare::PixelForLoop<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
    }

    TEST_CASE("Pixel convergence for floatinit_demo")
    {
      SECTION("Pixel2")
      {
        floatinit_demo::Pixel2<float> pixelf;
        TestPixelConvergence(pixelf);
        floatinit_demo::Pixel2<double> pixeld;
        TestPixelConvergence(pixeld);
        floatinit_demo::Pixel2<long double> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("Pixel2f")
      {
        floatinit_demo::Pixel2f<float> pixelf;
        TestPixelConvergence(pixelf);
        floatinit_demo::Pixel2f<double> pixeld;
        TestPixelConvergence(pixeld);
        floatinit_demo::Pixel2f<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("Pixel2_0")
      {
        floatinit_demo::Pixel2_0<float> pixelf;
        TestPixelConvergence(pixelf);
        floatinit_demo::Pixel2_0<double> pixeld;
        TestPixelConvergence(pixeld);
        floatinit_demo::Pixel2_0<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("Pixel_FLOAT_TYPE")
      {
        floatinit_demo::Pixel_FLOAT_TYPE<float> pixelf;
        TestPixelConvergence(pixelf);
        floatinit_demo::Pixel_FLOAT_TYPE<double> pixeld;
        TestPixelConvergence(pixeld);
        floatinit_demo::Pixel_FLOAT_TYPE<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
    }

    TEST_CASE("Pixel convergence for mandel::Complex")
    {
      SECTION("std::complex")
      {
        PixelComplex<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelComplex<std::complex<float>> pixeld;
        TestPixelConvergence(pixeld);
        PixelComplex<std::complex<float>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("mandel::Complex")
      {
        PixelComplex<mandel::Complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelComplex<mandel::Complex<float>> pixeld;
        TestPixelConvergence(pixeld);
        PixelComplex<mandel::Complex<float>> pixelld;
        TestPixelConvergence(pixelld);
      }
    }

    TEST_CASE("Pixel convergence for perf_demo")
    {
      SECTION("PixelComplexAbs")
      {
        perf_demo::PixelComplexAbs<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        perf_demo::PixelComplexAbs<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        perf_demo::PixelComplexAbs<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelFloatLikeInt")
      {
        using namespace perf_demo;

        PixelFloatLikeInt<float> pixelf;
        TestPixelConvergence(pixelf);
        PixelFloatLikeInt<double> pixeld;
        TestPixelConvergence(pixeld);
        PixelFloatLikeInt<long double> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelFloatLikeIntReverse")
      {
        using namespace perf_demo;

        PixelFloatLikeIntReverse<float> pixelf;
        TestPixelConvergence(pixelf);
        PixelFloatLikeIntReverse<double> pixeld;
        TestPixelConvergence(pixeld);
        PixelFloatLikeIntReverse<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
    }

    TEST_CASE("Pixel convergence for recursion_demo")
    {
      SECTION("PixelRecComplex")
      {
        using namespace recursion_demo;

        PixelRecComplex<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelRecComplex<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelRecComplex<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelRecComplexTailOpt")
      {
        using namespace recursion_demo;

        PixelRecComplexTailOpt<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelRecComplexTailOpt<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelRecComplexTailOpt<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelRecComplexConstMember")
      {
        using namespace recursion_demo;

        PixelRecComplexConstMember<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelRecComplexConstMember<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelRecComplexConstMember<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelRecComplexLambda")
      {
        using namespace recursion_demo;

        PixelRecComplexLambda<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelRecComplexLambda<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelRecComplexLambda<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelRecursion")
      {
        using namespace recursion_demo;

        PixelRecursion<float> pixelf;
        TestPixelConvergence(pixelf);
        PixelRecursion<double> pixeld;
        TestPixelConvergence(pixeld);
        PixelRecursion<long double> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelTailRecursion")
      {
        using namespace recursion_demo;

        PixelTailRecursion<float> pixelf;
        TestPixelConvergence(pixelf);
        PixelTailRecursion<double> pixeld;
        TestPixelConvergence(pixeld);
        PixelTailRecursion<long double> pixelld;
        TestPixelConvergence(pixelld);
      }

    }




#if 0
    TEST_CASE("Compare different algorithm (float)", "[basic]") 
    {
      using namespace std;

      ViewInfo view;
      view.resize(50, 50, 1.0);
      view.setZoom(-2.0, 2.0, -2.0, 2.0);

      Picture<int> picture_seq(view.width(), view.height());
      // init all values with -99
      fill(begin(picture_seq.data()), end(picture_seq.data()), -99);

      CalcSequentiell<float, int, Pixel<float>>()(view, picture_seq);

      // after the calc all value are different from the init value
      // all values in the range [1..100] (see pixel function!)
      test_values_in_range(picture_seq.data());

      SECTION("do_while_compare")
      {
        using namespace do_while_compare;

        SECTION("PixelDoLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelDoLoop<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelWhileLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelWhileLoop<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelForLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelForLoop<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
      }

      SECTION("floatinit_demo")
      {
        using namespace floatinit_demo;

        SECTION("Pixel2")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, Pixel2<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel2f")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, Pixel2f<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel2_0")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, Pixel2_0<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel_FLOAT_TYPE")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, Pixel_FLOAT_TYPE<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
      }
      SECTION("mandel::Complex")
      {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcSequentiell<float, int, PixelComplex<mandel::Complex<float>>>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      SECTION("perf_demo")
      {
        using namespace perf_demo;


        //* TODO: Fixme Test failing for float
        // i=45, j=10, re=
        // re = -1.59999990
        //. im = -1.20000005
        // 1.6*1.6+1.2+1.2 == 4.0
        SECTION("PixelComplexAbs")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelComplexAbs<std::complex<float>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          for (int j = 0; j < view.height(); ++j)
            for (int i = 0; i < view.width(); ++i) {
              int index = i + j* view.width();
              INFO("i = " << i << " j = " << j);
              REQUIRE(picture_test.data()[index] == picture_seq.data()[index]);
            }
          //REQUIRE(picture_test.data() == picture_seq.data());
        }
        //*/

        SECTION("PixelFloatLikeInt")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelFloatLikeInt<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        /*
        SECTION("PixelFloatLikeIntReverse")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<float, int, PixelFloatLikeIntReverse<float>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }*/


      }

    }
#endif
    
    TEST_CASE("Compare different algorithm (double)", "[basic]")
    {
      using namespace std;

      ViewInfo view;
      view.resize(50, 50, 1.0);
      view.setZoom(-2.0, 2.0, -2.0, 2.0);

      Picture<int> picture_seq(view.width(), view.height());
      // init all values with -99
      fill(begin(picture_seq.data()), end(picture_seq.data()), -99);

      CalcSequentiell<double, int, Pixel<double>>()(view, picture_seq);

      // after the calc all value are different from the init value
      // all values in the range [1..100] (see pixel function!)
      test_values_in_range(picture_seq.data());

      SECTION("do_while_compare")
      {
        using namespace do_while_compare;

        SECTION("PixelDoLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelDoLoop<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelWhileLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelWhileLoop<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelForLoop")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelForLoop<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
      }

      SECTION("floatinit_demo")
      {
        using namespace floatinit_demo;

        SECTION("Pixel2")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, Pixel2<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel2f")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, Pixel2f<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel2_0")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, Pixel2_0<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("Pixel_FLOAT_TYPE")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, Pixel_FLOAT_TYPE<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
      }
      SECTION("mandel::Complex")
      {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcSequentiell<double, int, PixelComplex<mandel::Complex<double>>>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      SECTION("perf_demo")
      {
        using namespace perf_demo;

        //* TODO: Fixme Test failing for float
        // i=45, j=10, re=
        // re = -1.59999990
        //. im = -1.20000005
        // 1.6*1.6+1.2+1.2 == 4.0
        SECTION("PixelComplexAbs")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelComplexAbs<std::complex<double>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          for (int j = 0; j < view.height(); ++j)
            for (int i = 0; i < view.width(); ++i) {
              int index = i + j* view.width();
              INFO("i = " << i << " j = " << j);
              REQUIRE(picture_test.data()[index] == picture_seq.data()[index]);
            }
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelFloatLikeInt")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelFloatLikeInt<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        SECTION("PixelFloatLikeIntReverse")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelFloatLikeIntReverse<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
      }

      SECTION("recursion_demo")
      {
        using namespace recursion_demo;

        SECTION("PixelRecComplex")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelRecComplex<std::complex<double>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }

        
        SECTION("PixelRecComplexTailOpt")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelRecComplexTailOpt<std::complex<double>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
        
        SECTION("PixelRecComplexConstMember")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelRecComplexConstMember<std::complex<double>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
        
        SECTION("PixelRecComplexLambda")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelRecComplexLambda<std::complex<double>>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
        
        /*
        SECTION("PixelRecursion")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelRecursion<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());

          for (int j = 0; j < view.height(); ++j)
            for (int i = 0; i < view.width(); ++i) {
              int index = i + j* view.width();
              INFO("i = " << i << " j = " << j);
              REQUIRE(picture_test.data()[index] == picture_seq.data()[index]);
            }

          REQUIRE(picture_test.data() == picture_seq.data());
        }
        /*
        SECTION("PixelTailRecursion")
        {
          Picture<int> picture_test(view.width(), view.height());
          fill(begin(picture_test.data()), end(picture_test.data()), -99);
          CalcSequentiell<double, int, PixelTailRecursion<double>>()(view, picture_test);
          test_values_in_range(picture_test.data());
          REQUIRE(picture_test.data() == picture_seq.data());
        }
        //*/



      }

    }


    


  }
}
