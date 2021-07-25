#version 330 core

layout(location = 0) in vec2 position;
layout(location = 1) in uint something;
layout(location = 2) in vec4 color;

out vec4 ourColor;

void main()
{
	gl_Position = vec4(position.xy, 0.0f, 1.0f);
    ourColor = color;
}
