#version 330 core

VERTEX_SHADER
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	gl_Position = u_MVP * aPos;
	normal = mat3(transpose(inverse(u_model))) * aNormal;
}

FRAGMENT_SHADER
out vec4 FragColor;

in vec3 normal;

void main()
{
	FragColor = vec4(normal, 1.0);
}
