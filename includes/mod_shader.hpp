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
