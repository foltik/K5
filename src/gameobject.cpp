#include "gameobject.h"

#include "transform.h"

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
    return *this;
}

void GameObject::Input() {
    for (GameComponent* component : components)
        component->Input();

    for (GameObject* child : children)
        child->Input();
}

void GameObject::Update() {
    for (GameComponent* component : components)
        component->Update();

    for (GameObject* child : children)
        child->Update();
}

void GameObject::Render() {
    for (GameComponent* component : components)
        component->Render();

    for (GameObject* child : children)
        child->Render();
}
