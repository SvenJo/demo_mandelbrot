#include <extern.h>
#include "stdafx.h"

#include "simpleexample.h"
#include "perfdemo.h"
#include "doloopdemo.h"
#include "unrolldemo.h"
#include "warmupdemo.h"
#include "paralleldemo.h"

#ifdef VECTORCLASS_FOUND
#include "simddemo.h"
#endif

#include "printiterations.h"
#include "floatinitdemo.h"
#include "stepdemo.h"
#include "openmpscheduledemo.h"

#include "test.h" // Only for debug purposes

void demo()
{
  //SimpleExample::demo();
  SimpleExample::demo_perf();
  PerfDemo::RunPerfTest();
  DoWhileCompare::RunPerfTestDefault();
  DoWhileCompare::RunPerfTest100();
  DoWhileCompare::RunPerfTest2();
  unroll::demo();
  parallel_demo::RunPerfTest();
  //simd_demo::RunPerfTest();
  floatinit_demo::RunPerfTes();
  
  //warmup::demo();

  // Only for debug purposes
  //openmp_schedule_demo::test();
  //printIterations::tester();
  //stepdemo::test();
  //test::test();
}


int main(int argc, char* argv[])
{
#if defined(BOOST_FOUND)

  using namespace std;
  namespace po = boost::program_options;

  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("help,h", "produce help message")
    ("csv,c",  "output in CSV format")
    ("text,t", "output as plain text (default)")
    ("suppressheaders,p", "suppress headers (plain)")
    ("none,n", "no output")
    ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);

  if (vm.count("help")) {
    cout << desc << "\n";
    return 1;
  }

  if (vm.count("csv"))
    PerfTest::DefaultReportMode() = PerfTest::ReportMode::CSV;

  if (vm.count("none"))
    PerfTest::DefaultReportMode() = PerfTest::ReportMode::NONE;

  /* default: is automatic set
  if (vm.count("test")) {
    cout << "don't report numbers" << "\n";
    PerfTest::DefaultReportMode() = PerfTest::ReportMode::NONE;
  }
  */

  if (vm.count("suppressheaders"))
    PerfTest::SuppressHeaders() = true;

#endif

  demo();
}
