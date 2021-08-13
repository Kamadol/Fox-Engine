#version 330 core
layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 u_MVP;
uniform mat4 u_model;

void main()
{
	gl_Position = u_MVP * aPos;
	texCoord = aTexCoord;
	fragPos = vec3(u_model * aPos);
	normal = mat3(transpose(inverse(u_model))) * aNormal;
}
