#ifndef RVIZ_RENDERING__ORTHOGRAPHIC_HPP_
#define RVIZ_RENDERING__ORTHOGRAPHIC_HPP_

namespace Ogre
{

class Matrix4;

}  // namespace Ogre

namespace rviz_rendering
{

Ogre::Matrix4 buildScaledOrthoMatrix(
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far);

}  // namespace rviz_rendering

#endif  // RVIZ_RENDERING__ORTHOGRAPHIC_HPP_
