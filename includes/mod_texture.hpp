#pragma once

#include "mod1.hpp"

class texture_2d
{
	public:
		~texture_2d();
		GLuint	texture2d;
		bool	load_texture2d(std::string const file_name);
};
