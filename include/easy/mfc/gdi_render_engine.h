#pragma once

#include "mfc_pixel_render_engine.h"

struct GDIRenderEngine : MFCPixelRenderEngine
{
  virtual void init(CWnd* pWnd) override
  {
    m_pDC = std::make_unique<CClientDC>(pWnd);
  }

  virtual void resize(const easy::ViewInfo&) override
  {
  }

  virtual void paint(const easy::ViewInfo& viewInfo, const easy::Picture<result_t>& picture) override
  {
    m_pDC->SetViewportOrg(CPoint{ 0, 0 });
    m_pDC->FillSolidRect(CRect{0, 0, viewInfo.windowWidth(), viewInfo.windowHeight()}, 0);
    m_pDC->SetViewportOrg(CPoint{ viewInfo.offSetX(), viewInfo.offSetY()});

    CMemDC memDC(*m_pDC, CRect{ 0, 0, viewInfo.width(), viewInfo.height()});

    CBitmap dispBMP;
    dispBMP.CreateCompatibleBitmap(m_pDC.get(), viewInfo.width(), viewInfo.height());
    memDC.GetDC().SelectObject(&dispBMP);

    BITMAPINFO info = { 0 };
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biSizeImage = DWORD(picture.size() * sizeof(COLORREF));
    info.bmiHeader.biWidth = viewInfo.width();
    info.bmiHeader.biHeight = -viewInfo.height();
    info.bmiHeader.biClrUsed = 0;

    //int r = 
    SetDIBits(memDC.GetDC(), dispBMP, 0, viewInfo.height(), picture.raw(), &info, DIB_RGB_COLORS);
  }

private:
  std::unique_ptr<CClientDC> m_pDC;
};
