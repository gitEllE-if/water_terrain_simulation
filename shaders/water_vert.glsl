#version 120

attribute vec2	pos_xy;
attribute float	pos_z;
attribute float	surf_height;

uniform mat4	view;
uniform mat4	projection;

varying float s_height;
varying float w_height;
varying vec3	position;
//varying vec3	normal;

void main()
{
	position = vec3(pos_xy.x, pos_z, pos_xy.y);
//	normal = vec3(0,1,0);

	gl_Position = projection * view * vec4(pos_xy.x, pos_z, pos_xy.y, 1.0f);
	s_height = surf_height;
	w_height = pos_z;
}
