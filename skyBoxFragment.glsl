#version 330 core
out vec4 fragmentColor; 
in vec3 cubeTexCoords;
uniform samplerCube skybox;

void main()
{
	fragmentColor = texture(skybox, cubeTexCoords);
}