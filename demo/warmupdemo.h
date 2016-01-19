#pragma once

#include <perf_tester.h>
#include <mandel/pixel.h>
#include <mandel/sequentiell.h>
#include <mandel/openmp.h>
#include <mandel/tbb.h>

// enable both to run 100 times!
#define NUMBER_OF_RUNS_50
#define NUMBER_OF_RUNS_100

namespace warmup
{
  using namespace std;
  using namespace mandel;

  void demo()
  {
    PerfTest perfTest("Warmup Demo", false, false, true);

    //*
#ifdef OPENMP_FOUND
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");

#ifdef NUMBER_OF_RUNS_50
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");

#ifdef NUMBER_OF_RUNS_100
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
    perfTest.test<CalcOpenMP<     float, int>>("warm up (OpenMP)");
#endif // NUMBER_OF_RUNS_50
#endif // NUMBER_OF_RUNS_100

#endif // OPENMP_FOUND

    //*/
#ifdef TBB_FOUND
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");

    #ifdef NUMBER_OF_RUNS_50
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");

    #ifdef NUMBER_OF_RUNS_100
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
    perfTest.test<CalcTBB<float, int, mandel::Pixel<float>>>("warm up (TBB)");
#endif // NUMBER_OF_RUNS_50
#endif // NUMBER_OF_RUNS_100
#endif // TBB_FOUND
    //*/  
  }

}
