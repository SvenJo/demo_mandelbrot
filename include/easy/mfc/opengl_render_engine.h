#pragma once

#include "mfc_pixel_render_engine.h"

#include <gl/gl.h>
#include <gl/glu.h>

struct OpenGLRenderEngine : MFCPixelRenderEngine
{
  std::unique_ptr<CClientDC> pDC_;
  CPalette* pOldPalette_ = nullptr;
  CPalette cPalette_;
  GLuint glTexture_=0;

  ~OpenGLRenderEngine()
  {
    HGLRC   hrc = ::wglGetCurrentContext();
    ::wglMakeCurrent(NULL, NULL);

    if (hrc)
      ::wglDeleteContext(hrc);

    if (pOldPalette_)
      pDC_->SelectPalette(pOldPalette_, FALSE);
  }

  void init(CWnd* pWnd) override
  {
    pDC_.reset(new CClientDC(pWnd));

     if (!bSetupPixelFormat())
       return;

    HGLRC hrc = wglCreateContext(pDC_->GetSafeHdc());
    wglMakeCurrent(pDC_->GetSafeHdc(), hrc);
  }

  virtual void resize(const easy::ViewInfo& viewInfo) override
  {
    glViewport(viewInfo.offSetX(), viewInfo.offSetY(), viewInfo.width(), viewInfo.height());
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, viewInfo.width(), 0, viewInfo.height());

    // delete old texture
    if (glTexture_) {
      glDeleteTextures(1, &glTexture_);
      glTexture_ = 0;
    }

    // generate new texture
    glGenTextures(1, &glTexture_);
    glBindTexture(GL_TEXTURE_2D, glTexture_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  }

  virtual void paint(const easy::ViewInfo& viewInfo, const easy::Picture<result_t>& picture) override
  {
    assert(pDC_);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, glTexture_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewInfo.width(), viewInfo.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, picture.raw());

    glBegin(GL_QUADS);
    glTexCoord2f(0.f, 1.f); glVertex2i(0,                0);
    glTexCoord2f(0.f, 0.f); glVertex2i(0,                viewInfo.height());
    glTexCoord2f(1.f, 0.f); glVertex2i(viewInfo.width(), viewInfo.height());
    glTexCoord2f(1.f, 1.f); glVertex2i(viewInfo.width(), 0);
    glEnd();

    SwapBuffers(wglGetCurrentDC());
  }

private:

  BOOL bSetupPixelFormat()
  {
    static PIXELFORMATDESCRIPTOR pfd =
    {
      sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
      1,                              // version number
      PFD_DRAW_TO_WINDOW |            // support window
      PFD_SUPPORT_OPENGL |          // support OpenGL
      PFD_DOUBLEBUFFER,             // double buffered
      PFD_TYPE_RGBA,                  // RGBA type
      24,                             // 24-bit color depth
      0, 0, 0, 0, 0, 0,               // color bits ignored
      0,                              // no alpha buffer
      0,                              // shift bit ignored
      0,                              // no accumulation buffer
      0, 0, 0, 0,                     // accum bits ignored
      32,                             // 32-bit z-buffer
      0,                              // no stencil buffer
      0,                              // no auxiliary buffer
      PFD_MAIN_PLANE,                 // main layer
      0,                              // reserved
      0, 0, 0                         // layer masks ignored
    };

    int pixelformat;
    if ((pixelformat = ChoosePixelFormat(pDC_->GetSafeHdc(), &pfd)) == 0)
    {
      //MessageBox(L"ChoosePixelFormat failed");
      return FALSE;
    }

    if (SetPixelFormat(pDC_->GetSafeHdc(), pixelformat, &pfd) == FALSE)
    {
      //MessageBox(L"SetPixelFormat failed");
      return FALSE;
    }

    return TRUE;
  }

};
