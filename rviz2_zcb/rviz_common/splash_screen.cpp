#include "splash_screen.hpp"

#include <iostream>

#include <QDir>
#include <QPainter>  // NOLINT: cpplint is unable to handle the include order here
#include <QPoint>  // NOLINT: cpplint is unable to handle the include order here
#include <QCoreApplication>  // NOLINT: cpplint is unable to handle the include order here

// #include "env_config.hpp"
#include "rviz_common/load_resource.hpp"
#include "globalconfig.h"

namespace rviz_common
{

SplashScreen::SplashScreen(const QPixmap & pixmap)
: QSplashScreen()
{
  const int bottom_border = 27;
  QPixmap splash(pixmap.width(), pixmap.height() + bottom_border);
  splash.fill(QColor(0, 0, 0) );

  QPainter painter(&splash);

  painter.drawPixmap(QPoint(0, 0), pixmap);

  QPixmap overlay = loadPixmap(QDir(GlobalConfig::resource_path).absoluteFilePath("images/splash_overlay.png"));
  painter.drawTiledPixmap(
    QRect(
      0, pixmap.height() - overlay.height(), pixmap.width(),
      pixmap.height() ), overlay);

  // draw version info
  // QString version_info = "r" + QString(get_version().c_str());
  // version_info += " (" + QString(get_distro().c_str()) + ")";
  QString version_info = "r" + QString("1.0.0");
  version_info += " (" + QString("humble") + ")";

  painter.setPen(QColor(160, 160, 160) );
  QRect r = splash.rect();
  r.setRect(r.x() + 5, r.y() + 5, r.width() - 10, r.height() - 10);
  painter.drawText(r, Qt::AlignRight | Qt::AlignBottom, version_info);

  setPixmap(splash);
}

void SplashScreen::showMessage(const QString & message)
{
  QSplashScreen::showMessage(message, Qt::AlignLeft | Qt::AlignBottom, Qt::white);
}

}  // end namespace rviz_common
