#include "mesh_loader.h"

#include <iostream>

#include <OgreHardwareBufferManager.h>
#include <OgreMaterial.h>
#include <OgreMaterialManager.h>
#include <OgreMeshManager.h>
#include <OgreMeshSerializer.h>
#include <OgrePass.h>
#include <OgreSubMesh.h>
#include <OgreTechnique.h>
#include <OgreTextureManager.h>
#include <OgreVector3.h>

#include <QDir>  // NOLINT cpplint cannot handle include order here
#include <QFileInfo>  // NOLINT cpplint cannot handle include order here
#include <QString>  // NOLINT cpplint cannot handle include order here

#include "retriever.h"
#include "assimp_loader.h"
#include "stl_loader.h"

#define ROS_PACKAGE_NAME "rviz_rendering"

resource_retriever::MemoryResource getResource(const std::string& resource_path)
{
	resource_retriever::Retriever retriever;
	resource_retriever::MemoryResource res;
	try {
		res = retriever.get(resource_path);
	}
	catch (resource_retriever::Exception& e) {
		std::cout << e.what() << std::endl;
		return resource_retriever::MemoryResource();
	}

	return res;
}

Ogre::MeshPtr loadMeshFromResource(const std::string& resource_path)
{
	if (Ogre::MeshManager::getSingleton().resourceExists(resource_path, ROS_PACKAGE_NAME)) {
		return Ogre::MeshManager::getSingleton().getByName(resource_path, ROS_PACKAGE_NAME);
	}
	else {
		QFileInfo model_path(QString::fromStdString(resource_path));
		std::string ext = model_path.completeSuffix().toStdString();
		if (ext == "mesh" || ext == "MESH") {
			auto res = getResource(resource_path);

			if (res.size == 0) {
				return Ogre::MeshPtr();
			}

			Ogre::MeshSerializer ser;
			Ogre::DataStreamPtr stream(new Ogre::MemoryDataStream(res.data.get(), res.size));
			Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().createManual(
				resource_path, ROS_PACKAGE_NAME);
			ser.importMesh(stream, mesh.get());
			stream->close();

			return mesh;
		}
		else if (ext == "stl" || ext == "STL" || ext == "stlb" || ext == "STLB") {
			auto res = getResource(resource_path);

			if (res.size == 0) {
				return Ogre::MeshPtr();
			}

			STLLoader stl_loader;
			if (!stl_loader.load(res.data.get(), res.size, resource_path)) {
				std::cout << "Failed to load file [" << resource_path.c_str() << "]" << std::endl;
				return Ogre::MeshPtr();
			}

			return stl_loader.toMesh(resource_path);
		}
		else {
			AssimpLoader assimp_loader;

			const aiScene* scene = assimp_loader.getScene(resource_path);
			if (!scene) {
				std::cout <<
					"Could not load resource [" << resource_path.c_str() << "]: " <<
					assimp_loader.getErrorMessage() << std::endl;
				return Ogre::MeshPtr();
			}

			return assimp_loader.meshFromAssimpScene(resource_path, scene);
		}
	}
}
