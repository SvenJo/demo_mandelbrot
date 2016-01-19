#pragma once

#include "../../easy/pixel_render_engine.h"


struct MFCPixelRenderEngine : PixelRenderEngine
{
  virtual void init(CWnd* pWnd) = 0;
};
