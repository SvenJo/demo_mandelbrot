#pragma once

#include "mfc_pixel_render_engine.h"

struct NullRenderEngine : MFCPixelRenderEngine
{
  virtual void init(CWnd*) {}
  virtual void resize(const easy::ViewInfo&) override {
  }
  virtual void paint(const easy::ViewInfo&, const easy::Picture<result_t>&) override
  {
    // only calc and don't paint!
  }

};
