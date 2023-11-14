#ifndef OGRE_RENDERING__STL_LOADER_H_
#define OGRE_RENDERING__STL_LOADER_H_

#include <string>
#include <vector>

#include <OgreVector3.h>
#include <OgreMesh.h>

#define ROS_PACKAGE_NAME "OgreRendering"

class STLLoader
{
public:
	STLLoader() = default;
	~STLLoader() = default;

	bool load(uint8_t* buffer, size_t num_bytes, const std::string& origin);

	Ogre::MeshPtr toMesh(const std::string& name);

	struct Triangle
	{
		Ogre::Vector3 vertices_[3];
		Ogre::Vector3 normal_;
	};

	typedef std::vector<Triangle> V_Triangle;
	V_Triangle triangles_;

protected:
	//! Load a binary STL file
	bool loadBinary(uint8_t* buffer);
};


#endif 

