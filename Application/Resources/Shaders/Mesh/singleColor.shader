#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;

out vec4 color;

uniform mat4 u_MVP;
uniform vec4 u_color = vec4(1.0f);

void main()
{
	gl_Position = u_MVP * aPos;
	color = u_color;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec4 color;

void main()
{
	FragColor = color;
}
