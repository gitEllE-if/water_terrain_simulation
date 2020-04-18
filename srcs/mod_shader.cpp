#include "mod_shader.hpp"

shader::shader(GLchar const *vert_path, GLchar const *frag_path, int prog_type)
{
	std::ifstream vert_shader_file;
	std::ifstream frag_shader_file;
	vert_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	frag_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	std::string vert_shader_source;
	std::string frag_shader_source;
	try
	{
		vert_shader_file.open(vert_path);
		frag_shader_file.open(frag_path);
		std::stringstream vert_shader_stream;
		std::stringstream frag_shader_stream;
		vert_shader_stream << vert_shader_file.rdbuf();
		frag_shader_stream << frag_shader_file.rdbuf();
		vert_shader_source = vert_shader_stream.str();
		frag_shader_source = frag_shader_stream.str();
	}
    catch (std::ifstream::failure e)
	{
		std::cout << "error: shader - file_read_failure" << std::endl;
	}
	const GLchar* vert_shader_code = vert_shader_source.c_str();
	const GLchar* frag_shader_code = frag_shader_source.c_str();
	GLuint	vert_obj;
	GLuint	frag_obj;
	GLint	success;
	GLchar	info_log[512];
	vert_obj = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vert_obj, 1, &vert_shader_code, NULL);
	glCompileShader(vert_obj);
	glGetShaderiv(vert_obj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vert_obj, 512, NULL, info_log);
		std::cout << "error: shader - compile_fail\n" << info_log << std::endl;
	}
	frag_obj = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(frag_obj, 1, &frag_shader_code, NULL);
	glCompileShader(frag_obj);
	glGetShaderiv(frag_obj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(frag_obj, 512, NULL, info_log);
		std::cout << "error: shader - compile_fail\n" << info_log << std::endl;
	}
	program = glCreateProgram();
	glAttachShader(program, vert_obj);
	glAttachShader(program, frag_obj);
	if (prog_type == 1)
	{
		glBindAttribLocation(program, 0, "pos_xy");
		glBindAttribLocation(program, 1, "surf_height");
		glBindAttribLocation(program, 3, "pos_z");
	}
	else if (prog_type == 2)
	{
		glBindAttribLocation(program, 0, "pos_xy");
		glBindAttribLocation(program, 1, "pos_z");
		glBindAttribLocation(program, 2, "norm");
	}
	else if (prog_type == 4)
		glBindAttribLocation(program, 4, "box_pos");
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, info_log);
		std::cout << "error: shader - link_fail\n" << info_log << std::endl;
	}
	glDeleteShader(vert_obj);
	glDeleteShader(frag_obj);
}

void shader::deleteProgram()
{
    glDeleteProgram(program);
}

void	shader::use()
{
    glUseProgram(program);
}

GLuint	shader::getProgram()
{
    return (program);
}
