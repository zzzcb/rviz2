#include "rviz_rendering/orthographic.hpp"

#include <OgreMatrix4.h>

namespace rviz_rendering
{

Ogre::Matrix4 buildScaledOrthoMatrix(
  float left,
  float right,
  float bottom,
  float top,
  float near,
  float far)
{
  float inverse_width = 1 / (right - left);
  float inverse_height = 1 / (top - bottom);
  float inverse_distance = 1 / (far - near);

  auto proj = Ogre::Matrix4::ZERO;
  proj[0][0] = 2 * inverse_width;
  proj[0][3] = -(right + left) * inverse_width;
  proj[1][1] = 2 * inverse_height;
  proj[1][3] = -(top + bottom) * inverse_height;
  proj[2][2] = -2 * inverse_distance;
  proj[2][3] = -(far + near) * inverse_distance;
  proj[3][3] = 1;
  return proj;
}

}  // namespace rviz_rendering
