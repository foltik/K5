#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
public:
	Camera();
	Camera(glm::vec3 position, glm::vec2 angle);
	Camera(glm::vec3 position, glm::vec2 angle, float moveSpeed, float sensitivity);

	void Update();
	void Update(float mouseX, float mouseY);
	
	void MoveForward();
	void MoveBack();

	void StrafeRight();
	void StrafeLeft();
	
	void SetAngle(glm::vec2 angle);
	void SetSpeed(float moveSpeed);
	void SetSens(float sensitivity);

	glm::mat4 GetView();

private:
	glm::vec3 pos;
	glm::vec3 front;
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

	float pitch;
	float yaw;

	glm::mat4 view;

	float lastX;
	float lastY;
	float speed = 1.0f;
	float sens = 1.0f;
};
