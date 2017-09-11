#include "gameobject.h"

#include "transform.h"
#include "renderengine.h"

GameObject::GameObject() {
    transform = new Transform();
}

GameObject::~GameObject() {
    delete transform;
}


const GameObject& GameObject::SetParent(GameObject& parent_) {
    assert(parent == nullptr);
    parent = &parent_;
    return *this;
}

const GameObject& GameObject::AddChild(GameObject& child) {
    child.SetParent(*this);
    children.push_back(&child);
    return *this;
}

const GameObject& GameObject::AddComponent(GameComponent& component) {
    component.SetParent(*this);
    components.push_back(&component);
    return *this;
}

Transform& GameObject::GetTransform() {
    return *transform;
}

void GameObject::Input(bool keyboard[512], bool mouse[16], float mouseX, float mouseY) {
    for (GameComponent* component : components)
        component->Input(keyboard, mouse, mouseX, mouseY);

    for (GameObject* child : children)
        child->Input(keyboard, mouse, mouseX, mouseY);
}

void GameObject::Update() {
    for (GameComponent* component : components)
        component->Update();

    for (GameObject* child : children)
        child->Update();
}

void GameObject::Render(RenderEngine& renderEngine) {
    for (GameComponent* component : components)
        component->Render(renderEngine);

    for (GameObject* child : children)
        child->Render(renderEngine);
}
