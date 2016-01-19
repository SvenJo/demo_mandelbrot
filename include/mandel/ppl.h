#pragma once

// work only with the MS compiler
/*
TODO:
add partitioners
*/

#ifdef PPL_ENABLED

#include "sequentiell.h"
#include "sse.h"

#include <ppl.h>

#include <xmmintrin.h>
#include "intrinsics_helper.h"

namespace mandel
{

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcPPL : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      Pixel<FLOAT_TYPE> pixel;

      using namespace concurrency;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      parallel_for(int(0), height, [&](int j) {

        for (int i = 0; i < width; ++i) {
          const FLOAT_TYPE x = (i * dx) + x1;
          const FLOAT_TYPE y = (j * dy) + y1;
          auto iter = pixel(x, y);
          auto index = i + j * width;
          assert(0 <= index && index < picture.size());
          picture[index] = t(iter);
        }
      });
    }
  };

}

#endif
