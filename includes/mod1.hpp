#pragma once

#define GLEW_STATIC
#define GLEW_NO_GLU

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stddef.h>
#include <cmath>
#include <vector>
#include <cassert>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <boost/filesystem.hpp>
 
#define GRID_HEIGHT		100
#define GRID_WIDTH		100
#define WIN_HEIGHT		800
#define WIN_WIDTH		800
#define TEX_SIZE		512
#define SURF_HEIGHT		2.0
#define MOD_GRAVITY		9.8
#define MOD_FRICTION	0.8
#define MOD_FLOW_SIZE	0.5
#define MOD_DX			0.1
#define	MOD_DT			0.001
#define	MOD_DF			0.01
#define MOD_FLOOD		2
#define MOD_RAIN		1
#define MOD_SNOW		0
#define PROG_WATER		1
#define PROG_SURFACE	2
#define PROG_SKYBOX		4
#define YAW				-90.0f
#define PITCH			0.0f
#define SPEED			3.0f
#define SENSITIVTY		0.25f
#define ZOOM			45.0f
#define DIR_FLOOD		"resources/img/flood/"
#define DIR_RAIN		"resources/img/rain/"
#define	DIR_SNOW		"resources/img/snow/"
#define TEX_GRASS		"resources/img/grass1.tga"
#define TEX_SNOW		"resources/img/snow1.tga"
#define TEX_SAND		"resources/img/sand1.tga"
#define TEX_ROCK		"resources/img/rock1.tga"
#define TEX_WATER_NORM	"tex_normal.jpg"
#define TEX_WATER		"tex_water.jpg"
#define SKYBOX_RIGHT	"mir_rt.tga"
#define SKYBOX_LEFT		"mir_lf.tga"
#define SKYBOX_TOP		"mir_up.tga"
#define SKYBOX_DOWN		"mir_dn.tga"
#define SKYBOX_FRONT	"mir_bk.tga"
#define SKYBOX_BACK		"mir_ft.tga"
#define AUDIO_WATER		"audio.ogg"
#define SHAD_V_WATER	"shaders/water_vert.glsl"
#define SHAD_F_WATER	"shaders/water_frag.glsl"
#define SHAD_V_SURFACE	"shaders/surface_vert.glsl"
#define SHAD_F_SURFACE	"shaders/surface_frag.glsl"
#define SHAD_V_SKYBOX	"shaders/skybox_vert.glsl"
#define SHAD_F_SKYBOX	"shaders/skybox_frag.glsl"
