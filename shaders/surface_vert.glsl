#version 120

attribute vec2	pos_xy;
attribute float	pos_z;
attribute vec3	norm;

uniform mat4	view;
uniform mat4	projection;

varying vec3	normal;
varying vec2	tex_coord;
varying float	height;

void main()
{
//	normal = (projection * view * vec4(normalize(norm), 0.0)).xyz;
	normal = normalize(norm);
	gl_Position = projection * view * vec4(pos_xy.x, pos_z, pos_xy.y, 1.0f);
	tex_coord = pos_xy;
	height = pos_z;
}
