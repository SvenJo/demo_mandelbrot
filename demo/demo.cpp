#include "stdafx.h"

#include "simpleexample.h"
#include "doloopdemo.h"
#include "floatinitdemo.h"
#include "paralleldemo.h"
#include "perfdemo.h"
#include "recursion.h"
#include "simddemo.h"
#include "transformdemo.h"
#include "unrolldemo.h"
#include "warmupdemo.h"

// Only for debug purposes
#include "openmpscheduledemo.h"
#include "printiterations.h"
#include "stepdemo.h"
#include "test.h"


void demo()
{
  simple_example::demo();
  //simple_example::demo_perf();
  //perf_demo::test();
  //parallel_demo::test();
  //simd_demo::test();

  //do_while_compare::test_default();
  //do_while_compare::test_2();
  //do_while_compare::test_100();
  //unroll::demo();
  //floatinit_demo::test();
  //perf_demo::test_int();
  //perf_demo::test_complex();
  //recursion_demo::test();
  //transform_demo::test();
  //warmup::demo();

  // Only for debug purposes
  //openmp_schedule_demo::test();
  //print_iterations::tester();
  //stepdemo::test();
  //test::test();
}

void demo_perf()
{
  simple_example::demo_perf();
  perf_demo::test();
  parallel_demo::test();
  simd_demo::test();
}

void demo_all()
{
  simple_example::demo_perf();
  perf_demo::test();
  parallel_demo::test();
  simd_demo::test();

  do_while_compare::test_default();
  do_while_compare::test_2();
  do_while_compare::test_100();
  
  unroll::demo();
  floatinit_demo::test();
  perf_demo::test_int();
  perf_demo::test_complex();
  recursion_demo::test();
  transform_demo::test();
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
    ("plain,p", "output as plain text (default)")
    ("suppressheaders,s", "suppress headers (plain)")
    ("none,n", "no output")
    ("all,a", "all performance tests")
    ("default,d", "default performance tests")
    ("test,t", "testing and debugging tests")
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

  if (vm.count("suppressheaders"))
    PerfTest::SuppressHeaders() = true;

  bool runDebugTests = true;
  
  if (vm.count("all")) {
    demo_all();
    runDebugTests = false;
  }
  
  if (vm.count("default")) {
    demo_perf();
    runDebugTests = false;
  }
  
  if (runDebugTests || vm.count("test")) {
    demo();
  }
#else
  // without boost
  demo();
#endif

}
