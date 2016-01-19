#pragma once

#ifdef AUTOVEC_ENABLED

/*
cl d:\myproject\mylooptest.cpp /O2 /Qpar /Qpar-report:1
cl d:\myproject\mylooptest.cpp /O2 /Qpar /Qpar-report:2

add "/Qpar /Qpar-report:2" to the additional compiler options!

// http://msdn.microsoft.com/de-de/library/jj658585.aspx

don't work, because doIt call pixel and the loop in pixel creates: "the loop includes multiple exits". (Reason Code 500)
*/

#include "sequentiell.h"

namespace mandel 
{

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcAutoVec : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

#pragma loop(hint_parallel(4))
      for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
          const FLOAT_TYPE x = (i * dx) + x1;
          const FLOAT_TYPE y = (j * dy) + y1;
          auto iter = pixel(x, y);
          auto index = i + j * width;
          assert(0 <= index && index < picture.size());
          picture[index] = t(iter);
        }
      }
    }

  };

}

#endif
