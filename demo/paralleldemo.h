#pragma once

#include <perf_tester.h>
#include <mandel/sequentiell.h>

#include <mandel/pixel.h>
#include <mandel/openmp.h>
#include <mandel/tbb.h>
#include <mandel/future.h>

namespace parallel_demo {

  inline void test()
  {
    using namespace mandel;

    //omp_set_num_threads(4);

    PerfTest perfTest("Performance Demo (parallel OpenMP vs. TBB vs. std::future)", true, true);

    perfTest.test<CalcSequentiell<float,  int, mandel::Pixel<float>>>("Sequential (float) ");
    perfTest.test<CalcSequentiell<double, int, mandel::Pixel<double>>>("Sequential (double)");

#ifdef OPENMP_FOUND
    perfTest.test<CalcOpenMP<float, int, mandel::Pixel<float>>>("OpenMP (float) ");
    perfTest.test<CalcOpenMP<double, int, mandel::Pixel<double>>>("OpenMP (double)");
#endif

#ifdef TBB_FOUND
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("TBB (float) ");
    perfTest.test<CalcTBB<double, int, mandel::Pixel<double>>>("TBB (double)");
#endif

    //perfTest.test<CalcSimpleFutures<float, int, mandel::Pixel<float>>>("Simple future (float) ");
    //perfTest.test<CalcSimpleFutures<double, int, mandel::Pixel<double>>>("Simple future (double)");
  }

}
