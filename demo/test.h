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
namespace test
{

  void test()
  {
    using namespace std;
    using namespace mandel;
    using namespace easy;
    /*
    cout << "sizeof(float)" << sizeof(float) << endl;
    cout << "sizeof(double)" << sizeof(double) << endl;
    cout << "sizeof(long double)" << sizeof(long double) << endl;
    */

    ViewInfo view;
    view.resize(40, 40, 1.0);
    view.setZoom(-2.0, 2.0, -2.0, 2.0);

    Picture<int> picture(view.width(), view.height());
    
    {
      fill(begin(picture.data()), end(picture.data()), -99);

      CalcSequentiell<float, int, Pixel<float>>()(view, picture);

      for (int j = 0; j < view.height(); ++j) {
        for (int i = 0; i < view.width(); ++i) {
          cout << picture.data()[i + j*view.width()] << " ";
        }
        cout << endl;
      }
    }

    {
      fill(begin(picture.data()), end(picture.data()), -99);

      CalcSimpleFutures<float, int>()(view, picture);

      for (int j = 0; j < view.height(); ++j) {
        for (int i = 0; i < view.width(); ++i) {
          cout << picture.data()[i + j*view.width()] << " ";
        }
        cout << endl;
      }
    }


  }
}
