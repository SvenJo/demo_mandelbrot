#include <benchmark/benchmark.h>

#ifdef  _MSC_VER
#pragma warning(disable: 4244)
#endif

static void setValue(double d)
{
#ifdef _MSC_VER
  static volatile double valueG = 0;
  valueG = d;
#else
  asm volatile("" : "+rm" (d));
#endif
}

static void BM_index_calc(benchmark::State& state) {
  while (state.KeepRunning()) {
    int disp_width = state.range_x();
    int disp_height = state.range_y();

    const double scale_real = 3.0 / disp_width;
    const double scale_imag = 3.0 / disp_height;

    for (int j = 1; j < disp_height; ++j) {
      const double im = j * scale_imag - 1.5;
      for (int i = 1; i < disp_width; ++i) {
        const double re = i * scale_real - 1.8;
        const double tmp = re*im;
        setValue(tmp);
      }
    }
  }
}

static void BM_index_add(benchmark::State& state) {
  while (state.KeepRunning()) {
    int disp_width = state.range_x();
    int disp_height = state.range_y();

    const double scale_real = 3.0 / disp_width;
    const double scale_imag = 3.0 / disp_height;

    double im = -1.5;
    for (int j = 1; j < disp_height; ++j) {
      im += scale_imag;
      double re = -1.8;
      for (int i = 1; i < disp_width; ++i) {
        re += scale_real;
        const double tmp = re*im;
        setValue(tmp);
      }
    }
  }
}


BENCHMARK(BM_index_calc)->ArgPair(100, 100);
BENCHMARK(BM_index_add)->ArgPair(100, 100);

BENCHMARK_MAIN()
