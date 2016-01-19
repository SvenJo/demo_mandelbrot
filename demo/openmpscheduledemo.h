#pragma once

#include <map>
#include <thread>
#include <mutex>
#include <algorithm>

/*
In arbeit
*/

namespace openmp_schedule_demo
{
  using namespace std;

  static const int max_loop = 10000000;

  struct info
  {
    decltype(this_thread::get_id()) id = {};
    int minval = max_loop;
    int maxval = 0;
    int long long sum = 0;
  };
  
  using cacheType = map<thread::id, info>; 

  void test()
  {
    mutex g_cache_mutex;

#ifdef OPENMP_FOUND

    cout << "OpenMP" << endl;
    cacheType openMPcache;

//#pragma omp parallel for
#pragma omp parallel for // schedule(dynamic)
    for (int i = 0; i < max_loop; ++i) {
        lock_guard<mutex> lock(g_cache_mutex);
        auto& info = openMPcache[this_thread::get_id()];
        info.id = this_thread::get_id();
        info.minval = min(info.minval, i);
        info.maxval = max(info.maxval, i);
        info.sum += i;
    }

    vector<info> openMPinfos;
    transform(openMPcache.begin(), openMPcache.end(), back_inserter(openMPinfos), [](const cacheType::value_type& p) { return p.second; });
    sort(openMPinfos.begin(), openMPinfos.end(), [](const info& l, const info& r) { return l.minval < r.minval; });

    for (auto p : openMPinfos) {      
      cout << "{" << endl;
      //cout << "OpenMP Id  = " << p.id << endl;
      cout << "  OpenMP min = " << p.minval << endl;
      cout << "  OpenMP max = " << p.maxval << endl;
      cout << "}" << endl;
    }
#endif

#ifdef TBB_FOUND
    cout << "tbb::parallel_for" << endl;
    cacheType TBBcache;

    tbb::parallel_for(int(0), int(max_loop), [&TBBcache, &g_cache_mutex] (int i){
        lock_guard<mutex> lock(g_cache_mutex);
        auto& info = TBBcache[this_thread::get_id()];
        info.id = this_thread::get_id();
        info.minval = min(info.minval, i);
        info.maxval = max(info.maxval, i);
        info.sum += i;
    });

    vector<info> TBBinfos;
    transform(TBBcache.begin(), TBBcache.end(), back_inserter(TBBinfos), [](const cacheType::value_type& p) { return p.second; });
    sort(TBBinfos.begin(), TBBinfos.end(), [](const info& l, const info& r) { return l.minval < r.minval; });

    for (auto p : TBBinfos) {
      cout << "{" << endl;
      //cout << "TBB Id  = " << p.id << endl;
      cout << "  TBB min = " << p.minval << endl;
      cout << "  TBB max = " << p.maxval << endl;
      cout << "}" << endl;
    }
#endif // TBB_FOUND

  }
}
