#version 330 core 
layout (location = 0) in vec3 aPos;
out vec3 cubeTexCoords;
uniform mat4 projectionTransform;
uniform mat4 viewTransform;
void main()
{
    cubeTexCoords = -aPos;
    vec4 pos = projectionTransform * viewTransform * vec4(aPos, 1.0);
    gl_Position = pos.xyww;
}
