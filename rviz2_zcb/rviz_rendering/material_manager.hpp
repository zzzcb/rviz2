#ifndef RVIZ_RENDERING__MATERIAL_MANAGER_HPP_
#define RVIZ_RENDERING__MATERIAL_MANAGER_HPP_

#include <string>

#include <OgreColourValue.h>
#include <OgreMaterialManager.h>
#include <OgreSceneManager.h>

namespace rviz_rendering
{

const float unit_alpha_threshold = 0.9998f;

class  MaterialManager
{
public:
  static void createColorMaterial(
    const std::string & name, const Ogre::ColourValue & color, bool use_self_illumination);

  static void createDefaultColorMaterials();

  static Ogre::MaterialPtr createMaterialWithNoLighting(std::string name);

  static Ogre::MaterialPtr createMaterialWithLighting(std::string name);

  static Ogre::MaterialPtr createMaterialWithShadowsAndLighting(std::string name);

  static Ogre::MaterialPtr createMaterialWithShadowsAndNoLighting(std::string name);

  static void createDefaultMaterials();

  static void enableAlphaBlending(Ogre::MaterialPtr material, float alpha);

  static void enableAlphaBlending(Ogre::SceneBlendType & blending, bool & depth_write, float alpha);
};

}  // namespace rviz_rendering

#endif  // RVIZ_RENDERING__MATERIAL_MANAGER_HPP_
