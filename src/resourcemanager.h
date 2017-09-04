#pragma once
#include <GL/glew.h>
#include <SOIL/SOIL.h>
#include <unordered_map>

#include "engine.h"
#include "texture.h"

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager();

    Texture* loadTexture(std::string file);

private:
    Texture* genTexture(const std::string& path);


    std::unordered_map<std::string, Texture*> loadedTextures;
};
