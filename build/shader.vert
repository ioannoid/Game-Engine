#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec4 vcolor;
layout (location = 2) in vec2 uvs;

out vec4 fcolor;
out vec2 textureCoords;

void main()
{
    gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
    fcolor = vcolor;
    textureCoords = uvs;
}