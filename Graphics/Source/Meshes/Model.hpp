#ifndef MODEL_HPP
#define MODEL_HPP

#include "Mesh.hpp"

class Model
{
public:
	Model(const char* filename);

private:
	std::vector<Mesh> m_meshes;

};

#endif
