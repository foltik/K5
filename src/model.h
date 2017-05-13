#pragma once
#include <vector>

#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.h"
#include "shader.h"

class Model {
public:
	Model(const char* path);

	void Draw(Shader* shader);
private:
	void genModel(const char* path);

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	
	std::vector<Texture> loadTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	
	std::vector<Texture> loadedTextures;
	std::vector<Mesh> m_meshes;
	std::string m_dir;
};