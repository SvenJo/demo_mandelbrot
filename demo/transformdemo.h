#pragma once

#include <perf_tester.h>
#include <mandel/pixel.h>
#include <mandel/sequentiell.h>

namespace transform_demo
{

  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct ComplexRange1
  {
    struct ComplexIterator
    {
      typedef std::forward_iterator_tag iterator_category;
      typedef typename COMPLEX_TYPE value_type;
      typedef void difference_type;
      typedef typename COMPLEX_TYPE* pointer;
      typedef typename COMPLEX_TYPE& reference;

      COMPLEX_TYPE operator*() { return val_; }
      void operator++() { val_ = parent_.next(val_); }
      bool operator!=(const ComplexIterator& other) { return other.val_ != val_; }

      COMPLEX_TYPE val_;
      const ComplexRange1& parent_;
    };


    ComplexRange1(FLOAT_TYPE re_from, FLOAT_TYPE re_to, FLOAT_TYPE im_from, FLOAT_TYPE im_to, std::size_t re_num_steps, std::size_t im_num_steps)
      : from_({ std::min(re_from, re_to), std::min(im_from, im_to) })
      , to_({ std::max(re_from, re_to), std::max(im_from, im_to) })
      , re_step_((to_.real() - from_.real()) / (re_num_steps - 1))
      , im_step_((to_.imag() - from_.imag()) / (im_num_steps - 1))
      , end_(incr(to_))
    {
    }

    ComplexIterator begin() const
    {
      return ComplexIterator{ from_, *this };
    }

    ComplexIterator end() const
    {
      return ComplexIterator{ end_, *this };
    }

  private:
    COMPLEX_TYPE incr(COMPLEX_TYPE val) const
    {
      auto n = COMPLEX_TYPE{ val.real() + re_step_, val.imag() };
      if (n.real() > to_.real())
        n = COMPLEX_TYPE{ from_.real(), val.imag() + im_step_ };
      return n;
    }

    COMPLEX_TYPE next(COMPLEX_TYPE val) const
    {
      auto n = incr(val);
      if (n.imag() > to_.imag())
        n = end_;
      return n;
    }

  private:
    const COMPLEX_TYPE from_; // first value
    const COMPLEX_TYPE to_; // last value
    const FLOAT_TYPE re_step_; // dx: step width in real direction
    const FLOAT_TYPE im_step_; // dy: step width in imag direction
    const COMPLEX_TYPE end_; // one behind the last value (to_)

    friend ComplexIterator;
  };


  template<typename COMPLEX_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type>
  struct ComplexRange2
  {
    struct ComplexIterator
    {
      typedef std::forward_iterator_tag iterator_category;
      typedef typename COMPLEX_TYPE value_type;
      typedef void difference_type;
      typedef typename COMPLEX_TYPE* pointer;
      typedef typename COMPLEX_TYPE& reference;

      COMPLEX_TYPE operator*() { return parent_.val(re_index_, im_index_); }

      void operator++() { 
        ++re_index_; 
        if (re_index_ >= parent_.re_num_steps_) {
          re_index_ = 0;
          ++im_index_;
          if (im_index_ >= parent_.im_num_steps_) {
            re_index_ = size_t(-1);
            im_index_ = size_t(-1);
          }
        }
      }

      bool operator!=(const ComplexIterator& other)
      {
        return other.re_index_ != re_index_ || other.im_index_ != im_index_;
      }

      size_t re_index_;
      size_t im_index_;
      const ComplexRange2& parent_;
    };


    ComplexRange2(FLOAT_TYPE re_from, FLOAT_TYPE re_to, FLOAT_TYPE im_from, FLOAT_TYPE im_to, std::size_t re_num_steps, std::size_t im_num_steps)
      : from_({ std::min(re_from, re_to), std::min(im_from, im_to) })
      , re_num_steps_(re_num_steps)
      , im_num_steps_(im_num_steps)
      , re_step_((re_to - re_from) / (re_num_steps - 1))
      , im_step_((im_to - im_from) / (im_num_steps - 1))
    {
    }

