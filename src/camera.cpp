#include "camera.h"

Camera::Camera(glm::vec3 position, glm::vec2 angle) {
	pos = position;
	pitch = angle.x;
	yaw = angle.y;
}

Camera::Camera(glm::vec3 position, glm::vec2 angle, float moveSpeed, float sensitivity) {
	pos = position;
	pitch = angle.x;
	yaw = angle.y;
	speed = moveSpeed;
	sens = sensitivity;
}

void Camera::Update() {
	front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

	view = glm::lookAt(pos, pos + front, up);
}

void Camera::Update(float mouseX, float mouseY) {
	yaw += (mouseX - lastX) * sens;
	pitch += (lastY - mouseY) * sens;

	lastX = mouseX;
	lastY = mouseY;

	if (yaw > 360.0f)
		yaw -= 360.0f;
	if (yaw < -360.0f)
		yaw += 360.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;
	if (pitch > 89.0f)
		pitch = 89.0f;

	front.x = glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw));

	view = glm::lookAt(pos, pos + front, up);
}

void Camera::MoveForward() { 
	pos += speed * front;
}
void Camera::MoveBack() { 
	pos -= speed * front;
}

void Camera::StrafeRight() { 
	pos += speed * glm::normalize(glm::cross(front, up));
}
void Camera::StrafeLeft() {
	pos -= speed * glm::normalize(glm::cross(front, up));
}

void Camera::SetAngle(glm::vec2 angle) {
	pitch = angle.x;
	yaw = angle.y;

	if (yaw > 360.0f)
		while (yaw > 360.0f)
			yaw -= 360.0f;

	if (yaw < -360.0f)
		while (yaw < -360.0f)
				yaw += 360.0f;

	if (pitch < -89.0f)
		pitch = -89.0f;

	if (pitch > 89.0f)
		pitch = 89.0f;
}

void Camera::SetSpeed(float moveSpeed) { speed = moveSpeed; }

void Camera::SetSens(float sensitivity) { sens = sensitivity; }

glm::mat4 Camera::GetView() {
	return view;
}

glm::vec3 Camera::GetPos() {
	return pos;
}

glm::vec2 Camera::GetAngle() {
	return glm::vec2(pitch, yaw);
}
