/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_shader.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 05:26:19 by laleta            #+#    #+#             */
/*   Updated: 2019/12/09 05:26:20 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"

class shader
{
	public:
    	shader(GLchar const * vertexPath, GLchar const * fragmentPath,
																int prog_type);
		void	deleteProgram();
		void	use();
		GLuint	getProgram();
	private:
		GLuint	program;
};
