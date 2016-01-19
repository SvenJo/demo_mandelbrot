#pragma once

// from gcc man page: https://gcc.gnu.org/onlinedocs/libstdc++/manual/using_exceptions.html
// TODO: move to other header

#if defined(_MSC_VER)
# define __cpp_exceptions 1
#endif

#if __cpp_exceptions
# define TRY_      try
# define CATCH_(X) catch(X)
# define throw_exception_again throw
#else
# define TRY_      if (true)
# define CATCH_(X) if (false)
# define throw_exception_again
#endif


namespace easy
{
  struct ViewInfo
  {    
    // logical view size
    int width() const { return width_; }
    int height() const { return height_; }

    // window size
    int windowWidth() const { return windowWidth_; }
    int windowHeight() const { return windowHeight_; }

    int offSetX() const { return (windowWidth_ - width_) / 2; }
    int offSetY() const { return (windowHeight_ - height_) / 2; }

    // zoom info
    double x1() const { return x1_; }
    double x2() const { return x2_; }
    double y1() const { return y1_; }
    double y2() const { return y2_; }

    double dx() const { return dx_; }
    double dy() const { return dy_; }

    void resize(int w, int h, double ratio = 0.7)
    {
      ratio_ = ratio;
      windowWidth_ = w;
      windowHeight_ = h;

      if (double(h) / double(w) > ratio_) {
        width_ = w;
        height_ = int(w * ratio_);
      }
      else {
        width_ = int(h / ratio_);
        height_ = h;
      }

      dx_ = static_cast<double>((x2() - x1()) / width());
      dy_ = static_cast<double>((y2() - y1()) / height());
    }

    void setZoom(double dx1, double dx2, double dy1, double dy2)
    {
      x1_ = std::max(dx1, -3.0);
      x2_ = std::min(dx2, 3.0);
      y1_ = std::max(dy1, -3.0);
      y2_ = std::min(dy2, 3.0);

      dx_ = static_cast<double>((x2() - x1()) / width());
      dy_ = static_cast<double>((y2() - y1()) / height());
    }

    void reset()
    {
      ViewInfo view;                // default values
      view.resize(windowWidth_, windowHeight_); // restore size
      std::swap(view, *this);       // use defaults
    }

    double diffx() const
    {
      return x2_ - x1_;
    }
    double diffy() const
    {
      return y2_ - y1_;
    }

    // pixel to real coordinates
    double x(int dx) const
    {
      return x1_ + dx * diffx() / width_;
    }

    // pixel to real coordinates
    double y(int dy)
    {
      return y1_ + dy * diffy() / height_;
    }

    void pixelMove(int dx, int dy)
    {
      move(dx * (diffx() / width_), dy *(diffy() / height_));
    }

    void move(double dx, double dy)
    {
      const auto xx1 = x1() + dx;
      const auto xx2 = x2() + dx;
      const auto yy1 = y1() + dy;
      const auto yy2 = y2() + dy;

      if(xx1 >= -3.0 && xx2 <= 3.0 && yy1 >= -3.0 && yy2 <= 3.0)
        setZoom(xx1, xx2, yy1, yy2);
    }

    void zoomIn(double zoomFactor)
    {
      const auto dx = diffx();
      const auto dy = diffy();

      const auto dxdiff = dx * (1.0 - 2 * zoomFactor);
      const auto dydiff = dy * (1.0 - 2 * zoomFactor);

      const auto xx1 = x1_ + (dx - dxdiff) / 2.;
      const auto xx2 = x2_ - (dx - dxdiff) / 2.;
      const auto yy1 = y1_ + (dy - dydiff) / 2.;
      const auto yy2 = y2_ - (dy - dydiff) / 2.;
      
      if(xx1 >= -3.0 && xx2 <= 3.0 && yy1 >= -3.0 && yy2 <= 3.0)
        setZoom(xx1, xx2, yy1, yy2);
    }

    // window size
    int width_ = 100;
    int height_ = 100;

    // window size
    int windowWidth_ = 100;
    int windowHeight_ = 100;

    double dx_ = 0.0;
    double dy_ = 0.0;
    double ratio_ = 0.7;

    // zoom info
    double x1_ = -2;
    double x2_ = 0.55;
    double y1_ = -1.15; //-0.95;
    double y2_ = 1.15; //0.95;
  };
}
