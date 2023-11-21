#ifndef RVIZ_COMMON__VIEWPORT_MOUSE_EVENT_HPP_
#define RVIZ_COMMON__VIEWPORT_MOUSE_EVENT_HPP_

#include <QEvent>
#include <Qt>

class QMouseEvent;
class QWheelEvent;

namespace rviz_common
{

class RenderPanel;

class  ViewportMouseEvent
{
public:
  /// Constructor for use with a QMouseEvent.
  ViewportMouseEvent(RenderPanel * p, QMouseEvent * e, int lx, int ly);

  // Qt has a separate QWheelEvent for mouse wheel events which is not
  // a subclass of QMouseEvent, but has a lot of overlap with it.

  /// Constructor for use with a QWheelEvent.
  ViewportMouseEvent(RenderPanel * p, QWheelEvent * e, int lx, int ly);

  // Convenience functions for getting the state of the buttons and
  // modifiers at the time of the event.
  // For the button which caused a press or release event, use acting_button.
  /// Return true if the left button was used.
  bool left();
  /// Return true if the middle button was used.
  bool middle();
  /// Return true if the right button was used.
  bool right();
  /// Return true if the shift button was pressed during the event.
  bool shift();
  /// Return true if the ctrl button was pressed during the event.
  bool control();
  /// Return true if the alt button was pressed during the event.
  bool alt();

  // Convenience functions to tell if the event is a mouse-down or
  // mouse-up event and which button caused it.
  /// Return true if the left button was raised during the event.
  bool leftUp();
  /// Return true if the middle button was raised during the event.
  bool middleUp();
  /// Return true if the right button was raised during the event.
  bool rightUp();
  /// Return true if the left button was depressed during the event.
  bool leftDown();
  /// Return true if the middle button was depressed during the event.
  bool middleDown();
  /// Return true if the right button was depressed during the event.
  bool rightDown();

  RenderPanel * panel;
  QEvent::Type type;
  int device_pixel_ratio;
  int x;
  int y;
  /// Angle that the common vertical mouse wheel was rotated
  int wheel_delta;
  // The button which caused the event.  Can be Qt::NoButton (move or wheel events).
  Qt::MouseButton acting_button;
  Qt::MouseButtons buttons_down;
  Qt::KeyboardModifiers modifiers;
  int last_x;
  int last_y;
};

}  // namespace rviz_common

#endif  // RVIZ_COMMON__VIEWPORT_MOUSE_EVENT_HPP_
