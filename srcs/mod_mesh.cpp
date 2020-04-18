#include "mod_mesh.hpp"

mesh::mesh(size_t x_cells, size_t y_cells, float dx):
	row(x_cells), col(y_cells)
{
	xy.resize(2 * x_cells * y_cells);
	for (size_t x = 0, idx = 0; x < x_cells; ++x)
	{
		for (size_t y = 0; y < y_cells; ++y)
		{
			xy[idx++] = x * dx;
			xy[idx++] = y * dx;
		}
	}
	indices.resize(2 * (x_cells - 1) * y_cells);
	for (size_t x = 0, vertex = 0; x < x_cells - 1; ++x)
	{
		for (size_t y = 0; y < y_cells; ++y)
		{
			indices[vertex++] = x * y_cells + y;
			indices[vertex++] = (x + 1) * y_cells + y;
		}
	}
	glGenBuffers(1, &xyVBO);
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ARRAY_BUFFER, xyVBO);
	glBufferData(GL_ARRAY_BUFFER, xy.size() * sizeof(GLfloat), xy.data(),
																GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat),
																	(GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),
												indices.data(), GL_STATIC_DRAW);
}

mesh::~mesh()
{
	glDeleteBuffers(1, &xyVBO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &normalVBO);
}

void	mesh::gen_mesh_normal(std::vector<GLfloat> *height)
{
	std::vector<GLfloat> mesh_normal(3 * row * col, 0.0);
	glm::vec3 vecs[3];

	for (size_t i = 0; i < (2 * (row - 1) * col); i++)
	{
		for (int8_t k = 0; k < 3; k++)
		{
			vecs[k].x = xy[2 * indices[i + k]];
			vecs[k].y = height->data()[indices[i + k]];
			vecs[k].z = xy[2 * indices[i + k] + 1];
		}
		glm::vec3 e1 = vecs[0] - vecs[1];
		glm::vec3 e2 = vecs[2] - vecs[1];
		glm::vec3 n = glm::cross(e1, e2);
		for (int8_t k = 0; k < 3; k++)
		{
			mesh_normal[3 * indices[i + k]] += fabs(n.x);
			mesh_normal[3 * indices[i + k] + 1] += fabs(n.y);
			mesh_normal[3 * indices[i + k] + 2] += fabs(n.z);
		}
	}
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, mesh_normal.size() * sizeof(GLfloat),
										mesh_normal.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
																	(GLvoid*)0);
	glEnableVertexAttribArray(2);
}

void	mesh::draw(bool need_normal)
{
	glBindBuffer(GL_ARRAY_BUFFER, xyVBO);
	if (need_normal)
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	for (GLuint r = 0; r < row - 1; ++r)
		glDrawElements(GL_TRIANGLE_STRIP, col * 2, GL_UNSIGNED_INT,
									(GLvoid*)(r * col * 2 * sizeof(GLuint)));
}
