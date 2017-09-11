#pragma once

#include "gamecomponent.h"

class Model;
class Shader;

class ModelRenderer : public GameComponent {
public:
    ModelRenderer(Shader* shader, Model* model);

    void Input(bool keyboard[512], bool mouse[16], float mouseX, float mouseY) override;
    void Update() override;
    void Render(RenderEngine &renderEngine) override;

private:
    Shader* shader;
    Model* model;
};