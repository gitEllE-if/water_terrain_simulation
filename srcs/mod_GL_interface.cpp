/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_GL_interface.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:46:54 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 00:15:46 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_GL_interface.hpp"

GL_interface::GL_interface(int win_width, int win_height):
	window(nullptr),
    win_ratio(GLfloat(win_width) / (GLfloat)win_height)
{
	int32_t width;
	int32_t	height;
	if (!glfw_initialized)
	{
		glfw_initialized = glfwInit();
		if (glfw_initialized != GL_TRUE)
		{
			std::cout << "error: unable to initialize GLFW\n" << std::endl;
			return ;
		}
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	window = glfwCreateWindow(win_width, win_height, "~~[MOD1]~~", NULL, NULL);
	if (!window)
	{
		std::cout << "error: unable to create a window\n" << std::endl;
		glfwTerminate();
        return ;
	}
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "error: unable to initialize GLEW\n" << std::endl;
		glfwTerminate();
		return ;
	}
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	const float light0_pos[4] = {0, 1, 0.5, 0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetKeyCallback(window, view_control::key_callback);
	glfwSetCursorPosCallback(window, view_control::mouse_callback);
	glfwSetScrollCallback(window, view_control::scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

GLint GL_interface::glfw_initialized = 0;

GL_interface::~GL_interface()
{
	if (glfw_initialized)
	{
		glfwTerminate();
		glfw_initialized = false;
	}
}
