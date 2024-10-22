#pragma once

#include "mod1.hpp"
#include "mod_shader.hpp"
#include "mod_view_control.hpp"

class skybox
{
	public:
		skybox();
		~skybox();
		GLuint cubemap_texture[3];
		void draw(const glm::mat4& view, const glm::mat4& projection);
	private:
		GLuint VBO;
		shader skybox_shader_prog;
		GLuint load_cubemap(std::string weather, std::vector<std::string> faces);
};
