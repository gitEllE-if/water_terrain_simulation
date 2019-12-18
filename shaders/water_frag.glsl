#version 120

uniform samplerCube	skybox;
uniform sampler2D	tex_water_norm;
uniform sampler2D	tex_water;
uniform vec3		camera_pos;
uniform float		tex_offset;
 
varying float		s_height;
varying float		w_height;
varying vec3		position;

void main()
{
	float k_mix;
	float k_alpha;
	float water = 10 * clamp(w_height - s_height, 0.0, 0.1);
	vec3 light_dir = normalize(vec3(gl_LightSource[0].position));
	vec2 tex_coord = vec2(position.x, position.z);
	vec3 normal = texture2D(tex_water_norm, tex_coord + tex_offset).rgb;
	normal = normalize(normal);
	normal = vec3(-normal.x, normal.z, normal.y);
	float intens = max(dot(light_dir, normal), 0.1);

	vec3 I = normalize(position - camera_pos);
	vec3 R = reflect(I, normal);

	if (tex_offset == 0.0)
	{
		k_mix = 0.8;
		k_alpha = 1.0;
	}
	else
	{
		k_mix = 0.3;
		k_alpha = 0.9;
	}
	vec3 color = mix(textureCube(skybox, R), texture2D(tex_water, tex_coord + tex_offset), k_mix).rgb;
	gl_FragColor = intens * vec4(color, clamp(sqrt(water), 0.0, k_alpha));
}
