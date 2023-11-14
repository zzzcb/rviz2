#include "stl_loader.h"

#include <iostream>

#include <OgreManualObject.h>


bool STLLoader::load(uint8_t* buffer, const size_t num_bytes, const std::string& origin)
{
	// check for ascii since we can only load binary types with this class
	std::string buffer_str = std::string(reinterpret_cast<char*>(buffer), num_bytes);

	if (buffer_str.substr(0, 5) == std::string("solid") &&
		buffer_str.find("endsolid", 5) != std::string::npos)
	{
		std::cout <<
			"The STL file '" << origin << "' is malformed. It "
			"starts with the word 'solid' and also contains the "
			"word 'endsolid', indicating that it's an ASCII STL "
			"file, but rviz can only load binary STL files so it "
			"will not be loaded. Please convert it to a "
			"binary STL file." << std::endl;
		return false;
	}

	// make sure there's enough data for a binary STL header and triangle count
	static const size_t binary_stl_header_len = 84;
	if (num_bytes <= binary_stl_header_len) {
		std::cout <<
			"The STL file '" << origin << "' is malformed. It "
			"appears to be a binary STL file but does not contain "
			"enough data for the 80 byte header and 32-bit integer "
			"triangle count." << std::endl;
		return false;
	}

	// one last check to make sure that the size matches the number of triangles
	unsigned int num_triangles = *(reinterpret_cast<uint32_t*>(buffer + 80));
	static const size_t number_of_bytes_per_triangle = 50;
	size_t expected_size = binary_stl_header_len + num_triangles * number_of_bytes_per_triangle;
	if (num_bytes < expected_size) {
		std::cout <<
			"The STL file '" << origin << "' is malformed. According "
			"to the binary STL header it should have '" <<
			num_triangles << "' triangles, but it has too little data for that to be the case." << std::endl;
		return false;
	}
	else if (num_bytes > expected_size) {
		std::cout <<
			"The STL file '" << origin << "' is malformed. According "
			"to the binary STL header it should have '" <<
			num_triangles << "' triangles, but it has too much" <<
			" data for that to be the case. The extra data will be ignored." << std::endl;
	}

	// load the binary STL data
	return this->loadBinary(buffer);
}

bool STLLoader::loadBinary(uint8_t* buffer)
{
	buffer += 80;  // skip the 80 byte header

	unsigned int numTriangles = *(unsigned int*)buffer;
	buffer += 4;

	for (unsigned int currentTriangle = 0; currentTriangle < numTriangles; ++currentTriangle) {
		Triangle triangle;

		triangle.normal_.x = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.normal_.y = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.normal_.z = *reinterpret_cast<float*>(buffer);
		buffer += 4;

		triangle.vertices_[0].x = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[0].y = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[0].z = *reinterpret_cast<float*>(buffer);
		buffer += 4;

		triangle.vertices_[1].x = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[1].y = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[1].z = *reinterpret_cast<float*>(buffer);
		buffer += 4;

		triangle.vertices_[2].x = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[2].y = *reinterpret_cast<float*>(buffer);
		buffer += 4;
		triangle.vertices_[2].z = *reinterpret_cast<float*>(buffer);
		buffer += 4;

		buffer += 2;  // 2 bytes of the attributeByteCount. It is usually 0, can be ignored.

		if (triangle.normal_.squaredLength() < 0.001) {
			Ogre::Vector3 side1 = triangle.vertices_[0] - triangle.vertices_[1];
			Ogre::Vector3 side2 = triangle.vertices_[1] - triangle.vertices_[2];
			triangle.normal_ = side1.crossProduct(side2);
		}
		triangle.normal_.normalise();

		triangles_.push_back(triangle);
	}

	return true;
}

void calculateUV(const Ogre::Vector3& vec, float& u, float& v)
{
	Ogre::Vector3 pos(vec);
	pos.normalise();
	u = acos(pos.y / pos.length());

	float val = pos.x / (sin(u));
	v = acos(val);

	u /= Ogre::Math::PI;
	v /= Ogre::Math::PI;
}

void addVertex(
	std::shared_ptr<Ogre::ManualObject> object, const STLLoader::Triangle& triangle, int index)
{
	float u, v;
	u = v = 0.0f;

	object->position(triangle.vertices_[index]);
	object->normal(triangle.normal_);
	calculateUV(triangle.vertices_[index], u, v);
	object->textureCoord(u, v);
}

Ogre::MeshPtr STLLoader::toMesh(const std::string& name)
{
	std::shared_ptr<Ogre::ManualObject> object =
		std::make_shared<Ogre::ManualObject>("the one and only");
	object->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST, ROS_PACKAGE_NAME);

	unsigned int vertexCount = 0;
	for (const STLLoader::Triangle& triangle : triangles_) {
		if (vertexCount >= 2004) {
			// Subdivide large meshes into submeshes with at most 2004
			// vertices to prevent problems on some graphics cards.
			object->end();
			object->begin(
				"BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST, ROS_PACKAGE_NAME);
			vertexCount = 0;
		}

		addVertex(object, triangle, 0);
		addVertex(object, triangle, 1);
		addVertex(object, triangle, 2);

		object->triangle(vertexCount + 0, vertexCount + 1, vertexCount + 2);

		vertexCount += 3;
	}

	object->end();

	Ogre::MeshPtr mesh = object->convertToMesh(name, ROS_PACKAGE_NAME);
	mesh->buildEdgeList();

	return mesh;
}

