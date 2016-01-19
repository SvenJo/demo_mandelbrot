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
#include <mandel/openmp.h>
#include <mandel/complex.h>
#include <mandel/future.h>
#include <mandel/tbb.h>
#include <mandel/sse_vectorclass.h>

#include <easy/viewinfo.h>
#include <easy/picture.h>

#include "test_helper.h"

namespace mandel
{
  using namespace easy;

  namespace unittest 
  {
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

      SECTION("compare with openmp") {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcOpenMP<float, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      /*
      SECTION("compare with futures (simple version)")
      {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcSimpleFutures<float, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      //*/
      //*
      SECTION("compare TBB") {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcTBB<float, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      //*/

      /*
      SECTION("compare with sse") {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcSSE<int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      //*/
    }

    TEST_CASE("Compare different algorithm (double)", "[basic]") {

      using namespace std;

      ViewInfo view;
      view.resize(50, 50, 1.0);
      view.setZoom(-2.0, 2.0, -2.0, 2.0);

      Picture<int> picture_seq(view.width(), view.height());
      // init all values with -99
      fill(begin(picture_seq.data()), end(picture_seq.data()), -99);

      CalcSequentiell<double, int>()(view, picture_seq);

      // after the calc all value are different from the init value
      // all values in the range [1..100] (see pixel function!)
      test_values_in_range(picture_seq.data());

      SECTION("compare with openmp") {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcOpenMP<double, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      /*
      SECTION("compare with futures (simple version)")
      {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcSimpleFutures<double, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      */
      //*
      SECTION("compare TBB") {
        Picture<int> picture_test(view.width(), view.height());
        fill(begin(picture_test.data()), end(picture_test.data()), -99);
        CalcTBB<double, int>()(view, picture_test);
        test_values_in_range(picture_test.data());
        REQUIRE(picture_test.data() == picture_seq.data());
      }
      //*/

    }
    

    TEST_CASE("Pixel convergence")
    {

      SECTION("Pixel") {
        Pixel<float> pixelf;
        TestPixelConvergence(pixelf);
        Pixel<double> pixeld;
        TestPixelConvergence(pixeld);
        Pixel<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("Pixel1989") {
        Pixel1989<float> pixelf;
        TestPixelConvergence(pixelf);
        Pixel1989<double> pixeld;
        TestPixelConvergence(pixeld);
        Pixel1989<long double> pixelld;
        TestPixelConvergence(pixelld);
      }
      SECTION("PixelInt") {
        PixelInt<int,1000> pixelf;
        TestPixelConvergence(pixelf);
        PixelInt<int64_t, 10000> pixeld;
        TestPixelConvergence(pixeld);
        PixelInt<long long, 10000> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelComplex, std::complex") {
        PixelComplex<std::complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelComplex<std::complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelComplex<std::complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("PixelComplex, mandel::Complex") {
        PixelComplex<mandel::Complex<float>> pixelf;
        TestPixelConvergence(pixelf);
        PixelComplex<mandel::Complex<double>> pixeld;
        TestPixelConvergence(pixeld);
        PixelComplex<mandel::Complex<long double>> pixelld;
        TestPixelConvergence(pixelld);
      }

      SECTION("Pixel_Vec_SSE")
      {
        SECTION("float")
        {
          Pixel_Vec_SSE<float> pixelf;

          ALIGMENT(16) std::array<float, Pixel_Vec_SSE<float>::vec_size>
            re = { 0., -1., 0., 0. }, 
            im = { 0.,  0., 0., 0. };

          const auto res = pixelf(re, im);
          REQUIRE(100 == res[0]);
          REQUIRE(100 == res[1]);
          REQUIRE(100 == res[2]);
          REQUIRE(100 == res[3]);
        }
        SECTION("double")
        {
          Pixel_Vec_SSE<double> pixeld;

          ALIGMENT(16) std::array<double, Pixel_Vec_SSE<double>::vec_size>
            re = { 0., -1. },
            im = { 0.,  0. };

          const auto res = pixeld(re, im);
          REQUIRE(100 == res[0]);
          REQUIRE(100 == res[1]);          
        }

        
      }

      SECTION("Pixel_Vec_AVX")
      {
        
      }


    }


  }
}