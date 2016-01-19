#pragma once

#include <valarray>

#include <perf_tester.h>
#include <mandel/sequentiell.h>

#include <mandel/pixel.h>
#include <mandel/openmp.h>
#include <mandel/sse_vectorclass.h>


namespace simd_demo {

  inline void test()
  {
    using namespace mandel;

    PerfTest perfTest("SIMD", false, true);

    perfTest.test<CalcSequentiell<float,  int, mandel::Pixel<float>>>("Sequential (float)");
    perfTest.test<CalcSequentiell<double, int, mandel::Pixel<double>>>("Sequential (double)");

#ifdef VECTORCLASS_FOUND
    perfTest.test<CalcSequentiellVec1<float,  int, mandel::Pixel_Vec_SSE<float>>>("SSE (float)");
    perfTest.test<CalcSequentiellVec1<double, int, mandel::Pixel_Vec_SSE<double>>>("SSE (double)");

#ifdef AVX_ENABLED
    perfTest.test<CalcSequentiellVec1<float,  int, mandel::Pixel_Vec_AVX<float>>>("AVX (float)");
    perfTest.test<CalcSequentiellVec1<double, int, mandel::Pixel_Vec_AVX<double>>>("AVX (double)");
#endif

#ifdef TBB_FOUND
    perfTest.test<CalcTBBVec<float,  int, mandel::Pixel_Vec_SSE<float>>>("SSE + TBB (float)");
    perfTest.test<CalcTBBVec<double, int, mandel::Pixel_Vec_SSE<double>>>("SSE + TBB (double)");


#ifdef AVX_ENABLED
    perfTest.test<CalcTBBVec<float,  int, mandel::Pixel_Vec_AVX<float>>>("AVX + TBB (float)");
    perfTest.test<CalcTBBVec<double, int, mandel::Pixel_Vec_AVX<double>>>("AVX + TBB (double)");
#endif
#endif // TBB_FOUND
#endif // VECTORCLASS_FOUND
  }

  inline void valarraytest()
  {
    using namespace std;

    valarray<float> re{ 0.f, 2.1f, 0.5f, 0.3f }, im{ 0.f, 0.1f, 1.2f, 3.3f };

    valarray<float> u(0.f, 4), v(0.f, 4), u2(0.f, 4), v2(0.f, 4);
    valarray<int> iter(1, 4);

    for (int it = 1; it < 100; ++it) {
      v = 2.f * v * u + im;
      u = u2 - v2 + re;
      u2 = u*u;
      v2 = v*v;

      valarray<bool> cmp = u2 + v2 < 4.f;
      valarray<int> tmp(4); for (int i = 0; i < 4; ++i) tmp[i] = cmp[i] ? 1 : 0;

      if (tmp.sum() == 0) break;
      iter += tmp;
    }
    for (auto i : iter) {
      cout << i << " ";
    }
    cout << endl;

  }


}
