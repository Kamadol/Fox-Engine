#version 330 core

out vec4 color;

uniform vec4 u_Color = vec4(1.0, 0.0, 0.0, 1.0);

void main()
{
	color = u_Color;
}