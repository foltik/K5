#include "renderengine.h"

#include "camera.h"
#include "light.h"

void RenderEngine::Render(GameObject &object) {
    object.Render(*this);
}

RenderEngine::RenderEngine() {

}
