#pragma once

namespace mandel {

  template<typename FLOAT_TYPE>
  struct Complex {

    typedef FLOAT_TYPE value_type;

    FLOAT_TYPE re_;
    FLOAT_TYPE im_;

    FLOAT_TYPE real() const { return re_; }
    FLOAT_TYPE imag() const { return im_; }
  };

  template<typename FLOAT_TYPE>
  inline Complex<FLOAT_TYPE> operator+(const Complex<FLOAT_TYPE>& left, const Complex<FLOAT_TYPE>& right)
  {
    return Complex<FLOAT_TYPE>{left.re_ + right.re_, left.im_ + right.im_ };
  }

  template<typename FLOAT_TYPE>
  inline Complex<FLOAT_TYPE> operator*(const Complex<FLOAT_TYPE>& left, const Complex<FLOAT_TYPE>& right)
  {
    return Complex<FLOAT_TYPE>{ left.re_ * right.re_ - left.im_ * right.im_, 
                                left.re_ * right.im_ + left.im_ * right.re_ };
  }

  template<typename FLOAT_TYPE>
  bool operator!=(const Complex<FLOAT_TYPE>& left, const Complex<FLOAT_TYPE>& right) { return left.re_ != right.re_ || left.im_ != right.im_; }
  
  template<typename T>
  inline T abs(const Complex<T>& z)
  {
    return sqrt(z.re_*z.re_ + z.im_*z.im_);
  }

}
