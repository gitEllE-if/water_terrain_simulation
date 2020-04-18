#version 120

attribute vec3 box_pos;

varying vec3 tex_coord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
	tex_coord = box_pos;
	vec4 pos = projection * view * vec4(box_pos, 1.0);
	gl_Position = pos.xyww;
//gl_Position = projection * view * vec4(box_pos, 1.0);
}  
