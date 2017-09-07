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

    void Input();
    void Update();
    void Render();

private:
    Transform* transform;

    std::vector<GameObject*> children;
    std::vector<GameComponent*> components;

    GameObject* parent = nullptr;
};