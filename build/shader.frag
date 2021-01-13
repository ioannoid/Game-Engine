#version 330 core

out vec4 FragColor;

in vec4 fcolor;
in vec2 textureCoords;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, textureCoords);
} 