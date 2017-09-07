#pragma once

class GameObject;

class GameComponent {
public:
    virtual void Input() {};
    virtual void Update() {};
    virtual void Render() {};

protected:
    GameObject* parent = nullptr;
};
