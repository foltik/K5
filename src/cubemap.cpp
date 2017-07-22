#include "cubemap.h"

Cubemap::Cubemap(const char* textures[6]) {
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);

    int width;
    int height;
    int channels;
    unsigned char* data;

    for (GLuint i = 0; i < 6; i++) {
        data = SOIL_load_image(textures[i],
                        &width, &height, &channels,
                        SOIL_LOAD_RGB);

        if (data == nullptr || !width || !height) {
            printf("Error//TextureLoad: Texture %s failed to load\n", textures[i]);
            return;
        }

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                     0, GL_RGB,
                     width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE,
                     data);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (void*)0);

    glBindVertexArray(0);
}
void Cubemap::Draw(glm::mat4 proj, glm::mat4 view) {
    glDepthMask(GL_FALSE);

    shader.Use();
    shader.uMatrix4("view", glm::mat4(glm::mat3(view)));
    shader.uMatrix4("proj", proj);

    glBindVertexArray(vao);
    glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glDepthMask(GL_TRUE);
}