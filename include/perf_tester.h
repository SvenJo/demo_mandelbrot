#pragma once

// already included in extern.h
// #include <chrono>
// #include <iostream>
// #include <string>
// #include <cassert>
// #include <iomanip>

#include <easy/viewinfo.h>
#include <easy/picture.h>

// for warmup
#include <mandel/pixel.h>
#include <mandel/openmp.h>
#include <mandel/tbb.h>

struct PerfTest {

  enum class ReportMode { NONE, CSV, TEXT };
  
  static bool& WarmUpOpenMPdone()
  {
    static bool bWarmUpDone = false;
    return bWarmUpDone;
  }

  static bool& WarmUpTBBdone()
  {
    static bool bWarmUpDone = false;
    return bWarmUpDone;
  }

  static bool& WarmUpCPUdone()
  {
    static bool bWarmUpDone = false;
    return bWarmUpDone;
  }

  static bool& SuppressHeaders()
  {
    static bool bSuppressHeaders = false;
    return bSuppressHeaders;
  }

  static ReportMode& DefaultReportMode()
  {
    static ReportMode defaultReportMode = ReportMode::TEXT;
    return defaultReportMode;
  }

  PerfTest() = default;

  PerfTest(const std::string& name, bool doOpenMPWarmUp = false, bool doTBBWarmUp = false, bool dontWarmUp = false)
    : reportMode(DefaultReportMode())
  {
    writeHeader(name);

    if (dontWarmUp) 
      return;

    if (doOpenMPWarmUp && !WarmUpOpenMPdone())
      warmupOpenMP();

    if (doTBBWarmUp && !WarmUpTBBdone())
      warmupTBB();

    if (!WarmUpCPUdone()) 
      warmupCPU();
  }

  static void warmupOpenMP()
  {   
#ifdef OPENMP_FOUND
    PerfTest perfTest;
    using namespace mandel;
    perfTest.test<CalcOpenMP<     float, int>>("warm up");
    perfTest.test<CalcOpenMP<     float, int>>("warm up");
    perfTest.test<CalcOpenMP<     float, int>>("warm up");

    WarmUpOpenMPdone() = true;
    WarmUpCPUdone() = true;
#endif
  }

  static void warmupTBB()
  {
#ifdef TBB_FOUND
    PerfTest perfTest;
    using namespace mandel;
    perfTest.test<CalcTBB<     float, int>>("warm up");
    perfTest.test<CalcTBB<     float, int>>("warm up");
    perfTest.test<CalcTBB<     float, int>>("warm up");

    WarmUpTBBdone() = true;
    WarmUpCPUdone() = true;
#endif
  }

  static void warmupCPU()
  {
    warmupOpenMP();
  }


  void writeHeader(const std::string& name)
  {
    using namespace std;

    if (SuppressHeaders()) 
      return;

    switch (reportMode) {
    case PerfTest::ReportMode::NONE:
      break;
    case PerfTest::ReportMode::CSV:
      // no title
      cout << "name;Pixel per Minutes\n";
      break;
    case PerfTest::ReportMode::TEXT:
      cout << "Perf. test: " << name << endl;
      cout << "iter.\t duration [ms]\t [pixel/s]\t name" << endl;
      break;
    default:
      assert(!"unexpected enum! fixme");
    }
  }

  void reportTest(const std::string& name, size_t iterations, double time, double pixel_per_sec) const
  {
    using namespace std;
    
    switch (reportMode) {
    case PerfTest::ReportMode::NONE:
      break;
    case PerfTest::ReportMode::CSV:
      cout << std::fixed << std::setprecision(4);
      cout << name << ';' << pixel_per_sec << "\n";
      break;
    case PerfTest::ReportMode::TEXT:
      cout << std::fixed << std::setprecision(4);
      cout << iterations << ",\t " << time << ",\t " << pixel_per_sec << ",\t " << name << endl;
      break;
    default:
      assert(!"unexpected enum! fixme");
    }
    
  }

  template<typename CALC_MANDELBROT_TYPE>
  void test(const std::string& test_name, double x1 = -1.8, double x2 = 1.2, double y1 = -1.5, double y2 = 1.5)
  {
#ifdef __ANDROID__
    const int xsize = 200;
    const int ysize = 200;
#else
    const int xsize = 1000;
    const int ysize = 1000;
#endif
    std::chrono::high_resolution_clock::duration times(0);

    TRY_
    {
      easy::ViewInfo view;
      view.resize(xsize, ysize, 1.0);
      view.setZoom(x1, x2, y1, y2);

      easy::Picture<int> picture(xsize, ysize);

      int iterations = 0;
      for (; iterations < 100; ++iterations) {
        const auto start = std::chrono::high_resolution_clock::now();
        CALC_MANDELBROT_TYPE()(view, picture);
        const auto end = std::chrono::high_resolution_clock::now();

        const auto single_shot = end - start;
        times += single_shot;

        if (times > std::chrono::seconds{ 1 }) {
            ++iterations;
            break;
        }
      }

      const double time_in_ms = std::chrono::duration <double, std::milli>(times).count();
      reportTest(test_name, iterations, time_in_ms, double(xsize*ysize*iterations) / (1000.0 * time_in_ms));
    }
    CATCH_(const std::exception& ex)
    {
#if __cpp_exceptions        
      std::cout << "stop: " << ex.what() << std::endl;
#endif        
      return;
    }
  }

  ReportMode reportMode = ReportMode::NONE;
};
