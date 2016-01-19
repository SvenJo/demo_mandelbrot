#include <benchmark/benchmark.h>
#include <cmath>

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

static void setValue(double d)
{
#ifdef _MSC_VER
  static volatile double valueG = 0;
  valueG = d;
#else
  asm volatile("" : "+rm" (d));
#endif
}

static void BM_int_none(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    setValue(a+b);
  }
}


static void BM_int_add(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    const int res = a + b;
    setValue(a + res);
  }
}

static void BM_int_minus(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    const int res = a - b;
    setValue(a + res);
  }
}

static void BM_int_mul(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    const int res = a * b;
    setValue(a + res);
  }
}

static void BM_int_div(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    const int res = a / b;
    setValue(a + res);
  }
}

static void BM_int_mod(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const int a = state.range_x() * 1.f;
    const int b = state.range_y() * 1.f;

    const int res = a % b;
    setValue(a + res);
  }
}


static void BM_double_none(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    setValue(a + b);
  }
}


static void BM_double_add(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    const double res = a + b;
    setValue(a + res);
  }
}

static void BM_double_minus(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    const double res = a - b;
    setValue(a + res);
  }
}

static void BM_double_mul(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    const double res = a * b;
    setValue(a + res);
  }
}

static void BM_double_div(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    const double res = a / b;
    setValue(a + res);
  }
}

static void BM_double_mod(benchmark::State& state)
{
  while (state.KeepRunning()) {
    const double a = state.range_x() * 1.f;
    const double b = state.range_y() * 1.f;

    const double res = fmod(a,b);
    setValue(a + res);
  }
}



BENCHMARK(BM_int_none)->ArgPair(7, 3);
BENCHMARK(BM_int_add)->ArgPair(7, 3);
BENCHMARK(BM_int_minus)->ArgPair(7, 3);
BENCHMARK(BM_int_mul)->ArgPair(7, 3);
BENCHMARK(BM_int_div)->ArgPair(7, 3);
BENCHMARK(BM_int_mod)->ArgPair(7, 3);

BENCHMARK(BM_double_none)->ArgPair(7, 3);
BENCHMARK(BM_double_add)->ArgPair(7, 3);
BENCHMARK(BM_double_minus)->ArgPair(7, 3);
BENCHMARK(BM_double_mul)->ArgPair(7, 3);
BENCHMARK(BM_double_div)->ArgPair(7, 3);
BENCHMARK(BM_double_mod)->ArgPair(7, 3);

BENCHMARK_MAIN()
