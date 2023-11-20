#ifndef RVIZ_RENDERING__RENDER_WINDOW_HPP_
#define RVIZ_RENDERING__RENDER_WINDOW_HPP_

#include <functional>
#include <string>

#include <QObject>  // NOLINT
#include <QWindow>  // NOLINT

#include "OgreSceneNode.h"
#include "OgreRenderTargetListener.h"

// TODO(wjwwood): remove this when the camera can be abstracted
namespace Ogre
{

class Camera;
class ColourValue;
class Light;
class SceneManager;
class Viewport;

}  // namespace Ogre

namespace rviz_rendering
{

class RenderWindowImpl;
class RenderWindowOgreAdapter;

/// QWindow on which a rviz rendering system draws.
class  RenderWindow : public QWindow
{
  Q_OBJECT

public:
  friend RenderWindowOgreAdapter;

  explicit RenderWindow(QWindow * parent = Q_NULLPTR);
  virtual ~RenderWindow();

  void
  captureScreenShot(std::string imageName);

  /// Call after adding this class to a layout.
  virtual
  void
  initialize();

  virtual
  void
  render(QPainter * painter);

  virtual
  void
  render();

  using onRenderWindowMouseEventsCallback = std::function<void (QMouseEvent * event)>;
  void
  setOnRenderWindowMouseEventsCallback(onRenderWindowMouseEventsCallback callback);

  using onRenderWindowWheelEventsCallback = std::function<void (QWheelEvent * event)>;
  void
  setOnRenderWindowWheelEventsCallback(onRenderWindowWheelEventsCallback callback);

  using setupSceneCallback = std::function<void (Ogre::SceneNode *)>;
  void
  setupSceneAfterInit(setupSceneCallback setup_scene_callback);

  void
  windowMovedOrResized();

public slots:
  virtual
  void
  renderLater();

  virtual
  void
  renderNow();

  // Used to capture keyboard and mouse events.
  // bool
  // eventFilter(QObject * target, QEvent * event) override;

protected:
  // virtual
  // void
  // keyPressEvent(QKeyEvent * key_event) override;

  // virtual
  // void
  // keyReleaseEvent(QKeyEvent * key_event) override;

  // virtual
  // void
  // mouseMoveEvent(QMouseEvent * mouse_event) override;

  // virtual
  // void
  // wheelEvent(QWheelEvent * wheel_event) override;

  // virtual
  // void
  // mousePressEvent(QMouseEvent * mouse_event) override;

  // virtual
  // void
  // mouseReleaseEvent(QMouseEvent * mouse_event) override;

  void
  exposeEvent(QExposeEvent * expose_event) override;

  bool
  event(QEvent * event) override;

  RenderWindowImpl * impl_;
  onRenderWindowMouseEventsCallback on_mouse_events_callback_;
  onRenderWindowWheelEventsCallback on_wheel_events_callback_;
};

// TODO(wjwwood): remove this when the Ogre stuff can be abstracted
class  RenderWindowOgreAdapter
{
public:
  static
  void
  setOgreCamera(RenderWindow * render_window, Ogre::Camera * ogre_camera);

  static
  Ogre::Camera *
  getOgreCamera(RenderWindow * render_window);

  static
  Ogre::Viewport *
  getOgreViewport(RenderWindow * render_window);

  static
  void
  setBackgroundColor(RenderWindow * render_window, const Ogre::ColourValue * color);

  static
  Ogre::Light *
  getDirectionalLight(RenderWindow * render_window);

  static
  Ogre::SceneManager *
  getSceneManager(RenderWindow * render_window);

  static
  void
  setSceneManager(RenderWindow * render_window, Ogre::SceneManager * scene_manager);

  static
  void
  addListener(RenderWindow * render_window, Ogre::RenderTargetListener * listener);

  static
  void
  setVisibilityMask(RenderWindow * render_window, uint32_t mask);

  static
  void
  removeListener(RenderWindow * render_window, Ogre::RenderTargetListener * listener);
};

}  // namespace rviz_rendering

#endif  // RVIZ_RENDERING__RENDER_WINDOW_HPP_
