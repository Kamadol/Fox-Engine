#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Vector3.hpp"

struct Material
{
	Material(Vector3 ambient, Vector3 diffuse, Vector3 specular, float shininess);

	static Material emerald();
	static Material jade();
	static Material obsidian();
	static Material pearl();
	static Material turquoise();
	static Material ruby();
	static Material chrome();
	static Material silver();
	static Material gold();
	static Material brass();
	static Material bronze();
	static Material copper();
	static Material greenPlastic();
	static Material redRubber();

	Vector3 m_ambient;
	Vector3 m_diffuse;
	Vector3 m_specular;
	float m_shininess;

};

#endif
