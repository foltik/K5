#pragma once
#include <cassert>

class GameObject;
class RenderEngine;
class Shader;

class GameComponent {
public:
    void SetParent(GameObject& parent_) {
        assert(parent == nullptr);
        parent = &parent_;
    }

    GameObject& GetParent() {
        assert(parent != nullptr);
        return *parent;
    }

    virtual void Input(bool keyboard[512], bool mouse[16], float mouseX, float mouseY) = 0;
    virtual void Update() = 0;
    virtual void Render(Shader& shader, RenderEngine& renderEngine) = 0;

private:
    GameObject* parent = nullptr;
};
