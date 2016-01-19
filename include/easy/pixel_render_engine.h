#pragma once

#include "picture.h"
#include "viewinfo.h"



struct PixelRenderEngine
{
  virtual ~PixelRenderEngine(){}

  virtual void resize(const easy::ViewInfo&) = 0;
  virtual void paint(const easy::ViewInfo&, const easy::Picture<result_t>& picture) = 0;
};
