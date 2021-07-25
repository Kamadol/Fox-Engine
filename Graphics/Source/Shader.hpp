#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Mat4x4.hpp"

class Shader
{
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1f(const char* uniformName, float v);
	void setUniform2f(const char* uniformName, Vector2 v);
	void setUniform3f(const char* uniformName, Vector3 v);
	void setUniform4f(const char* uniformName, Vector4 v);
	void setUniformMat4(const char* uniformName, const Mat4x4 &v);

private:
	size_t compile(size_t type, const std::string source);
	size_t createShader(const std::string vert, const std::string frag);

private:
	size_t id;

};

#endif
