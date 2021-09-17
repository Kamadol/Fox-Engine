#include "Material.hpp"

Material::Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, float shininess)
	:m_ambient(ambient), m_diffuse(diffuse), m_specular(specular), m_shininess(shininess)
{

}

Material Material::emerald()
{
	Vector3 ambient(0.0215f, 0.1745f, 0.0215f);
	Vector3 diffuse(0.07568f, 0.61424f, 0.07568f);
	Vector3 specular(0.633f, 0.727811f, 0.633f);
	float shininess = 0.6f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::obsidian()
{
	Vector3 ambient(0.05375f, 0.05f, 0.06625f);
	Vector3 diffuse(0.18275f, 0.17f, 0.22525f);
	Vector3 specular(0.332741f, 0.328634f, 0.346435f);
	float shininess = 0.3f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::ruby()
{
	Vector3 ambient(0.1745f, 0.01175f, 0.01175f);
	Vector3 diffuse(0.61424f, 0.04136f, 0.04136f);
	Vector3 specular(0.727811f, 0.626959f, 0.626959f);
	float shininess = 0.6f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::chrome()
{
	Vector3 ambient(0.25f);
	Vector3 diffuse(0.4f);
	Vector3 specular(0.774597f);
	float shininess = 0.6f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::silver()
{
	Vector3 ambient(0.19225f);
	Vector3 diffuse(0.50754f);
	Vector3 specular(0.508273f);
	float shininess = 0.4f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::gold()
{
	Vector3 ambient(0.24725f, 0.1995f, 0.0745f);
	Vector3 diffuse(0.75164f, 0.60648f, 0.22648f);
	Vector3 specular(0.628281f, 0.555802f, 0.366065f);
	float shininess = 0.4f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::greenPlastic()
{
	Vector3 ambient(0.0f);
	Vector3 diffuse(0.1f, 0.35f, 0.1f);
	Vector3 specular(0.45f, 0.55f, 0.45f);
	float shininess = 0.25f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::redRubber()
{
	Vector3 ambient(0.05f, 0.0f, 0.0f);
	Vector3 diffuse(0.5f, 0.4f, 0.4f);
	Vector3 specular(0.7f, 0.04f, 0.04f);
	float shininess = 0.078125f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
