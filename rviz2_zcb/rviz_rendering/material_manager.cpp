#include "rviz_rendering/material_manager.hpp"

#include <string>

#include <OgreMaterial.h>
#include <OgreTechnique.h>

namespace rviz_rendering
{

void MaterialManager::createColorMaterial(
  const std::string & name, const Ogre::ColourValue & color, bool use_self_illumination)
{
  Ogre::MaterialPtr mat = Ogre::MaterialManager::getSingleton().create(name, "rviz_rendering");
  mat->setAmbient(color * 0.5f);
  mat->setDiffuse(color);
  if (use_self_illumination) {
    mat->setSelfIllumination(color);
  }
  mat->setLightingEnabled(true);
  mat->setReceiveShadows(false);
}

void MaterialManager::createDefaultColorMaterials()
{
  createColorMaterial("RVIZ/Red", Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f), true);
  createColorMaterial("RVIZ/Green", Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f), true);
  createColorMaterial("RVIZ/Blue", Ogre::ColourValue(0.0f, 0.0f, 1.0f, 1.0f), true);
  createColorMaterial("RVIZ/Cyan", Ogre::ColourValue(0.0f, 1.0f, 1.0f, 1.0f), true);
  createColorMaterial("RVIZ/ShadedRed", Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f), false);
  createColorMaterial("RVIZ/ShadedGreen", Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f), false);
  createColorMaterial("RVIZ/ShadedBlue", Ogre::ColourValue(0.0f, 0.0f, 1.0f, 1.0f), false);
  createColorMaterial("RVIZ/ShadedCyan", Ogre::ColourValue(0.0f, 1.0f, 1.0f, 1.0f), false);
}

Ogre::MaterialPtr MaterialManager::createMaterialWithNoLighting(std::string name)
{
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(name, "rviz_rendering");
  material->setReceiveShadows(false);
  material->getTechnique(0)->setLightingEnabled(false);

  return material;
}

Ogre::MaterialPtr MaterialManager::createMaterialWithLighting(std::string name)
{
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(name, "rviz_rendering");
  material->setReceiveShadows(false);
  material->getTechnique(0)->setLightingEnabled(true);

  return material;
}

Ogre::MaterialPtr MaterialManager::createMaterialWithShadowsAndLighting(std::string name)
{
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(name, "rviz_rendering");
  material->getTechnique(0)->setLightingEnabled(true);

  return material;
}

Ogre::MaterialPtr MaterialManager::createMaterialWithShadowsAndNoLighting(std::string name)
{
  Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(name, "rviz_rendering");
  material->getTechnique(0)->setLightingEnabled(false);

  return material;
}

void MaterialManager::enableAlphaBlending(Ogre::MaterialPtr material, float alpha)
{
  if (alpha < unit_alpha_threshold) {
    material->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);
    material->setDepthWriteEnabled(false);
  } else {
    material->setSceneBlending(Ogre::SBT_REPLACE);
    material->setDepthWriteEnabled(true);
  }
}

void MaterialManager::enableAlphaBlending(
  Ogre::SceneBlendType & blending, bool & depth_write, float alpha)
{
  if (alpha < unit_alpha_threshold) {
    blending = Ogre::SBT_TRANSPARENT_ALPHA;
    depth_write = false;
  } else {
    blending = Ogre::SBT_REPLACE;
    depth_write = true;
  }
}

void MaterialManager::createDefaultMaterials()
{
  auto retrieve_result = Ogre::MaterialManager::getSingleton().createOrRetrieve(
    "BaseWhiteNoLighting", "rviz_rendering");
  auto material = std::dynamic_pointer_cast<Ogre::Material>(retrieve_result.first);
  if (material) {
    material->setLightingEnabled(false);
  }
}

}  // namespace rviz_rendering
