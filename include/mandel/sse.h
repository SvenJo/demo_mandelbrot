#pragma once

#ifdef __SSE__
// compile with Advanced Vector Extensions 2 (/arch:AVX2) or at least SSE2

#include <xmmintrin.h>

#ifdef _MSC_VER
#include <fvec.h>
#include <ivec.h>
#include <dvec.h>
#endif

#include "sequentiell.h"

#include "intrinsics_helper.h"

#ifdef  _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4838 4244)
#endif


#ifdef _MSC_VER
#define ALIGMENT(size) __declspec(align(size))
#else
#define ALIGMENT(size) __attribute__((aligned(size)))
#endif


namespace mandel
{
  struct PixelSSE4f
  {
    std::array<int, 4> operator()(const std::array<float, 4>& re, const std::array<float, 4>& im, const int max_iter = 100) const
    {
      //std::array<int, 4> result;

      ALIGMENT(16) float fours[4] = { 4.0f, 4.0f, 4.0f, 4.0f };
      ALIGMENT(16) float onesF[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
      __m128 xmm5 = _mm_load_ps(fours);
      __m128 ones = _mm_load_ps(onesF);


      __m128 xmm6 = _mm_load_ps(re.data());   // 4 x and y values on a 2x2 grid
      __m128 xmm7 = _mm_load_ps(im.data());

      __m128 xmm0 = _mm_xor_ps(xmm6, xmm6); // zero out xmm0,xmm1,xmm3
      __m128 xmm1 = xmm0;
      __m128 xmm3 = xmm0;
      __m128 xmm2, xmm4;

      unsigned int test = 0;

      int iter = 0;
      do
      {
        xmm2 = xmm0;                       // xi
        xmm2 = _mm_mul_ps(xmm2, xmm1);     // xi * yi
        xmm0 = _mm_mul_ps(xmm0, xmm0);     // xi * xi
        xmm1 = _mm_mul_ps(xmm1, xmm1);     // yi * yi
        xmm4 = xmm0;                       // xi * xi
        xmm4 = _mm_add_ps(xmm4, xmm1);     // xi*xi + yi*yi
        xmm0 = _mm_sub_ps(xmm0, xmm1);     // xi*xi - yi*yi
        xmm0 = _mm_add_ps(xmm0, xmm6);     // xi*xi - yi*yi + x0
        xmm1 = xmm2;                       // xi*yi
        xmm1 = _mm_add_ps(xmm1, xmm1);     // 2*xi*yi
        xmm1 = _mm_add_ps(xmm1, xmm7);     // 2*xi*yi+y0

        xmm4 = _mm_cmplt_ps(xmm4, xmm5);   // xi*xi+yi*yi < 4 in each slot
                                           // now xmm4 has all 1s in the non overflowed locations
                                           // xmm0 has the new x value
                                           // xmm1 has the new y value
        test = _mm_movemask_ps(xmm4) & 15; // lower 4 bits are comparisons
        xmm4 = _mm_and_ps(xmm4, ones);     // get 1.0f or 0.0f in each field
        xmm3 = _mm_add_ps(xmm3, xmm4);     // xmm3 is counters for each pixel iteration

        ++iter;
      } while ((test != 0) && (iter < max_iter));

      std::array<int, 4> result; // = xmm3.m128_f32;
      result[0] = v128_f(xmm3, 0);
      result[1] = v128_f(xmm3, 1);
      result[2] = v128_f(xmm3, 2);
      result[3] = v128_f(xmm3, 3);

      return result;
    }

    static const int vec_size = 4;
  };


  // FLOAT_TYPE is always float!
  // don't work, because of missing resize
  template<typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcSSE : CalcMandelBrot<RESULT_TYPE>
  {
    // http://www.lomont.org/Software/
    // http://www.lomont.org/Math/Papers/2011/Intro%20to%20Intel%20AVX-Final.pdf
    //
    virtual void doIt(const int width, const int height, const double dX1, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PixelSSE4f pixel;

      const auto x1 = static_cast<float>(dX1);
      const auto y1 = static_cast<float>(dY1);
      const auto dx = static_cast<float>(dDx);
      const auto dy = static_cast<float>(dDy);

      assert(width * height == (int)picture.size());

      int widthEven = width & ~1UL; // todo - make work for odd height, width also
      int heightEven = height & ~1UL;


      for (int j = 0; j < heightEven; j += 2)
      {
        for (int i = 0; i < widthEven; i += 2)
        {
          std::array<float, 4> xi, yi;
          xi[0] = xi[2] = x1 + i*dx;
          xi[1] = xi[3] = x1 + (i + 1)*dx;
          yi[0] = yi[1] = y1 + j*dy;
          yi[2] = yi[3] = y1 + (j + 1)*dy;

          auto iter = pixel(xi, yi);

          picture[i + j*width]           = t(iter[0]);
          picture[i + 1 + j*width]       = t(iter[1]);
          picture[i + (j + 1)*width]     = t(iter[2]);
          picture[i + 1 + (j + 1)*width] = t(iter[3]);
        }
      }
    }

  };


#ifdef  _MSC_VER

  // Don't work because of missing resize!!!!

  template<typename RESULT_TYPE, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcFVec : CalcMandelBrot<RESULT_TYPE>
  {
    virtual void doIt(const int width, const int height, const double /*dX1*/, const double dY1, const double dDx, const double dDy, std::vector<RESULT_TYPE> &picture, const int max_iter = 100) const
    {
      TRANSFORM_TYPE t;

      ALIGMENT(16) float INIT_Y_4[4] = {0.0f, dDy, 2* dDy, 3* dDy};
      ALIGMENT(16) int I_RES[4] = { 0 };

      int i, j;
      F32vec4 x, y;

      F32vec4 F_STEP_Y(4.0f*dDy);

      I32vec4 I_ONE = _mm_set1_epi32(1);
      F32vec4 F_FOUR(4.0f);
      F32vec4 F_TWO(4.0f);

      for (i = 0, x = F32vec4(dDx); i < width; i++, x += F32vec4(dDx)) {
        for (j = 0, y = F32vec4(dY1) + *(F32vec4*)INIT_Y_4; j < height; j+=4, y += F_STEP_Y) {
          F32vec4 sx, sy;
          I32vec4 iter = _mm_setzero_si128();
          int scalar_iter = 0;

          sx = x;
          sy = y;
          while (scalar_iter < max_iter) {
            //int mask = 0;
            F32vec4 old_sx = sx;
            __m128 vmask = _mm_cmplt_ps(sx*sx + sy*sy, F_FOUR);

            if (_mm_test_all_ones(_mm_castps_si128(vmask))) break;

            if (_mm_test_all_zeros(_mm_castps_si128(vmask), _mm_castps_si128(vmask))) {

              sx = x + sx*sx - sy*sy;
              sy = y + F_TWO * old_sx*sy;
              iter += I_ONE;

            } else {
              sx = _mm_blendv_ps(x + sx*sx - sy*sy,    sx, vmask);
              sy = _mm_blendv_ps(y + F_TWO * old_sx*sy,sy, vmask);
            }
            scalar_iter++;
          }

          const auto index = i + j * width;
          assert(0 <= index && index < picture.size());
          _mm_storeu_si128((__m128i*)I_RES, iter);

          picture[index+0] = t(I_RES[0]);
          picture[index+1] = t(I_RES[1]);
          picture[index+2] = t(I_RES[2]);
          picture[index+3] = t(I_RES[3]);
        }
      }
    }

  };
  #endif

#ifdef  _MSC_VER
#pragma warning(pop)
#endif

}

#endif // __SSE__
