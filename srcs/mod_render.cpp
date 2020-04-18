#include "mod_render.hpp"
#include "mod_texture.hpp"
#include "mod_view_control.hpp"

visual_engine::visual_engine(size_t x_cells, size_t y_cells, float dx,
		int window_width, int window_height, std::vector<GLfloat> *surf_level):
        GL_interface(window_width, window_height), tex_offset(0.0),
		mesh(x_cells, y_cells, dx), 
        waterShaderProgram(SHAD_V_WATER, SHAD_F_WATER, PROG_WATER),
        surfaceShaderProgram(SHAD_V_SURFACE, SHAD_F_SURFACE, PROG_SURFACE),
		sky_box()
{
	mesh.gen_mesh_normal(surf_level);
	if (!tex_surface[0].load_texture2d(TEX_SAND) ||
		!tex_surface[1].load_texture2d(TEX_GRASS) ||
		!tex_surface[2].load_texture2d(TEX_ROCK) ||
		!tex_surface[3].load_texture2d(TEX_SNOW) ||
		!tex_normal[MOD_FLOOD].load_texture2d(DIR_FLOOD TEX_WATER_NORM) ||
		!tex_normal[MOD_RAIN].load_texture2d(DIR_RAIN TEX_WATER_NORM) ||
		!tex_normal[MOD_SNOW].load_texture2d(DIR_SNOW TEX_WATER_NORM) ||
		!tex_water[MOD_FLOOD].load_texture2d(DIR_FLOOD TEX_WATER) ||
		!tex_water[MOD_RAIN].load_texture2d(DIR_RAIN TEX_WATER) ||
		!tex_water[MOD_SNOW].load_texture2d(DIR_SNOW TEX_WATER))
	{
		std::cout << "error: load_texture_image fail" << std::endl;
		exit(1);
	}
}

visual_engine::~visual_engine()
{
    surfaceShaderProgram.deleteProgram();
    waterShaderProgram.deleteProgram();
    glDeleteBuffers(1, &waterHeightVBO);
    glDeleteBuffers(1, &surfaceLevelVBO);
}

void visual_engine::update_vertex_values(std::vector<GLfloat> *water_height,
											std::vector<GLfloat> *surface_level)
{
    static bool first_time = true;
    if (surface_level && first_time)
	{
        glGenBuffers(1, &surfaceLevelVBO);
        glBindBuffer(GL_ARRAY_BUFFER, surfaceLevelVBO);
        glBufferData(GL_ARRAY_BUFFER, surface_level->size() * sizeof(GLfloat),
										surface_level->data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat),
																	(GLvoid*)0);
        glEnableVertexAttribArray(1);
    }
    if (water_height)
	{
        if (first_time)
		{
			glGenBuffers(1, &waterHeightVBO);
        	glBindBuffer(GL_ARRAY_BUFFER, waterHeightVBO);
            glBufferData(GL_ARRAY_BUFFER, water_height->size() * sizeof(GLfloat),
										water_height->data(), GL_DYNAMIC_DRAW);
            glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat),
																	(GLvoid*)0);
            first_time = false;
            glEnableVertexAttribArray(3);
        }
        else
		{
			glBindBuffer(GL_ARRAY_BUFFER, waterHeightVBO);
			glBufferData(GL_ARRAY_BUFFER, water_height->size() * sizeof(GLfloat),
										water_height->data(), GL_DYNAMIC_DRAW);
		}
    }
}

void visual_engine::render()
{
	if (view_control::state.weather == MOD_SNOW)
		tex_offset = 0.0;
	tex_offset += 0.0001 * view_control::state.weather;
    glfwPollEvents();
    static GLfloat last_frame = glfwGetTime();
    GLfloat current_time = glfwGetTime();
    view_control::delta_time = current_time - last_frame;
    last_frame = current_time;
    view_control::do_camera_movement();
	view_control::set_mod_state();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 view = view_control::cam.get_view_matrix();
    glm::mat4 projection = glm::perspective(glm::radians(view_control::cam.zoom),
														win_ratio, 1.0f, 100.0f);
	glm::mat4 view1 = glm::mat4(glm::mat3(view_control::cam.get_view_matrix()));
	glm::vec3 camera_pos = view_control::cam.position;

    surfaceShaderProgram.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex_surface[0].texture2d);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex_surface[1].texture2d);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, tex_surface[2].texture2d);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, tex_surface[3].texture2d);
	glUniform1i(glGetUniformLocation(surfaceShaderProgram.getProgram(), "tex_sand"), 0);
	glUniform1i(glGetUniformLocation(surfaceShaderProgram.getProgram(), "tex_grass"), 1);
	glUniform1i(glGetUniformLocation(surfaceShaderProgram.getProgram(), "tex_rock"), 2);
	glUniform1i(glGetUniformLocation(surfaceShaderProgram.getProgram(), "tex_snow"), 3);
	glUniform1f(glGetUniformLocation(surfaceShaderProgram.getProgram(), "max_height"), SURF_HEIGHT);
    glUniformMatrix4fv(glGetUniformLocation(surfaceShaderProgram.getProgram(),
									"view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(surfaceShaderProgram.getProgram(),
						"projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glBindBuffer(GL_ARRAY_BUFFER, surfaceLevelVBO);
	mesh.draw(true);
	glUseProgram(0);
    waterShaderProgram.use();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_CUBE_MAP,
						sky_box.cubemap_texture[view_control::state.weather]);
	glUniform1i(glGetUniformLocation(waterShaderProgram.getProgram(), "skybox"), 4);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D,
						tex_normal[view_control::state.weather].texture2d);
	glUniform1i(glGetUniformLocation(waterShaderProgram.getProgram(),
														"tex_water_norm"), 5);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, tex_water[view_control::state.weather].texture2d);
	glUniform1i(glGetUniformLocation(waterShaderProgram.getProgram(), "tex_water"), 6);
	glUniform3fv(glGetUniformLocation(waterShaderProgram.getProgram(),
							"camera_pos"), 1, glm::value_ptr(camera_pos));
	glUniform1f(glGetUniformLocation(waterShaderProgram.getProgram(),
							"tex_offset"), tex_offset);
    glUniformMatrix4fv(glGetUniformLocation(waterShaderProgram.getProgram(),
									"view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(waterShaderProgram.getProgram(),
						"projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glBindBuffer(GL_ARRAY_BUFFER, waterHeightVBO);
	mesh.draw(false);
	glUseProgram(0);
	sky_box.draw(view1, projection);
    glfwSwapBuffers(window);
}

bool visual_engine::should_stop()
{
    return((bool)glfwWindowShouldClose(window));
}

bool visual_engine::start_simulation()
{
    return(view_control::state.run);
}
