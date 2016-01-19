#pragma once

namespace mandel
{
  template<typename FLOAT_TYPE>
  struct Pixel
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      int iter{ 0 };

      do {
        v = FLOAT_TYPE(2) * v * u + im;
        u = u2 - v2 + re;
        u2 = u*u;
        v2 = v*v;
        ++iter;
      } while (u2 + v2 < FLOAT_TYPE(4) && iter < max_iter);
      return iter;
    }
  };

  template<typename FLOAT_TYPE>
  struct Pixel1989
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      FLOAT_TYPE u{ 0 }, v{ 0 };
      int iter{ 0 };

      do {
        const FLOAT_TYPE uu = v*v - u*u + re;
        u = FLOAT_TYPE(2) * u*v + im;
        v = uu;
        ++iter;
      } while (u*u + v*v < FLOAT_TYPE(4.0) && iter < max_iter);
      return iter;
    }
  };

  template<typename INT_TYPE, int SHIFT = 1000>
  struct PixelInt
  {
    int operator()(const double re, const double im, const int max_iter = 100) const
    {
      INT_TYPE u{ 0 }, v{ 0 };
      const INT_TYPE rm_ = int(re * SHIFT );
      const INT_TYPE im_ = int(im * SHIFT);
      int iter{ 0 };

      do {
        const INT_TYPE uold = u;
        u = (u*u - v*v) / SHIFT + rm_;
        v = (2 * uold*v) / SHIFT + im_;
        ++iter;
      } while ((u*u + v*v) < 4 * SHIFT * SHIFT && iter < max_iter);
      return iter;
    }
  };


  /*
  //Don't work: reduce SHIFT to 100 to get a minimal result!

  template<typename INT_TYPE, int SHIFT = 100>
  struct PixelInt
  {
    int operator()(const double re, const double im, const int max_iter = 100)
    {
      INT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
      auto iter = int{ 0 };

      INT_TYPE re_ = (int)(re * SHIFT);
      INT_TYPE im_ = (int)(im * SHIFT);

      do {
        v  = 2   * v  * u / SHIFT + im_;
        u  = u2  - v2  + re_;
        u2  = u *u / SHIFT;
        v2  = v *v / SHIFT;
        ++iter;
      } while (((u2 + v2) < (4 * SHIFT * SHIFT)) && (iter < max_iter));
      return iter;
    }
  };*/

  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct PixelComplex
  {
    int operator()(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100) const
    {
      const COMPLEX_TYPE c = { re, im };
      COMPLEX_TYPE z = { 0. };
      int iter{ 0 };

      do {
        z = z * z + c;
        ++iter;
      } while ((z.imag() * z.imag() + z.real() * z.real() < FLOAT_TYPE(4.0)) && (iter < max_iter));

      return iter;
    }
  };

}
