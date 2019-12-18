#version 120

varying vec3		normal;
varying vec2		tex_coord;
varying float		height;
uniform sampler2D	tex_sand;
uniform sampler2D	tex_grass;
uniform sampler2D	tex_rock;
uniform sampler2D	tex_snow;
uniform float		max_height; 

vec4 calc_tex_mix(float height, float min, float max, vec4 tex1, vec4 tex2)
{
	float ratio = (height - min) / (max - min);
	return (mix(tex1, tex2, ratio));
}

void main()
{
	float max_h = max_height / 100.0;
	float sandGrassFrom = 0.02;
	float sandGrassTo = max_h * 5.0;
	float grassRockFrom = max_h * 10.0; 
	float grassRockTo = max_h * 50.0;
	float rockSnowFrom = max_h * 75.0;
	float rockSnowTo = max_h * 95.0;
	vec4 color;
	vec4 sand = texture2D(tex_sand, tex_coord / 3.0);
	vec4 grass = texture2D(tex_grass, tex_coord / 5.0);
	vec4 rock = texture2D(tex_rock, tex_coord / 2.0);
	vec4 snow = texture2D(tex_snow, tex_coord);
	if (height < sandGrassFrom)
		color = sand;
	else if (height < sandGrassTo)
		color = calc_tex_mix(height, sandGrassFrom, sandGrassTo, sand, grass);
	else if (height < grassRockFrom)
		color = grass;
	else if (height < grassRockTo)
		color = calc_tex_mix(height, grassRockFrom, grassRockTo, grass, rock);
	else if (height < rockSnowFrom)
		color = rock;
	else if (height < rockSnowTo)
		color = calc_tex_mix(height, rockSnowFrom, rockSnowTo, rock, snow);
	else
		color = snow;
	vec3 light_dir = normalize(vec3(gl_LightSource[0].position));
	float intens = max(dot(light_dir, normal), 0.1);
	gl_FragColor = intens * color;
}
