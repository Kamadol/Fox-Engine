#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "Vector4.hpp"

class Shader
{
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform4f(const char* uniformName, Vector4 v);

private:
	size_t compile(size_t type, const std::string source);
	size_t createShader(const std::string vert, const std::string frag);

private:
	size_t id;

};

#endif
