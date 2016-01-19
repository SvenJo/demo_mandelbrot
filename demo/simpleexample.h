#pragma once

#include <complex>

namespace simple_example {

  inline char transform(int iter)
  {
    if (iter < 10) return ' ';
    if (iter < 20) return '.';
    if (iter < 30) return 'o';
    if (iter < 50) return '*';
    if (iter < 70) return 'x';
    if (iter < 90) return 'X';
    return '@';
  }

  inline int pixel(double re, double im)
  {
    const std::complex<double> c{ re, im };
    std::complex<double> z{ 0. };
    int iter{ 0 };
    while ((iter < 100) && (std::abs(z) < 2.0)) {
      z = z * z + c;
      ++iter;
    }
    return iter;
  }

  inline void demo()
  {
    using namespace std;

    cout << "Mandelbrot demo:\n";

    const auto start = std::chrono::high_resolution_clock::now();

    const int disp_width = 160;
    const int disp_height = 80;

    const double scale_real = 3.0 / disp_width;
    const double scale_imag = 3.0 / disp_height;

    for (int j = 1; j < disp_height; ++j) {
      for (int i = 1; i < disp_width; ++i) {
        const double re = (i * scale_real) - 1.8;
        const double im = (j * scale_imag) - 1.5;
        const int iter = pixel(re, im);
        cout << transform(iter);
      }
      cout << '\n';
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto time_in_ms = std::chrono::duration <double, std::milli>(end - start).count();
    
    cout << "Dauer: " << time_in_ms << "ms; " << double(disp_width*disp_height)/(time_in_ms*1000.0) << "MPixel/s"  << endl;
  }

  inline void demo_perf()
  {
    using namespace std;

    cout << "Mandelbrot demo: (performance only)\n";

    const auto start = std::chrono::high_resolution_clock::now();

    const int disp_width = 17900;
    const int disp_height = 800;

    const double scale_real = 3.0 / disp_width;
    const double scale_imag = 3.0 / disp_height;
    
    volatile int dont_opt_to_much = 0;

    for (int j = 1; j < disp_height; ++j) {
      for (int i = 1; i < disp_width; ++i) {
        const double x = (i * scale_real) - 1.8;
        const double y = (j * scale_imag) - 1.5;

        double u = 0.0, v = 0.0, u2 = 0.0, v2 = 0.0;
        int iter = 0;

        while ((u2 + v2 < 4.0) && (iter < 100)) {
          v = 2 * v * u + y;
          u = u2 - v2 + x;
          u2 = u * u;
          v2 = v * v;
          ++iter;
        }
        dont_opt_to_much += iter;
        //char c = transform(iter);
        //cout << c;
      }
      //cout << '\n';
    }

    const auto end = std::chrono::high_resolution_clock::now();
    const auto time_in_ms = std::chrono::duration <double, std::milli>(end - start).count();
    
    cout << "Dauer: " << time_in_ms << "ms; " << double(disp_width*disp_height)/(time_in_ms*1000.0) << "MPixel/s"  << endl;
  }

}
