#pragma once

#ifdef TBB_FOUND

#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>

#include "sequentiell.h"
#include "sse_vectorclass.h"

namespace mandel
{

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE = Pixel<FLOAT_TYPE>, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcTBB : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      tbb::parallel_for(int(0), int(height), [&](int j) {
        const FLOAT_TYPE y = (j * dy) + y1;
        for (auto i = int(0); i < width; ++i) {
          const FLOAT_TYPE x = (i * dx) + x1;          
          const auto iter = pixel(x, y);
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      });
    }

  };
  
  
  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcTBBVec : CalcMandelBrot < RESULT_TYPE >
  {

    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixelvec;
      Pixel<FLOAT_TYPE> pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);
      
      const int vec_missing = width % PIXEL_TYPE::vec_size;
      const int vec_width = width - vec_missing;

      tbb::parallel_for(int(0), int(height), [&](int j) {
        const FLOAT_TYPE y = (j * dy) + y1;
        for (int i = 0; i < vec_width; i += PIXEL_TYPE::vec_size) {
          ALIGMENT(16) std::array<FLOAT_TYPE, PIXEL_TYPE::vec_size> re, im;
          for (int n = 0; n < PIXEL_TYPE::vec_size; ++n) {
            re[n] = ((i + n) * dx) + x1;
            im[n] = y;
          }

          auto iter = pixelvec(re, im);

          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          for (int n = 0; n < PIXEL_TYPE::vec_size; ++n) {
            picture[index + n] = t(iter[n]);
          }
        }
        for (int i = vec_width; i < width; ++i) {
          const FLOAT_TYPE x = (i * dx) + x1;
          const auto iter = pixel(x, y);
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      });
    }

  };

}

#endif // TBB_FOUND
