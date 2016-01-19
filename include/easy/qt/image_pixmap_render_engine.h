#pragma once

#include "../pixel_render_engine.h"

#include <QPixmap>

struct ImagePixmapRenderEngine : PixelRenderEngine
{
  ImagePixmapRenderEngine(QWidget* w) : widget_(w)
  {
  }

  virtual void resize(const easy::ViewInfo&) override
  {
  }

  virtual void paint(const easy::ViewInfo& viewInfo, const easy::Picture<result_t>& picture) override
  {
    QPainter painter(widget_);
    painter.fillRect(widget_->rect(), Qt::black);

    QImage image((const uchar *)picture.raw(), viewInfo.width(), viewInfo.height(), QImage::Format_RGB32);
    pixmap_ = QPixmap::fromImage(image);

    if (pixmap_.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(widget_->rect(), Qt::AlignCenter, "Rendering initial image, please wait...");
        return;
    }
    QRectF source = painter.matrix().inverted().mapRect(widget_->rect()).adjusted(-1, -1, 1, 1);
    QRectF target(viewInfo.offSetX(), viewInfo.offSetY(), viewInfo.windowWidth(), viewInfo.windowHeight());
    painter.drawPixmap(target, pixmap_, source);
  }

private:
  QWidget* widget_;
  QPixmap pixmap_;
};
