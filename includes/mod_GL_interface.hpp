#pragma once

#include "mod1.hpp"
#include "mod_view_control.hpp"

class GL_interface
{
	public:
		GL_interface(int window_width, int window_height);
		virtual ~GL_interface();
	protected:
		GLFWwindow*		window;
		GLfloat			win_ratio;
		static GLint	glfw_initialized;
};
