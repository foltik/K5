#include "model.h"

Model::Model(const char* path) {
	genModel(path);
}

void Model::Draw(Shader* shader) {
	for (auto &mesh : m_meshes)
		mesh.Draw(shader);
}

void Model::genModel(const char* path) {
	std::string p = CEngine::Instance().path + std::string(path);
    path = p.c_str();

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_OptimizeMeshes | aiProcess_JoinIdenticalVertices);

	if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		printf("Error//ModelLoad: %s\n", importer.GetErrorString());
		return;
	}

	m_dir = std::string(path).substr(0, std::string(path).find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (GLuint i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> verts;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	// Load vertices and texture coordinates if they exist
	for (GLuint i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vec;

		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.pos = vec;

		vec.x = mesh->mNormals[i].x;
		vec.y = mesh->mNormals[i].y;
		vec.z = mesh->mNormals[i].z;
		vertex.norm = vec;

		if (mesh->HasTextureCoords(0)) {
			glm::vec2 tex;
			
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
			vertex.tex = tex;
		}
		else {
			vertex.tex = glm::vec2(0.0f, 0.0f);
		}

		verts.push_back(vertex);
	}

	// Load indices
	for (GLuint i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		assert(face.mNumIndices == 3);

		indices.push_back(face.mIndices[0]);
		indices.push_back(face.mIndices[1]);
		indices.push_back(face.mIndices[2]);
	}
	
	// Load materials
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];

	std::vector<Texture> diffMaps = loadTextures(mat, aiTextureType_DIFFUSE, "diffuse");
	textures.insert(textures.end(), diffMaps.begin(), diffMaps.end());

	std::vector<Texture> specMaps = loadTextures(mat, aiTextureType_SPECULAR, "specular");
	textures.insert(textures.end(), specMaps.begin(), specMaps.end());

	return Mesh(verts, indices, textures);
}

std::vector<Texture> Model::loadTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (GLuint i = 0; i < mat->GetTextureCount(type); i++) {
		aiString str;
		mat->GetTexture(type, i, &str);
		
		for (GLuint j = 0; j < loadedTextures.size(); j++) {
			if (std::strcmp(loadedTextures[j].m_path.c_str(), str.C_Str()) == 0) {
				textures.push_back(loadedTextures[j]);
				return textures;
			}
		}

		std::string fileStr = str.C_Str();
		fileStr = fileStr.substr(fileStr.find_last_of(R"(/\)") + 1);

		Texture tex(fileStr.c_str(), m_dir.c_str());
		tex.type = typeName;

		textures.push_back(tex);
		loadedTextures.push_back(tex);
	}

	return textures;
}
