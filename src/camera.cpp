#include "camera.h"

#include "gameobject.h"
#include "transform.h"

#include <glm/gtc/matrix_transform.hpp>

/*
Camera::Camera() : pos(0.0f), angle(0.0f) {}

Camera::Camera(glm::vec3 position, glm::vec2 _angle) {
	pos = position;
	angle = _angle;
}

Camera::Camera(glm::vec3 position, glm::vec2 _angle, float moveSpeed, float sensitivity) {
	pos = position;
	angle = _angle;
	speed = moveSpeed;
	sens = sensitivity;
}

void Camera::Update() {
	front.x = glm::cos(glm::radians(angle.y)) * glm::cos(glm::radians(angle.x));
	front.y = glm::sin(glm::radians(angle.y));
	front.z = glm::cos(glm::radians(angle.y)) * glm::sin(glm::radians(angle.x));

	view = glm::lookAt(pos, pos + front, up);
}

void Camera::Update(float mouseX, float mouseY) {
	angle.x += (mouseX - lastX) * sens;
	angle.y += (lastY - mouseY) * sens;

	lastX = mouseX;
	lastY = mouseY;

	if (angle.x > 360.0f)
		angle.x -= 360.0f;
	if (angle.x < -360.0f)
		angle.x += 360.0f;

	if (angle.y < -89.0f)
		angle.y = -89.0f;
	if (angle.y > 89.0f)
		angle.y = 89.0f;

	front.x = glm::cos(glm::radians(angle.y)) * glm::cos(glm::radians(angle.x));
	front.y = glm::sin(glm::radians(angle.y));
	front.z = glm::cos(glm::radians(angle.y)) * glm::sin(glm::radians(angle.x));

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
	angle.y = angle.x;
	angle.x = angle.y;

	if (angle.x > 360.0f)
		while (angle.x > 360.0f)
			angle.x -= 360.0f;

	if (angle.x < -360.0f)
		while (angle.x < -360.0f)
				angle.x += 360.0f;

	if (angle.y < -89.0f)
		angle.y = -89.0f;

	if (angle.y > 89.0f)
		angle.y = 89.0f;
}

void Camera::SetSpeed(float moveSpeed) { speed = moveSpeed; }
void Camera::SetSens(float sensitivity) { sens = sensitivity; }

glm::mat4 Camera::GetView() { return view; }
glm::vec3 Camera::GetPos() { return pos; }
glm::vec2 Camera::GetAngle() { return angle; }
*/

void Camera::Input(bool* keyboard, bool* mouse, float mouseX, float mouseY) {

}

void Camera::Update() {

}

void Camera::Render(Shader& shader, RenderEngine& renderEngine) {

}

void Camera::SetProjection(const glm::mat4& projection) {
    Camera::projection = projection;
}

glm::mat4 Camera::GetViewProjection() {
    return projection * GetParent().GetTransform().GetMatrix();
}
