#pragma once

#ifdef  AMP_ENABLED

#include "sequentiell.h"

#include <amp.h>

/*
TODO:
- use tiles: otherwise the perf tests will not run. (to big for the graphics card memory)
- create a restrict transform function into the color space (bernstein transform)
*/

#define TILE_SIZE       32

namespace mandel 
{

  template<typename FLOAT_TYPE>
  int pixel_amp(const FLOAT_TYPE x, const FLOAT_TYPE y, const int max_iter = 100) restrict(amp)
  {
    auto u = FLOAT_TYPE{ 0 };
    auto v = FLOAT_TYPE{ 0 };
    auto u2 = FLOAT_TYPE{ 0 };
    auto v2 = FLOAT_TYPE{ 0 };
    auto iter = int{ 0 };

    do {
      v = 2 * v * u + y;
      u = u2 - v2 + x;
      u2 = u*u;
      v2 = v*v;
      ++iter;
    } while ((u2 + v2 < 4.0) && (iter < max_iter));
    return iter;
  }

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcAMP : CalcMandelBrot < RESULT_TYPE >
  {

    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      using namespace concurrency;

      TRANSFORM_TYPE t;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      array_view<RESULT_TYPE, 2> a(height, width, picture.data());
      a.discard_data();

      parallel_for_each(a.extent, [=](index<2> idx) restrict(amp) {

        int j = idx[0];
        int i = idx[1];

        const FLOAT_TYPE x = (i * dx) + x1;
        const FLOAT_TYPE y = (j * dy) + y1;
        int iter = pixel_amp(x, y);

        a[idx] = iter;
      });
      a.synchronize();

      for (auto& i : picture) i = t(i);
    }
  };


  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcAMP_tile : CalcMandelBrot < RESULT_TYPE >
  {

    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      using namespace concurrency;

      TRANSFORM_TYPE t;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      array_view<RESULT_TYPE, 2> a(height, width, picture.data());
      a.discard_data();

      parallel_for_each(a.extent.tile<10, 10>(), [=](index<2> idx) restrict(amp) {

        int j = idx[0];
        int i = idx[1];

        const FLOAT_TYPE x = (i * dx) + x1;
        const FLOAT_TYPE y = (j * dy) + y1;
        int iter = pixel_amp(x, y);

        a[idx] = iter;
      });
      a.synchronize();

      for (auto& i : picture) i = t(i);
    }
  };

}

#endif // AMP_ENABLED