    ComplexIterator begin() const
    {
      return ComplexIterator{ 0, 0, *this };
    }

    ComplexIterator end() const
    {
      return ComplexIterator{ size_t(-1), size_t(-1), *this };
    }

  private:
    COMPLEX_TYPE val(size_t re_index, size_t im_index) const
    {
      return COMPLEX_TYPE{ from_.real() + re_step_ * re_index, from_.imag() + im_step_ * im_index };
    }

  private:
    const COMPLEX_TYPE from_;
    const std::size_t re_num_steps_;
    const std::size_t im_num_steps_;
    const FLOAT_TYPE re_step_;
    const FLOAT_TYPE im_step_;

    friend ComplexIterator;
  };


  template<typename COMPLEX_TYPE, typename RESULT_TYPE, typename PIXEL_TYPE, typename COMPLEXRANGE_TYPE, typename FLOAT_TYPE = typename COMPLEX_TYPE::value_type, typename TRANSFORM_TYPE = null_transform<RESULT_TYPE>>
  struct CalcComplexRange
  {
    void operator() (const easy::ViewInfo& view, easy::Picture<RESULT_TYPE>& picture) const
    {
      assert(picture.width() * picture.height() <= (int)picture.size());
      assert(0 < view.width() && 0 < view.height());
      assert(view.x1() < view.x2());
      assert(view.y1() < view.y2());

      doIt(view.width(), view.height(), view.x1(), view.y1(), view.x2(), view.y2(), picture.data());
    }
  private:
    void doIt(const int width, const int height, const double dX1, const double dY1, const double dX2, const double dY2, std::vector<RESULT_TYPE> &picture) const
    {
      TRANSFORM_TYPE t;
      PIXEL_TYPE pixel;

      const auto x1 = static_cast<FLOAT_TYPE>(dX1);
      const auto y1 = static_cast<FLOAT_TYPE>(dY1);
      const auto x2 = static_cast<FLOAT_TYPE>(dX2);
      const auto y2 = static_cast<FLOAT_TYPE>(dY2);

      COMPLEXRANGE_TYPE range(x1, x2, y1, y2, width, height);

      std::transform(std::begin(range), std::end(range), std::begin(picture), [&pixel, &t](COMPLEX_TYPE val) {
        const auto iter = pixel(val.real(), val.imag());
        return t(iter);
      });
    }

  };

  void test()
  {

    using namespace mandel;

    /*
    ComplexRange2<std::complex<double>> range{ -1.0, 1.0, -2.0, 2.0, 3, 5 };
    for (const auto v : range) {
      std::cout << v << " ";
    }
    std::cout << std::endl;
    /*/

    PerfTest perfTest("Performance Demo (different float types)");

    perfTest.test<CalcSequentiell<float, int, PixelComplex<Complex<float>>>>("mandel::Complex float");
    perfTest.test<CalcSequentiell<double, int, PixelComplex<Complex<double>>>>("mandel::Complex double");

    perfTest.test<CalcComplexRange<Complex<float>,int,PixelComplex<Complex<float>>,ComplexRange1<Complex<float>>>>("mandel::Complex float ComplexRange (add)");
    perfTest.test<CalcComplexRange<Complex<double>, int, PixelComplex<Complex<double>>, ComplexRange1<Complex<double>>>>("mandel::Complex double ComplexRange (add)");

    perfTest.test<CalcComplexRange<Complex<float>, int, PixelComplex<Complex<float>>, ComplexRange2<Complex<float>>>>("mandel::Complex float ComplexRange (index)");
    perfTest.test<CalcComplexRange<Complex<double>, int, PixelComplex<Complex<double>>, ComplexRange2<Complex<double>>>>("mandel::Complex double ComplexRange (index)");
    //*/
  }

}
