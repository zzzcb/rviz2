#include "rviz_rendering/resource_config.hpp"

#include <string>

#ifndef RVIZ_RENDERING_DEFAULT_RESOURCE_DIRECTORY
#define RVIZ_RENDERING_DEFAULT_RESOURCE_DIRECTORY ""
#endif

#ifndef RVIZ_RENDERING_OGRE_PLUGIN_DIR
#define RVIZ_RENDERING_OGRE_PLUGIN_DIR "not set!"
#endif

namespace
{

// TODO(wjwwood): avoid static std::string's
static std::string __resource_directory = RVIZ_RENDERING_DEFAULT_RESOURCE_DIRECTORY;  // NOLINT
static std::string __ogre_plugin_directory = RVIZ_RENDERING_OGRE_PLUGIN_DIR;  // NOLINT

}  // namespace

namespace rviz_rendering
{

std::string
get_resource_directory()
{
  return __resource_directory;
}

void
set_resource_directory(const std::string & resource_directory)
{
  __resource_directory = resource_directory;
}

std::string
get_ogre_plugin_directory()
{
  return __ogre_plugin_directory;
}

void
set_ogre_plugin_directory(const std::string & ogre_plugin_directory)
{
  __ogre_plugin_directory = ogre_plugin_directory;
}

}  // namespace rviz_rendering
