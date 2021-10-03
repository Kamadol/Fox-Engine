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
Material Material::pearl()
{
	Vector3 ambient(0.25f, 0.20725f, 0.20725f);
	Vector3 diffuse(1.0f, 0.829f, 0.829f);
	Vector3 specular(0.296648f, 0.296648f, 0.296648f);
	float shininess = 0.088f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::turquoise()
{
	Vector3 ambient(0.1f, 0.18725f, 0.1745f);
	Vector3 diffuse(0.396f, 0.74151f, 0.69102f);
	Vector3 specular(0.297254f, 0.30829f, 0.306678f);
	float shininess = 0.1f * 128.0f;

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
Material Material::brass()
{
	Vector3 ambient(0.329412f, 0.223529f, 0.027451f);
	Vector3 diffuse(0.780392f, 0.568627f, 0.113725f);
	Vector3 specular(0.992157f, 0.941176f, 0.807843f);
	float shininess = 0.21794872f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::bronze()
{
	Vector3 ambient(0.2125f, 0.1275f, 0.054f);
	Vector3 diffuse(0.714f, 0.4284f, 0.18144f);
	Vector3 specular(0.393548f, 0.271906f, 0.166721f);
	float shininess = 0.2f * 128.0f;

	return Material(ambient, diffuse, specular, shininess);
}
Material Material::copper()
{
	Vector3 ambient(0.19125f, 0.0735f, 0.0225f);
	Vector3 diffuse(0.7038f, 0.27048f, 0.0828f);
	Vector3 specular(0.256777f, 0.137622f, 0.086014f);
	float shininess = 0.1f * 128.0f;

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
