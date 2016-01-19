#pragma once


#ifndef _MSC_VER
namespace std {

  // missing make_unique for GCC (or enable C++14)
  template<typename T, typename... Args>
  std::unique_ptr<T> make_unique(Args&&... args) {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
}
#endif
