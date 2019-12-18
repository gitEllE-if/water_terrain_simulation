/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_mesh.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 03:23:55 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 05:38:27 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"

class mesh
{
	public:
		mesh(size_t x_cells, size_t y_cells, float dx);
		~mesh();
		void	gen_mesh_normal(std::vector<GLfloat> *height);
		void	draw(bool need_normal);
	private:
		GLuint					row;
		GLuint					col;
		GLuint					xyVBO;
		GLuint					normalVBO;
		GLuint					EBO;
		std::vector<GLfloat>	xy;
		std::vector<GLuint>		indices;
};
