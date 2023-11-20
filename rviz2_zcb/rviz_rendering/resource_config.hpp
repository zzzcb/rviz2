#ifndef RVIZ_RENDERING__RESOURCE_CONFIG_HPP_
#define RVIZ_RENDERING__RESOURCE_CONFIG_HPP_

#include <string>

namespace rviz_rendering
{

/// Return the absolute path to the rviz_rendering resource directory.

std::string
get_resource_directory();

/// Set the absolute path to the rviz_rendering resource directory.
/**
 * Should be called before initializing the rendering system, as this directory
 * is used to load configurations and other resources during setup.
 * This function is not thread-safe.
 */

void
set_resource_directory(const std::string & resource_directory);

/// Return the absolute path to the Ogre plugin directory.

std::string
get_ogre_plugin_directory();

/// Set the absolute path to the Ogre plugin directory.
/**
 * Should be called before initializing the rendering system, as this directory
 * is used to load configurations and other resources during setup.
 * This function is not thread-safe.
 */

void
set_ogre_plugin_directory(const std::string & ogre_plugin_directory);

}  // namespace rviz_rendering

#endif  // RVIZ_RENDERING__RESOURCE_CONFIG_HPP_
