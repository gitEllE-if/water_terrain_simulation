#pragma once

#include "mod1.hpp"

enum camera_move
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

class camera
{
	public:
    	camera(	glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
				glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
				GLfloat yaw = YAW, GLfloat pitch = PITCH);
		glm::mat4	get_view_matrix();
		void		process_keyboard(camera_move direction, GLfloat delta_time);
		void		process_mouse_move(GLfloat xoffset, GLfloat yoffset);
		void		process_mouse_scroll(GLfloat yoffset);
		glm::vec3	position;
		glm::vec3	front;
		glm::vec3	up;
		glm::vec3	right;
		glm::vec3	world_up;
		GLfloat		yaw;
		GLfloat		pitch;
		GLfloat		move_speed;
		GLfloat		mouse_sensitivity;
		GLfloat		zoom;
	private:
		void		update_cam_vector();
};
