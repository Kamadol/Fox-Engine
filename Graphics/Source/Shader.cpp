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
	}
	else
		std::cout << vertPath << " cannot be loaded" << std::endl;
	file.close();

	file.open(fragPath);
	if (file.good())
	{
		fragmentSource << file.rdbuf();
	}
	else
		std::cout << fragPath << " cannot be loaded" << std::endl;
	
	m_id = createShader(vertexSource.str(), fragmentSource.str());
}
Shader::Shader(const char* shaderPath)
{
	std::ifstream file;
	file.open(shaderPath);
	if (!file.good())
		std::cout << shaderPath << " cannot be loaded" << std::endl;
	std::string line;

	std::string version;
	std::string vertex;
	std::string fragment;
	std::string geometry;

	while (std::getline(file, line))
	{
		if (line.find("#version") != std::string::npos)
		{
			version = line + "\n";
			break;
		}
	}
	
	size_t shaderWrite = 0;
	while (std::getline(file, line))
	{
		if (line.find("VERTEX_SHADER") != std::string::npos)
		{
			vertex += version;
			shaderWrite = 1;
			continue;
		}
		else if (line.find("FRAGMENT_SHADER") != std::string::npos)
		{
			fragment += version;
			shaderWrite = 2;
			continue;
		}
		else if (line.find("GEOMETRY_SHADER") != std::string::npos)
		{
			geometry += version;
			shaderWrite = 3;
			continue;
		}

		if (shaderWrite == 1)
			vertex += line + "\n";
		else if (shaderWrite == 2)
			fragment += line + "\n";
		else if (shaderWrite == 3)
			geometry += line + "\n";
	}

	if(geometry.empty())
		m_id = createShader(vertex, fragment);
	else
		m_id = createShader(vertex, fragment, geometry);
}
Shader::~Shader()
{
	glDeleteProgram(m_id);
}

void Shader::bind() const
{
	glUseProgram(m_id);
}
void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setUniform1i(const char* uniformName, int v)
{
	glUniform1i(getLocation(uniformName), v);
}
void Shader::setUniform1f(const char* uniformName, float v)
{
	glUniform1f(getLocation(uniformName), v);
}
void Shader::setUniform2f(const char* uniformName, Vector2 v)
{
	glUniform2f(getLocation(uniformName), v.x, v.y);
}
void Shader::setUniform3f(const char* uniformName, Vector3 v)
{
	glUniform3f(getLocation(uniformName), v.x, v.y, v.z);
}
void Shader::setUniform4f(const char* uniformName, Vector4 v)
{
	glUniform4f(getLocation(uniformName), v.x, v.y, v.z, v.w);
}
void Shader::setUniformMat4(const char* uniformName, const Mat4x4& m)
{
	glUniformMatrix4fv(getLocation(uniformName), 1, GL_FALSE, &m(0, 0));
}
void Shader::setUniformMaterial(const char* uniformName, const Material& material)
{
	std::string name(uniformName);

	Vector3 amb = material.m_ambient;
	Vector3 dif = material.m_diffuse;
	Vector3 spe = material.m_specular;

	glUniform1f(glGetUniformLocation(m_id, (name + ".shininess").c_str()), material.m_shininess);
	glUniform3f(glGetUniformLocation(m_id, (name + ".ambient"  ).c_str()), amb.x, amb.y, amb.z);
	glUniform3f(glGetUniformLocation(m_id, (name + ".diffuse"  ).c_str()), dif.x, dif.y, dif.z);
	glUniform3f(glGetUniformLocation(m_id, (name + ".specular" ).c_str()), spe.x, spe.y, spe.z);

	//glUniform1f(getLocation((name + ".shininess").c_str()), material.m_shininess);
	//glUniform3f(getLocation((name + ".ambient"  ).c_str()), amb.x, amb.y, amb.z);
	//glUniform3f(getLocation((name + ".diffuse"  ).c_str()), dif.x, dif.y, dif.z);
	//glUniform3f(getLocation((name + ".specular" ).c_str()), spe.x, spe.y, spe.z);
}

int Shader::getLocation(const char* name)
{
	if (m_locations.find(name) != m_locations.end())
	{
		return m_locations[name];
	}
	else
	{
		int loc = glGetUniformLocation(m_id, name);
		if (loc != -1)
		{
			m_locations[name] = loc;
			return loc;
		}
		else
		{
			//std::cout << "Shader uniform " << name << " doesn't exist" << std::endl;
		}
	}
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
size_t Shader::createShader(const std::string& vert, const std::string& frag, const std::string& geo)
{
	size_t program = glCreateProgram();
	size_t vs = compile(GL_VERTEX_SHADER, vert);
	size_t fs = compile(GL_FRAGMENT_SHADER, frag);
	size_t gs = compile(GL_GEOMETRY_SHADER, geo);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glAttachShader(program, gs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteShader(gs);

	return program;
}
size_t Shader::createShader(const std::string& vert, const std::string& frag)
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
