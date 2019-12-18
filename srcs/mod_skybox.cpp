/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_skybox.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laleta <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 23:08:31 by laleta            #+#    #+#             */
/*   Updated: 2019/11/29 04:49:19 by laleta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mod_skybox.hpp"

skybox::skybox():
	skybox_shader_prog(SHAD_V_SKYBOX, SHAD_F_SKYBOX, PROG_SKYBOX)
{
	GLfloat skybox_vertex[108] = 
	{
		-1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f
	};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skybox_vertex), &skybox_vertex,
																GL_STATIC_DRAW);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
																	(void*)0);
	std::vector<std::string> faces
	{
		SKYBOX_RIGHT, SKYBOX_LEFT, SKYBOX_TOP,
		SKYBOX_DOWN, SKYBOX_FRONT, SKYBOX_BACK
	};
	cubemap_texture[MOD_SNOW] = load_cubemap(DIR_SNOW, faces);
	cubemap_texture[MOD_RAIN] = load_cubemap(DIR_RAIN, faces);
	cubemap_texture[MOD_FLOOD] = load_cubemap(DIR_FLOOD, faces);
}

skybox::~skybox()
{
	skybox_shader_prog.deleteProgram();
	glDeleteBuffers(1, &VBO);
	glDeleteTextures(3, cubemap_texture);
}

void	skybox::draw(const glm::mat4& view, const glm::mat4& projection)
{
	glDepthFunc(GL_LEQUAL);
	skybox_shader_prog.use();
	glUniformMatrix4fv(glGetUniformLocation(skybox_shader_prog.getProgram(),
									"view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skybox_shader_prog.getProgram(),
						"projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_CUBE_MAP,
								cubemap_texture[view_control::state.weather]);
	glUniform1i(glGetUniformLocation(skybox_shader_prog.getProgram(), "skybox"),
																			4);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glUseProgram(0);
	glDepthFunc(GL_LESS); 
}

GLuint skybox::load_cubemap(std::string weather, std::vector<std::string> faces)
{
	GLuint		texture;
	sf::Image	image[6];

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	for (uint8_t i = 0; i < faces.size(); i++)
	{
		if(image[i].loadFromFile(weather + faces[i].c_str()))
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
			image[i].getSize().x, image[i].getSize().y, 0, GL_RGBA,
									GL_UNSIGNED_BYTE, image[i].getPixelsPtr());
		}
		else
			std::cout << "error: image_load_fail " << faces[i].c_str();
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return (texture);
}
