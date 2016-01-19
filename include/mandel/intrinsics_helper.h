#pragma once

#ifdef __SSE__

namespace mandel
{
  // helper for gcc (linux)
  // clang and msvc are able to support V[i]
#ifdef __GNUC__

  namespace detail
  {
    union U {
      __m128 v;    // SSE 4 x float vector
      float a[4];  // scalar array of 4 floats
    };
  }

  inline float v128_f(__m128 V, unsigned int i)
  {
    assert(i <= 3);
    detail::U u; u.v = V;
    return u.a[i];
  }
#elif _MSC_VER   

  inline float v128_f(__m128 V, unsigned int i) { return V.m128_f32[i]; }

#else
#error unknown compiler
#endif

}

#endif // __SSE__
