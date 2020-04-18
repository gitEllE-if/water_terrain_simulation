#include "mod_texture.hpp"

bool	texture_2d::load_texture2d(std::string const file_name)
{
	sf::Image image;

	if (!image.loadFromFile(file_name))
		return (false);
	image.flipVertically();
	glGenTextures(1, &texture2d);
	glBindTexture(GL_TEXTURE_2D, texture2d);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x,
		image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
													GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	return (true);
}

texture_2d::~texture_2d()
{
    glDeleteTextures(1, &texture2d);
}
