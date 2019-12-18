#version 120

varying vec3 tex_coord;

uniform samplerCube skybox;

void main()
{    
    gl_FragColor = textureCube(skybox, tex_coord);
}
