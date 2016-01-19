#include <benchmark/benchmark.h>

#include <complex>

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

static void BM_cmplx_abs(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::complex<float> z(state.range_x() / 100.0f, state.range_y() / 100.0f);
    if (std::abs(z) >= 2.0f) {
      setValue(state.range_x());
    }
  }
}

static void BM_cmplx_hypot(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::complex<float> z(state.range_x() / 100.0f, state.range_y() / 100.0f);
    if (std::hypot(z.real(), z.imag()) >= 2.0f) {
      setValue(state.range_x());
    }
  }
}

static void BM_cmplx_sqrt(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::complex<float> z(state.range_x() / 100.0f, state.range_y() / 100.0f);
    if (std::sqrt(z.real()*z.real() + z.imag()*z.imag()) >= 2.0f) {
      setValue(state.range_x());
    }
  }
}


static void BM_cmplx_square(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::complex<float> z(state.range_x() / 100.0f, state.range_y() / 100.0f);
    if ((z.real()*z.real() + z.imag()*z.imag()) >= 4.0f) {
      setValue(state.range_x());
    }
  }
}

static void BM_cmplx_empty(benchmark::State& state) {
  while (state.KeepRunning()) {
    std::complex<float> z(state.range_x() / 100.0f, state.range_y() / 100.0f);
    if (z.real() + z.imag() > 0.f) {
      setValue(state.range_x());
    }
  }
}

///////////////////////////////////////////////////////////////////////////////
// float

static void BM_float_hypot(benchmark::State& state) {
  while (state.KeepRunning()) {
    float re = state.range_x() / 100.0f;
    float im = state.range_y() / 100.0f;

    if (std::hypot(re,im) >= 2.0f) {
      setValue(state.range_x());
    }
  }
}

static void BM_float_sqrt(benchmark::State& state) {
  while (state.KeepRunning()) {
    float re = state.range_x() / 100.0f;
    float im = state.range_y() / 100.0f;

    if (std::sqrt(re*re + im*im) >= 2.0f) {
      setValue(state.range_x());
    }
  }
}


static void BM_float_square(benchmark::State& state) {
  while (state.KeepRunning()) {
    float re = state.range_x() / 100.0f;
    float im = state.range_y() / 100.0f;

    if ((re*re + im*im) >= 4.0f) {
      setValue(state.range_x());
    }
  }
}

static void BM_float_empty(benchmark::State& state) {
  while (state.KeepRunning()) {
    float re = state.range_x() / 100.0f;
    float im = state.range_y() / 100.0f;

    if (re + im > 0.f) {
      setValue(state.range_x());
    }
  }
}

BENCHMARK(BM_cmplx_abs)->ArgPair(100, 200);
BENCHMARK(BM_cmplx_hypot)->ArgPair(100, 200);
BENCHMARK(BM_cmplx_sqrt)->ArgPair(100, 200);
BENCHMARK(BM_cmplx_square)->ArgPair(100, 200);
BENCHMARK(BM_cmplx_empty)->ArgPair(100, 200);

BENCHMARK(BM_float_hypot)->ArgPair(100, 200);
BENCHMARK(BM_float_sqrt)->ArgPair(100, 200);
BENCHMARK(BM_float_square)->ArgPair(100, 200);
BENCHMARK(BM_float_empty)->ArgPair(100, 200);

BENCHMARK_MAIN()
