#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>

#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Mat4x4.hpp"
#include "Meshes/Material.hpp"

class Shader
{
public:
	Shader(const char* vertPath, const char* fragPath);
	Shader(const char* shaderPath);
	~Shader();

	void bind() const;
	void unbind() const;

	void setUniform1i(const char* uniformName, int v) const;
	void setUniform1f(const char* uniformName, float v) const;
	void setUniform2f(const char* uniformName, Vector2 v) const;
	void setUniform3f(const char* uniformName, Vector3 v) const;
	void setUniform4f(const char* uniformName, Vector4 v) const;
	void setUniformMat4(const char* uniformName, const Mat4x4& m) const;
	void setUniformMaterial(const char* uniformName, const Material& material) const;

private:
	int getLocation(const char* name) const;
	unsigned int compile(unsigned int type, const std::string source);
	unsigned int createShader(const std::string& vert, const std::string& frag, const std::string& geo);
	unsigned int createShader(const std::string& vert, const std::string& frag);

private:
	unsigned int m_id;
	mutable std::unordered_map<const char*, int> m_locations;
};

#endif
