#ifndef OGRE_RENDERING__ASSIMP_LOADER_H_
#define OGRE_RENDERING__ASSIMP_LOADER_H_

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <OgreHardwareBufferManager.h>
#include <OgreMesh.h>

#define ROS_PACKAGE_NAME "OgreRendering"

class AssimpLoader
{
public:
	AssimpLoader();
	const aiScene* getScene(const std::string& resource_path);
	Ogre::MeshPtr meshFromAssimpScene(const std::string& name, const aiScene* scene);
	std::string getErrorMessage();


private:
	struct SubMeshInternals
	{
		Ogre::HardwareVertexBufferSharedPtr vertex_buffer_;
		Ogre::AxisAlignedBox& axis_aligned_box_;
		float& radius_;

		SubMeshInternals(
			Ogre::HardwareVertexBufferSharedPtr vertex_buffer, Ogre::AxisAlignedBox&
			axis_aligned_box, float& radius)
			: vertex_buffer_(vertex_buffer),
			axis_aligned_box_(axis_aligned_box),
			radius_(radius)
		{}
	};

	struct MaterialInternals
	{
		Ogre::Pass* pass_;

		Ogre::ColourValue diffuse_;
		Ogre::ColourValue specular_;
		Ogre::ColourValue ambient_;

		MaterialInternals(
			Ogre::Pass* pass,
			const Ogre::ColourValue& diffuse,
			const Ogre::ColourValue& specular,
			const Ogre::ColourValue& ambient)
			: pass_(pass),
			diffuse_(diffuse),
			specular_(specular),
			ambient_(ambient)
		{}
	};

  std::vector<Ogre::MaterialPtr> loadMaterials(
    const std::string & resource_path, const aiScene * scene);
  void setLightColorsFromAssimp(
    const std::string & resource_path,
    Ogre::MaterialPtr & mat,
    const aiMaterial * ai_material,
    MaterialInternals & material_internals);

  void loadTexture(const std::string & resource_path);

  void setBlending(
    Ogre::MaterialPtr & mat, const aiMaterial * ai_material,
    const MaterialInternals & material_internals);

	void buildMesh(
		const aiScene* scene,
		const aiNode* node,
		const Ogre::MeshPtr& mesh,
		Ogre::AxisAlignedBox& axis_aligned_box,
		float& radius,
		std::vector<Ogre::MaterialPtr>& material_table);
	aiMatrix4x4 computeTransformOverSceneGraph(const aiNode* node);
	void declareVertexBufferOrdering(const aiMesh* input_mesh, const Ogre::VertexData* vertex_data);
	Ogre::HardwareVertexBufferSharedPtr allocateVertexBuffer(
		const aiMesh* input_mesh, Ogre::VertexData* vertex_data);
	void fillVertexBuffer(
		const aiMatrix4x4& transform,
		const aiMatrix3x3& inverse_transpose_rotation,
		const aiMesh* input_mesh,
		SubMeshInternals& internals);
	void createAndFillIndexBuffer(
		const aiMesh* input_mesh, const Ogre::SubMesh* submesh, const Ogre::VertexData* vertex_data);

	template<typename T>
	void fillIndexBuffer(const aiMesh* input_mesh, Ogre::HardwareIndexBufferSharedPtr& index_buffer)
	{
		auto* indices =
			static_cast<T*>(index_buffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));

		for (T j = 0; j < input_mesh->mNumFaces; j++) {
			aiFace& face = input_mesh->mFaces[j];
			for (T k = 0; k < face.mNumIndices; ++k) {
				*indices++ = face.mIndices[k];
			}
		}
		index_buffer->unlock();
	}

	std::unique_ptr<Assimp::Importer> importer_;
};

#endif