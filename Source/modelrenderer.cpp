#include "modelrenderer.h"

#include "model.h"
#include "shader.h"
#include "gameobject.h"
#include "transform.h"

ModelRenderer::ModelRenderer(Shader *shader_, Model *model_) {
    shader = shader_;
    model = model_;
}

void ModelRenderer::Input(bool keyboard[512], bool mouse[16], float mouseX, float mouseY) {

}

void ModelRenderer::Update() {

}

void ModelRenderer::Render(Shader& shader, RenderEngine &renderEngine) {
    shader.Use();
    shader.uMatrix4("model", GetParent().GetTransform().GetMatrix());
    model->Draw(&shader);
}
