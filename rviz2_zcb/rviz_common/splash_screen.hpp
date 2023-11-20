#ifndef RVIZ_COMMON__SPLASH_SCREEN_HPP_
#define RVIZ_COMMON__SPLASH_SCREEN_HPP_

#include <QSplashScreen>


class QPainter;

namespace rviz_common
{

class SplashScreen : public QSplashScreen
{
  Q_OBJECT

public:
  explicit SplashScreen(const QPixmap & pixmap);

public Q_SLOTS:
  void showMessage(const QString & message);
};

}  // end namespace rviz_common

#endif  // RVIZ_COMMON__SPLASH_SCREEN_HPP_
