#pragma once
#include <glm/glm.hpp>

#include "gamecomponent.h"

/*
class Camera {
public:
	Camera();
	Camera(glm::vec3 position, glm::vec2 _angle);
	Camera(glm::vec3 position, glm::vec2 _angle, float moveSpeed, float sensitivity);

	void Update();
	void Update(float mouseX, float mouseY);
	
	void MoveForward();
	void MoveBack();

	void StrafeRight();
	void StrafeLeft();
	
	void SetAngle(glm::vec2 _angle);
	void SetSpeed(float moveSpeed);
	void SetSens(float sensitivity);

	glm::mat4 GetView();
	glm::vec3 GetPos();
	glm::vec2 GetAngle();

private:
	glm::vec2 angle;
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view;

	float lastX;
	float lastY;
	float speed = 1.0f;
	float sens = 1.0f;
};
*/

class Camera : public GameComponent {
public:
    void Input(bool* keyboard, bool* mouse, float mouseX, float mouseY) override;
    void Update() override;
    void Render(Shader& shader, RenderEngine& renderEngine) override;

    glm::mat4 GetViewProjection();

    void SetProjection(const glm::mat4& projection);

private:
    glm::mat4 projection;
};
