#pragma once

namespace mandel
{
  using namespace easy;

  namespace unittest
  {
    inline void test_values_in_range(const std::vector<int>& picture) // and different from the init value!
    {
      for (const auto i : picture) {
        REQUIRE(i != -99);
        REQUIRE(i >= 1);
        REQUIRE(i <= 100); // maxiter == 100!
      }
    }

    template<typename PIXEL>
    void TestPixelConvergence(const PIXEL& f)
    {
      REQUIRE(100 == f(0., 0.));
      REQUIRE(100 == f(-1., 0.));
      REQUIRE(1 == f(-2., -2.));
      REQUIRE(1 == f(2., -2.));
      REQUIRE(1 == f(-2., 2.));
      REQUIRE(1 == f(2., 2.));
    }

  }
}

