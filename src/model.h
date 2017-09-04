#pragma once
#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "engine.h"

struct Vertex {
    glm::vec3 pos;
	glm::vec3 norm;
	glm::vec2 tex;
};

class Shader;

struct Model {
    void Draw(Shader *shader) {
        int nDiffuse = 0;
        int nSpecular = 0;

        // Load each texture into texture units
        for (int i = 0; i < texs.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + (GLenum)i);
            std::string name = nameFromTextureType(texs[i]->type);
            std::string idx = std::to_string(name == "diffuse" ? nDiffuse++ : nSpecular++);
            std::string uniform = "texture_" + name + "_" + idx;
            shader->uInt(uniform.c_str(), i);
            glBindTexture(GL_TEXTURE_2D, texs[i]->textureId);
        }
        glActiveTexture(GL_TEXTURE0);

        shader->uFloat("material.shine", 16.0f);

        // Draw
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, (GLsizei)numInds, GL_UNSIGNED_INT, (GLvoid *)0);
        glBindVertexArray(0);

        // Unload textures from texture units
        for (int i = 0; i < texs.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + (GLenum)i);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }

    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    size_t numInds;
    std::vector<Texture*> texs;
};
