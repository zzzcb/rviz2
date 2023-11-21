#include "rviz_common/viewport_mouse_event.hpp"

#include <QMouseEvent>
#include <QWheelEvent>

#include "rviz_common/render_panel.hpp"
#include "rviz_rendering/render_window.hpp"

namespace rviz_common
{

ViewportMouseEvent::ViewportMouseEvent(RenderPanel * p, QMouseEvent * e, int lx, int ly)
: panel(p),
  type(e->type()),
  device_pixel_ratio(static_cast<int>(panel->getRenderWindow()->devicePixelRatio())),
  x(e->x() * device_pixel_ratio),
  y(e->y() * device_pixel_ratio),
  wheel_delta(0),
  acting_button(e->button()),
  buttons_down(e->buttons()),
  modifiers(e->modifiers()),
  last_x(lx * device_pixel_ratio),
  last_y(ly * device_pixel_ratio)
{
}

ViewportMouseEvent::ViewportMouseEvent(RenderPanel * p, QWheelEvent * e, int lx, int ly)
: panel(p),
  type(e->type()),
  device_pixel_ratio(static_cast<int>(panel->getRenderWindow()->devicePixelRatio())),
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  x(e->position().x() * device_pixel_ratio),
  y(e->position().y() * device_pixel_ratio),
#else
  x(e->x() * device_pixel_ratio),
  y(e->y() * device_pixel_ratio),
#endif
  wheel_delta(e->angleDelta().y()),
  acting_button(Qt::NoButton),
  buttons_down(e->buttons()),
  modifiers(e->modifiers()),
  last_x(lx * device_pixel_ratio),
  last_y(ly * device_pixel_ratio)
{
}

bool ViewportMouseEvent::left()
{
  return buttons_down & Qt::LeftButton;
}

bool ViewportMouseEvent::middle()
{
  return buttons_down & Qt::MiddleButton;
}

bool ViewportMouseEvent::right()
{
  return buttons_down & Qt::RightButton;
}

bool ViewportMouseEvent::shift()
{
  return modifiers & Qt::ShiftModifier;
}

bool ViewportMouseEvent::control()
{
  return modifiers & Qt::ControlModifier;
}

bool ViewportMouseEvent::alt()
{
  return modifiers & Qt::AltModifier;
}

bool ViewportMouseEvent::leftUp()
{
  return type == QEvent::MouseButtonRelease && acting_button == Qt::LeftButton;
}

bool ViewportMouseEvent::middleUp()
{
  return type == QEvent::MouseButtonRelease && acting_button == Qt::MiddleButton;
}

bool ViewportMouseEvent::rightUp()
{
  return type == QEvent::MouseButtonRelease && acting_button == Qt::RightButton;
}

bool ViewportMouseEvent::leftDown()
{
  return type == QEvent::MouseButtonPress && acting_button == Qt::LeftButton;
}

bool ViewportMouseEvent::middleDown()
{
  return type == QEvent::MouseButtonPress && acting_button == Qt::MiddleButton;
}

bool ViewportMouseEvent::rightDown()
{
  return type == QEvent::MouseButtonPress && acting_button == Qt::RightButton;
}

}  // namespace rviz_common
