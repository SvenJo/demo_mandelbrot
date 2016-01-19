#pragma once

//TODO: reword HRESULT hr handling!

#include "mfc_pixel_render_engine.h"

#include <d2d1.h>
#include <atlbase.h>

struct Direct2DRenderEngine : MFCPixelRenderEngine
{
  Direct2DRenderEngine()
  {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory_);
    if (!SUCCEEDED(hr)) pD2DFactory_ = nullptr;
  }

  void init(CWnd* pWnd) override
  {
    /*HRESULT hr = */ pD2DFactory_->CreateHwndRenderTarget(
      D2D1::RenderTargetProperties(),
      D2D1::HwndRenderTargetProperties(
      pWnd->GetSafeHwnd(),
      D2D1::SizeU(100, 100)
      ), &m_pRenderTarget);
  }

  virtual void resize(const easy::ViewInfo& viewInfo) override
  {
    if (m_pRenderTarget) {
      m_pRenderTarget->Resize(D2D1::SizeU(viewInfo.windowWidth(), viewInfo.windowHeight()));

      D2D1_PIXEL_FORMAT pixelFormat = D2D1::PixelFormat(
        DXGI_FORMAT_R8G8B8A8_UNORM,
        D2D1_ALPHA_MODE_IGNORE
        );
      D2D1_BITMAP_PROPERTIES bitmapProperties;
      bitmapProperties.pixelFormat = pixelFormat;
      m_pRenderTarget->GetDpi(&bitmapProperties.dpiX, &bitmapProperties.dpiY);
      m_pBitmap = nullptr;
      m_pRenderTarget->CreateBitmap(D2D1::SizeU(viewInfo.width(), viewInfo.height()), bitmapProperties, &m_pBitmap);
    }
  }

  virtual void paint(const easy::ViewInfo& viewInfo, const easy::Picture<result_t>& picture) override
  {
    assert(m_pRenderTarget);
    assert(m_pBitmap);

    m_pRenderTarget->BeginDraw();
    /*HRESULT hr = */ m_pBitmap->CopyFromMemory(NULL, (BYTE*)picture.raw(), 4 * viewInfo.width());
    m_pRenderTarget->DrawBitmap(m_pBitmap, D2D1::RectF(
      FLOAT(viewInfo.offSetX()),
      FLOAT(viewInfo.offSetY()),
      FLOAT(viewInfo.width() + viewInfo.offSetX()),
      FLOAT(viewInfo.height() + viewInfo.offSetY())));
    m_pRenderTarget->EndDraw();
  }

private:
  CComPtr<ID2D1Factory> pD2DFactory_;
  CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
  CComPtr<ID2D1Bitmap> m_pBitmap;
};
