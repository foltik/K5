#include "resourcemanager.h"

#include <SOIL/SOIL.h>
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
#include <assimp/Importer.hpp>

#include "engine.h"
#include "model.h"

// Free each resource loaded by the manager
ResourceManager::~ResourceManager() {
    for (auto& pair : loadedTextures)
        delete pair.second;

    for (auto& pair : loadedModels)
        delete pair.second;
}

// Looks for a texture to load, starting in "CWD/textures/"
Texture* ResourceManager::loadTexture(const std::string file, TextureType type) {
    if (loadedTextures.count(file)) {
        // If it was already loaded, just return it
        return loadedTextures[file];
    } else {
        // Otherwise figure out the whole path and load in the texture
        std::string path = CEngine::Instance().getCwd() + std::string("textures/") + file;
        Texture* tex = genTexture(path, type);
        loadedTextures[file] = tex;
        return tex;
    }
}

Texture* ResourceManager::genTexture(const std::string& path, TextureType type) {
    auto* texture = new Texture;
    texture->type = type;

	// Generate the texture object for OpenGL
	glGenTextures(1, &texture->textureId);

	// Bind the texture object
	glBindTexture(GL_TEXTURE_2D, texture->textureId);

	// Load the texture
    texture->path = path;
	unsigned char* data = SOIL_load_image(path.c_str(), &texture->width, &texture->height, nullptr, SOIL_LOAD_RGBA);
	if (data == nullptr) {
        // If the texture wasn't able to be loaded, use an error texture instead
		printf("Error//TextureLoad: Texture %s failed to load\n", path.c_str());
        std::string errorTexturePath = CEngine::Instance().getCwd() + "textures/__error.png";
        data = SOIL_load_image(errorTexturePath.c_str(), &texture->width, &texture->height, nullptr, SOIL_LOAD_RGBA);
        texture->path = errorTexturePath;
	}

	// Load the texture data into the texture object and generate mipmaps
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Free the texture data and unbind the texture object
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

Model* ResourceManager::loadModel(std::string file) {
    if (loadedModels.count(file)) {
        // If it was already loaded, just return it
        return loadedModels[file];
    } else {
        // Otherwise figure out the whole path and load in the texture
        std::string path = CEngine::Instance().getCwd() + std::string("models/") + file;
        Model* model = genModel(path);
        loadedModels[file] = model;
        return model;
    }
}

Model* ResourceManager::genModel(const std::string &path) {
    auto* model = new Model;

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path,
                                             aiProcess_Triangulate |
                                             aiProcess_FlipUVs |
                                             aiProcess_GenNormals |
                                             aiProcess_OptimizeMeshes |
                                             aiProcess_JoinIdenticalVertices);

    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
		printf("Error//ModelLoad: %s\n", importer.GetErrorString());
        std::string errorModelPath = CEngine::Instance().getCwd() + "models/__error.obj";
        importer.FreeScene();
        scene = importer.ReadFile(errorModelPath,
                                  aiProcess_Triangulate |
                                  aiProcess_FlipUVs |
                                  aiProcess_GenNormals |
                                  aiProcess_OptimizeMeshes |
                                  aiProcess_JoinIdenticalVertices);
	}

    // Set up the vectors to hold the model data
    std::vector<Vertex> verts;
    std::vector<GLuint> inds;
    std::vector<Texture*> texs;

    // Recursively process each node, storing the mesh data into the vectors
    processNode(scene->mRootNode, scene, verts, inds, texs);

    // Copy over some metadata
    model->texs = std::vector<Texture*>(texs);
    model->numInds = inds.size();

    // Create the OpenGL object after we have all the data
    glGenVertexArrays(1, &model->vao);
    glGenBuffers(1, &model->ebo);
    glGenBuffers(1, &model->vbo);

    glBindVertexArray(model->vao);

    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBufferData(GL_ARRAY_BUFFER, (GLsizei)verts.size() * sizeof(Vertex), &verts[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizei)inds.size() * sizeof(GLuint), &inds[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, norm));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, tex));

    glBindVertexArray(0);

    return model;
}

void ResourceManager::processNode(aiNode *node, const aiScene *scene,
                                  std::vector<Vertex>& verts,
                                  std::vector<GLuint>& inds,
                                  std::vector<Texture*>& texs) {

    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        // Load each vertex (pos, normals, tex coord)
        for (unsigned int j = 0; j < mesh->mNumVertices; j++) {
            Vertex vert {
                    {mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z},
                    {mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z},
                    {0.0f, 0.0f}
            };

            if (mesh->HasTextureCoords(0))
                vert.tex = {mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y};

            verts.push_back(vert);
        }

        // Load each vertex index
        for (unsigned int j = 0; j < mesh->mNumFaces; j++) {
            // Each face is guaranteed to have 3 indices
            inds.push_back(mesh->mFaces[j].mIndices[0]);
            inds.push_back(mesh->mFaces[j].mIndices[1]);
            inds.push_back(mesh->mFaces[j].mIndices[2]);
        }

        processMaterialTextures(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_DIFFUSE, texs);
        processMaterialTextures(scene->mMaterials[mesh->mMaterialIndex], aiTextureType_SPECULAR, texs);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        processNode(node->mChildren[i], scene, verts, inds, texs);
    }
}

void ResourceManager::processMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<Texture*>& texs) {
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++) {
        aiString path;
        mat->GetTexture(type, i, &path);

        TextureType texType;
        if (type == aiTextureType_SPECULAR)
            texType = TextureType::SPECULAR;
        else if (type == aiTextureType_DIFFUSE)
            texType = TextureType::DIFFUSE;
        else
            texType = TextureType::UNKNOWN;

        texs.push_back(loadTexture(std::string(path.C_Str()), texType));
    }
}


