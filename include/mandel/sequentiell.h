#pragma once

#include <easy/picture.h>
#include <easy/viewinfo.h>

#include <cassert>
#include <vector>

#include "pixel.h"

#ifdef _MSC_VER
#define ALIGMENT(size) __declspec(align(size))
#else
#define ALIGMENT(size) __attribute__((aligned(size)))
#endif

template<typename RESULT_TYPE>
struct null_transform
{
  null_transform(int = 0) {}

  RESULT_TYPE operator()(const int value) const
  {
    return static_cast<RESULT_TYPE>(value);
  }
};

namespace mandel {

  template<typename RES_TYPE>
  struct CalcMandelBrot
  {
    using RESULT_TYPE = RES_TYPE;

    /**
    Calculate the mandelbrot set.

    For continence use x1, x2 y1, y2 as double coordinate. The algorithm use x1, y1, dx and dy.

    The interface of the base class use int and double types, but the derived class may work on different types. (e.g. size_t for loop index or float for the calculations)
    */
    void operator() (const easy::ViewInfo& view, easy::Picture<RESULT_TYPE>& picture) const
    {
      assert(picture.width() * picture.height() <= (int)picture.size());
      assert(0 < view.width() && 0 < view.height());
      assert(view.x1() < view.x2());
      assert(view.y1() < view.y2());

      doIt(view.width(), view.height(), view.x1(), view.y1(), view.dx(), view.dy(), picture.data());
    }


  private:
    virtual void doIt(const int width, const int height, const double x1, const double y1, const double dx, const double dy, std::vector<RESULT_TYPE> &picture) const = 0;
  };

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE = Pixel<FLOAT_TYPE>, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcSequentiell : CalcMandelBrot < RESULT_TYPE >
  {
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto dx = static_cast<FLOAT_TYPE>(dDx);
      const auto dy = static_cast<FLOAT_TYPE>(dDy);

      for (int j = 0; j < height; ++j) {
        const auto y = (j * dy) + y1;
        for (int i = 0; i < width; ++i) {
          const auto x = (i * dx) + x1;
          const auto iter = pixel(x, y);
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      }
    }
  };

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcSequentiellVec : CalcMandelBrot < RESULT_TYPE >
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

      for (int j = 0; j < height; ++j) {
        const auto y = (j * dy) + y1;
        for (int i = 0; i < vec_width; i+=PIXEL_TYPE::vec_size) {
          ALIGMENT(16) std::array<float, PIXEL_TYPE::vec_size> re, im;
          for (int n = 0; n < PIXEL_TYPE::vec_size; ++n) {
            re[n] = ((i+n) * dx) + x1;
            im[n] = y;
          }
          
          auto iter = pixelvec(re, im);
          
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          for (int n = 0; n < PIXEL_TYPE::vec_size; ++n) {
            picture[index+n] = t(iter[n]);
          }
        }
        for (int i = vec_width; i < width; ++i) {
          const auto x = (i * dx) + x1;
          const auto iter = pixel(x, y);
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      }
    }
  };

  template<typename FLOAT_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcSequentiellVec1 : CalcMandelBrot < RESULT_TYPE >
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

      for (int j = 0; j < height; ++j) {
        const auto y = (j * dy) + y1;
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
          const auto x = (i * dx) + x1;
          const auto iter = pixel(x, y);
          const auto index = i + j * width;
          assert(0 <= index && index < (int)picture.size());
          picture[index] = t(iter);
        }
      }
    }
  };

}
