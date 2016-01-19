#pragma once

#ifdef VECTORCLASS_FOUND
// compile with Advanced Vector Extensions 2 (/arch:AVX2) or at least SSE2

#include "sequentiell.h"
#include "sse.h"

#include <vectorclass.h>

namespace mandel
{
  template<typename FLOAT_TYPE> struct Pixel_Vec_SSE;
  template<typename FLOAT_TYPE> struct Pixel_Vec_AVX;

  template<>
  struct Pixel_Vec_SSE<float> 
  {
    std::array<int, 4> operator()(const std::array<float, 4>& re, const std::array<float, 4>& im, const int max_iter = 100) const
    {
      std::array<int, 4> result;

      Vec4f x; x.load_a(re.data());
      Vec4f y; y.load_a(im.data());

      Vec4i iter(0);

      Vec4f u(0);
      Vec4f v(0);
      Vec4f u2(0);
      Vec4f v2(0);

      Vec4i flip(1, 1, 1, 1);

      do {
        v = 2.f * v * u + y;
        u = u2 - v2 + x;
        u2 = u * u;
        v2 = v * v;
        iter = iter + flip;
        flip = -((Vec4i)(u2 + v2 < 4.f) && (Vec4i)(iter < max_iter));

        //} while ((flip[0] + flip[1] + flip[2] + flip[3]) != 0);
      } while (horizontal_add(flip) != 0);

      result[0] = iter[0];
      result[1] = iter[1];
      result[2] = iter[2];
      result[3] = iter[3];

      return result;
    }

    static const int vec_size = 4;
  };

  template<>
  struct Pixel_Vec_SSE<double>
  {
    std::array<int, 2> operator()(const std::array<double, 2>& re, const std::array<double, 2>& im, const int max_iter = 100) const
    {
      std::array<int, 2> result;

      Vec2d x; x.load_a(re.data());
      Vec2d y; y.load_a(im.data());

      Vec2q iter(0);

      Vec2d u(0);
      Vec2d v(0);
      Vec2d u2(0);
      Vec2d v2(0);

      Vec2q flip(1, 1);

      do {
        v = 2.0 * v * u + y;
        u = u2 - v2 + x;
        u2 = u * u;
        v2 = v * v;
        iter = iter + flip;
        flip = -((Vec2q)(u2 + v2 < 4.0) && (Vec2q)(iter < max_iter));

        //} while ((flip[0] + flip[1] + flip[2] + flip[3]) != 0);
      } while (horizontal_add(flip) != 0);

      result[0] = (int)iter[0];
      result[1] = (int)iter[1];

      return result;
    }

    static const int vec_size = 2;
  };

  template<>
  struct Pixel_Vec_AVX<float>
  {
    std::array<int, 8> operator()(const std::array<float, 8>& re, const std::array<float, 8>& im, const int max_iter = 100) const
    {
      std::array<int, 8> result;

      Vec8f x; x.load_a(re.data());
      Vec8f y; y.load_a(im.data());

      Vec8i iter(0);

      Vec8f u(0);
      Vec8f v(0);
      Vec8f u2(0);
      Vec8f v2(0);

      Vec8i flip(1, 1, 1, 1, 1, 1, 1, 1);

      do {
        v = 2.f * v * u + y;
        u = u2 - v2 + x;
        u2 = u * u;
        v2 = v * v;
        iter = iter + flip;
        flip = -((Vec8i)(u2 + v2 < 4.f) && (Vec8i)(iter < max_iter));

        //} while ((flip[0] + flip[1] + flip[2] + flip[3]) != 0);
      } while (horizontal_add(flip) != 0);

      result[0] = iter[0];
      result[1] = iter[1];
      result[2] = iter[2];
      result[3] = iter[3];
      result[4] = iter[4];
      result[5] = iter[5];
      result[6] = iter[6];
      result[7] = iter[7];
      
      return result;
    }

    static const int vec_size = 8;
  };

  template<>
  struct Pixel_Vec_AVX<double>
  {
    std::array<int, 4> operator()(const std::array<double, 4>& re, const std::array<double, 4>& im, const int max_iter = 100) const
    {
      std::array<int, 4> result;

      Vec4d x; x.load_a(re.data());
      Vec4d y; y.load_a(im.data());

      Vec4q iter(0);

      Vec4d u(0);
      Vec4d v(0);
      Vec4d u2(0);
      Vec4d v2(0);

      Vec4q flip(1, 1, 1, 1);

      do {
        v = 2.0 * v * u + y;
        u = u2 - v2 + x;
        u2 = u * u;
        v2 = v * v;
        iter = iter + flip;
        flip = -((Vec4q)(u2 + v2 < 4.0) && (Vec4q)(iter < max_iter));

        //} while ((flip[0] + flip[1] + flip[2] + flip[3]) != 0);
      } while (horizontal_add(flip) != 0);

      result[0] = (int)iter[0];
      result[1] = (int)iter[1];
      result[2] = (int)iter[2];
      result[3] = (int)iter[3];

      return result;
    }

    static const int vec_size = 4;
  };

}

#endif // VECTORCLASS_FOUND
