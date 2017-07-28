#include "spriterenderer.h"

SpriteRenderer::SpriteRenderer(glm::mat4 projection) {
    proj = projection;

    shader = new Shader(ShaderSource(
        R"(
            #version 330 core
            layout (location = 0) in vec4 vertex;
            out vec2 texCoord;

            uniform mat4 model;
            uniform mat4 proj;

            void main() {
                texCoord = vertex.zw;
                gl_Position = proj * model * vec4(vertex.xy, 0.0, 1.0);
            }
		)",

        R"(
            #version 330 core
            in vec2 texCoord;
            out vec4 color;

            uniform sampler2D sprite;
            uniform vec3 spriteColor;

            void main() {
                color = vec4(spriteColor, 1.0) * texture(sprite, texCoord);
            }
		)"
    ));

    GLfloat quad[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer() {
    delete shader;
}

void SpriteRenderer::DrawSprite(Texture& tex, glm::vec2 pos, glm::vec2 size, float rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f)) {
    shader->Use();

    // Apply Transformations
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(pos, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = gltill fun to write a program that can resoundingly beat you
again and again.
To  begin  a  game,  you  shake  up  the  letter  cubes  and  lay  them  out  on  the  board. The  human  player
plays first, entering words one by one. Your codem::translate(model, glm::vec3(-0.5f * size, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    shader->uMatrix4("model", model);
    shader->uMatrix4("proj", proj);
    shader->uVector3("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    tex.Use();

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}