#pragma once

#include <future>

#include "sequentiell.h"

namespace mandel
{
  template<typename Body>
  void SimpleFutureFor(int start, int end, Body body)
  {
    const int num_of_threads = std::thread::hardware_concurrency();
    std::vector<std::future<void>> threads; threads.reserve(num_of_threads);

    for (int thrdIdx = 0; thrdIdx < num_of_threads; ++thrdIdx) {
      threads.emplace_back(std::async(std::launch::async, [&] {
        for (int j = start + thrdIdx; j < end; j += num_of_threads)
          body(j);
      }));
    }
    for (auto& t : threads)
      t.get();
  }

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE = Pixel<FLOAT_TYPE>, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcSimpleFutures : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      SimpleFutureFor(0, height, [&](int j) {
          const auto y = (j * dy) + y1;
          for (int i = 0; i < width; ++i) {
            const auto x = (i * dx) + x1;
            const auto iter = pixel(x, y);
            const auto index = i + j * width;
            assert(0 <= index && index < (int)picture.size());
            picture[index] = t(iter);
          }
      });
    }
  };

}
