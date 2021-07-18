#include "Shader.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

#include "GL/glew.h"

Shader::Shader(const char* vertPath, const char* fragPath)
{
	std::ifstream file;
	std::stringstream vertexSource;
	std::stringstream fragmentSource;

	file.open(vertPath);
	if (file.good())
	{
		vertexSource << file.rdbuf();
		//std::cout << vertexSource.str() << std::endl;
	}
	else
		std::cout << vertPath << " cannot be loaded" << std::endl;
	file.close();

	file.open(fragPath);
	if (file.good())
	{
		fragmentSource << file.rdbuf();
		//std::cout << fragmentSource.str() << std::endl;
	}
	else
		std::cout << fragPath << " cannot be loaded" << std::endl;
	
	id = createShader(vertexSource.str(), fragmentSource.str());
}
Shader::~Shader()
{
	glDeleteProgram(id);
}

void Shader::bind() const
{
	glUseProgram(id);
}
void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform4f(const char* uniformName, Vector4 v)
{
	glUniform4f(glGetUniformLocation(id, uniformName), v.x, v.y, v.z, v.w);
}

size_t Shader::compile(size_t type, const std::string source)
{
	size_t id = glCreateShader(type);
	const char* s = source.c_str();
	glShaderSource(id, 1, &s, nullptr);
	glCompileShader(id);

	//error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];

		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile shader!" << std::endl;
		std::cout << message << std::endl;
		delete[] message;
		
		glDeleteShader(id);
		
		return 0;
	}

	return id;
}

size_t Shader::createShader(const std::string vert, const std::string frag)
{
	size_t program = glCreateProgram();
	size_t vs = compile(GL_VERTEX_SHADER, vert);
	size_t fs = compile(GL_FRAGMENT_SHADER, frag);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	
	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}