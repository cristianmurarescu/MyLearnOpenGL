#version 330 core

out vec4 FragColor;

in vec4 ourPos;
in vec3 ourColor;

void main()
{
   FragColor = ourPos;
}