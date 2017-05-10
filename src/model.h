#pragma once
#include <GL/glew.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

#include "mesh.h"
#include "shader.h"

class Model {
public:
	Model(GLchar* path);

	void Draw(Shader shader);
private:
	void genModel(GLchar* path);

	void processNode();
	void processMesh();
	
	std::vector<Texture> loadTextures();
	
	std::vector<Mesh> meshes;
};