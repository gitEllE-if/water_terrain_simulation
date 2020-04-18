#include "mod_camera.hpp"

camera::camera(glm::vec3 pos, glm::vec3 up, GLfloat yyaw, GLfloat ppitch):
	position(pos),
	front(glm::vec3(0.0f, 0.0f, -1.0f)),
	world_up(up),
	yaw(yyaw),
	pitch(ppitch),
	move_speed(SPEED),
	mouse_sensitivity(SENSITIVTY),
	zoom(ZOOM)
{
    update_cam_vector();
}

glm::mat4 camera::get_view_matrix()
{
    return (glm::lookAt(position, position + front, up));
}

void camera::process_keyboard(camera_move direction, GLfloat delta_time)
{
    GLfloat velocity = move_speed * delta_time;
    if (direction == FORWARD)
        position += front * velocity;
    if (direction == BACKWARD)
        position -= front * velocity;
    if (direction == LEFT)
        position -= right * velocity;
    if (direction == RIGHT)
        position += right * velocity;
}

void camera::process_mouse_move(GLfloat xoffset, GLfloat yoffset)
{
	xoffset *= mouse_sensitivity;
	yoffset *= mouse_sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	update_cam_vector();
}

void camera::process_mouse_scroll(GLfloat yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
        zoom -= yoffset;
    if (zoom <= 1.0f)
        zoom = 1.0f;
    if (zoom >= 45.0f)
        zoom = 45.0f;
}

void camera::update_cam_vector()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    right = glm::normalize(glm::cross(front, world_up));
	up = glm::normalize(glm::cross(right, front));
}
