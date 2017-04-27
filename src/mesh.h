#pragma once
#ifdef __linux__
#define GL_GLEXT_PROTOTYPES
#include "SDL2/SDL_opengl.h"
#elif _WIN32
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_opengl_glext.h>
#pragma comment(lib, "opengl32.lib")
#include <gl/GLU.h>
#else
#error Unsupported Platform
#endif

#include "vertex3f.h"

class mesh {
public:
	mesh();

	void addVerts(vertex3f* verts);

	void draw();

	unsigned* vbo;
	unsigned size;
};