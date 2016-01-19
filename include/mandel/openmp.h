/**
control OpenMP on the cmd line:
set OMP_NUM_THREADS = 16
*/

#pragma once

#ifdef OPENMP_FOUND

#include <omp.h>

#include "sequentiell.h"
#include "sse.h"
#include "intrinsics_helper.h"

namespace mandel
{

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE = Pixel<FLOAT_TYPE>, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcOpenMP : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);
 /*
#pragma omp parallel for
/*/
#pragma omp parallel for schedule(dynamic)
//#pragma omp parallel for schedule(guided)
//*/
      for (int j = 0; j < height; ++j) {
        const FLOAT_TYPE y = (j * dy) + y1;
        for (int i = 0; i < width; ++i) {
          const FLOAT_TYPE x = (i * dx) + x1;
          auto iter = pixel(x, y);
          auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      }
    }

  };

}

#endif
