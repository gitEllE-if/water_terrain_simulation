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
