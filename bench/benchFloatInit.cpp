#include <benchmark/benchmark.h>

#ifdef  _MSC_VER
#pragma warning(disable: 4244)
#endif

static void setValue(int i)
{
#ifdef _MSC_VER
  static volatile int valueG = 0;
  valueG = i;
#else
  asm volatile("" : "+rm" (i));
#endif
}

template<typename FLOAT_TYPE>
int Pixel2(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100)
{
  FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
  int iter{ 0 };

  do {
    v = 2 * v * u + im;
    u = u2 - v2 + re;
    u2 = u*u;
    v2 = v*v;
    ++iter;
  } while (u2 + v2 < 4 && iter < max_iter);
  return iter;
}

template<typename FLOAT_TYPE>
int Pixel2f(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100)
{
  FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
  int iter{ 0 };

  do {
    v = 2.f * v * u + im;
    u = u2 - v2 + re;
    u2 = u*u;
    v2 = v*v;
    ++iter;
  } while (u2 + v2 < 4.f && iter < max_iter);
  return iter;
}

template<typename FLOAT_TYPE>
int Pixel2_0(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100)
{
  FLOAT_TYPE u{ 0 }, v{ 0 }, u2{ 0 }, v2{ 0 };
  int iter{ 0 };

  do {
    v = 2.0 * v * u + im;
    u = u2 - v2 + re;
    u2 = u*u;
    v2 = v*v;
    ++iter;
  } while (u2 + v2 < 4.0 && iter < max_iter);
  return iter;
}

template<typename FLOAT_TYPE>
int Pixel_FLOAT_TYPE(const FLOAT_TYPE re, const FLOAT_TYPE im, const int max_iter = 100)
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


static void BM_float__init_2(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const float re = state.range_x() * 1.f;
    const float im = state.range_y() * 1.f;

    int iter = Pixel2<float>(re, im);
    setValue(iter);
  }
}

static void BM_double_init_2(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double re = state.range_x() * 1.f;
    const double im = state.range_y() * 1.f;

    int iter = Pixel2<double>(re, im);
    setValue(iter);
  }
}

static void BM_float__init_2f(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const float re = state.range_x() * 1.f;
    const float im = state.range_y() * 1.f;

    int iter = Pixel2f(re, im);
    setValue(iter);
  }
}

static void BM_double_init_2f(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double re = state.range_x() * 1.f;
    const double im = state.range_y() * 1.f;

    int iter = Pixel2f<double>(re, im);
    setValue(iter);
  }
}

static void BM_float__init_20(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const float re = state.range_x() * 1.f;
    const float im = state.range_y() * 1.f;

    int iter = Pixel2_0<float>(re, im);
    setValue(iter);
  }
}

static void BM_double_init_20(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double re = state.range_x() * 1.f;
    const double im = state.range_y() * 1.f;

    int iter = Pixel2_0<double>(re, im);
    setValue(iter);
  }
}

static void BM_float__init_temple_param(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const float re = state.range_x() * 1.f;
    const float im = state.range_y() * 1.f;

    int iter = Pixel_FLOAT_TYPE<float>(re, im);
    setValue(iter);
  }
}

static void BM_double_init_temple_param(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double re = state.range_x() * 1.f;
    const double im = state.range_y() * 1.f;

    int iter = Pixel_FLOAT_TYPE<double>(re, im);
    setValue(iter);
  }
}


BENCHMARK(BM_float__init_2)->ArgPair(0, 0);
BENCHMARK(BM_double_init_2)->ArgPair(0, 0);

BENCHMARK(BM_float__init_2f)->ArgPair(0, 0);
BENCHMARK(BM_double_init_2f)->ArgPair(0, 0);

BENCHMARK(BM_float__init_20)->ArgPair(0, 0);
BENCHMARK(BM_double_init_20)->ArgPair(0, 0);

BENCHMARK(BM_float__init_temple_param)->ArgPair(0, 0);
BENCHMARK(BM_double_init_temple_param)->ArgPair(0, 0);

BENCHMARK_MAIN()
