#pragma once

/*
#include <cairo/cairo-win32.h>

#include "mfc_pixel_render_engine.h"

struct CairoRenderEngine : MFCPixelRenderEngine
{
  ~CairoRenderEngine()
  {
    cairo_destroy(m_cr);
    cairo_surface_destroy(m_surface);
  }

  virtual void init(CWnd* pWnd) override
  {
    m_pDC = std::make_unique<CClientDC>(pWnd);
    m_surface = cairo_win32_surface_create(m_pDC->GetSafeHdc());
    m_cr = cairo_create(m_surface);  // For drawing we need a cairo context.  
  }

  virtual void resize(const easy::ViewInfo&) override
  {
  }

  virtual void paint(const easy::ViewInfo& viewInfo, const easy::Picture<int>& picture) override
  {
    int stride = cairo_format_stride_for_width(CAIRO_FORMAT_RGB24, xsize);
    cairo_surface_t *imageSurface = cairo_image_surface_create_for_data((unsigned char*)picture.data(), CAIRO_FORMAT_RGB24, xsize, ysize, stride);
    cairo_set_source_surface(m_cr, imageSurface, 0, 0);
    cairo_paint(m_cr);
    cairo_show_page(m_cr);
    cairo_surface_destroy(imageSurface);

    HDC src = cairo_win32_surface_get_dc(m_surface);
    BitBlt(m_pDC->GetSafeHdc(), xoffset, yoffset, xsize, ysize, src, 0,0, SRCCOPY);
  }

private:
  std::unique_ptr<CClientDC> m_pDC;
  cairo_surface_t* m_surface = nullptr;
  cairo_t* m_cr = nullptr;
};

*/
