#ifndef MODEL_HPP
#define MODEL_HPP

#include "TransformableCP.hpp"
#include "Mesh.hpp"

class Model : public TransformableCP
{
public:
	Model(const char* filename);

private:
	std::vector<Mesh> m_meshes;

};

#endif
