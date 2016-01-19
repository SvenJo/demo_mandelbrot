#pragma once

namespace easy
{
  template<typename RES_TYPE>
  struct Picture
  {
    Picture(int x, int y)
      : width_(x)
      , height_(y)
      , data_(size_t(x*y))
    {}

    void resize(int w, int h)
    {
      width_ = w;
      height_ = h;
      data_.resize(size_t(w*h));
    }

    int width()  const { return width_; }
    int height() const { return height_; }

    const std::vector<RES_TYPE>& data() const { return data_; }
    std::vector<RES_TYPE>& data() { return data_; }

    const RES_TYPE* raw() const
    {
      return data_.data();
    }

    size_t size() const { return data_.size(); }
  private:
    // memory (in the most case the same as width and height)
    int width_;
    int height_;
    std::vector<RES_TYPE> data_;
  };

}
