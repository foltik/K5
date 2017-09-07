#pragma once
#include <vector>

#include "gamecomponent.h"

class Transform;

class GameObject {
public:
    GameObject();
    ~GameObject();

    const GameObject& SetParent(GameObject& parent_);
    const GameObject& AddChild(GameObject& child);
    const GameObject& AddComponent(GameComponent& component);

    Transform& GetTransform();

    void Input(bool keyboard[512], bool mouse[16], float mouseX, float mouseY);
    void Update();
    void Render();

private:
    Transform* transform;

    std::vector<GameObject*> children;
    std::vector<GameComponent*> components;

    GameObject* parent = nullptr;
};