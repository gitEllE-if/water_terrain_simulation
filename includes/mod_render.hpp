/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_render.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 22:55:06 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 05:31:26 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "mod1.hpp"
#include "mod_GL_interface.hpp"
#include "mod_shader.hpp"
#include "mod_camera.hpp"
#include "mod_texture.hpp"
#include "mod_skybox.hpp"
#include "mod_mesh.hpp"

class visual_engine: public GL_interface
{
	public:
		visual_engine(size_t x_cells, size_t y_cells, float dx,
		int win_width = 800, int win_height = 600,
							std::vector<GLfloat> *surf_height = nullptr);
		~visual_engine();
		void update_vertex_values(std::vector<GLfloat> *water_height = nullptr,
								std::vector<GLfloat> *surface_level = nullptr);
		bool	start_simulation();
		void	render();
		bool	should_stop();
		float	tex_offset;
	private:
		GLuint					waterHeightVBO;
		GLuint					surfaceLevelVBO;
		mesh					mesh;
		shader					waterShaderProgram;
		shader					surfaceShaderProgram;
		skybox					sky_box;
		texture_2d				tex_surface[4];
//		texture_2d				texture2;
//		texture_2d				texture3;
//		texture_2d				texture4;
		texture_2d				tex_normal[3];
		texture_2d				tex_water[3];
};
