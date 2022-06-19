#pragma once
#include <GL/glew.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <unordered_map>

#include "texture.h"

struct Vertex;
struct Model;

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager();

    Texture* loadTexture(std::string file, TextureType type = TextureType::SPRITE);
    Model* loadModel(std::string file);

private:
    Texture* genTexture(const std::string& path, TextureType type);

    Model* genModel(const std::string& path);
    void processNode(aiNode* node, const aiScene* scene,
                     std::vector<Vertex>& verts,
                     std::vector<GLuint>& inds,
                     std::vector<Texture*>& texs);
    void processMaterialTextures(aiMaterial* mat, aiTextureType type, std::vector<Texture*>& texs);

    std::unordered_map<std::string, Texture*> loadedTextures;
    std::unordered_map<std::string, Model*> loadedModels;
};
