/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_GL_interface.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:42:19 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 00:11:02 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
