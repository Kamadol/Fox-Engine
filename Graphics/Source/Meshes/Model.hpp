#ifndef MODEL_HPP
#define MODEL_HPP

#include "TransformableCP.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"

class Model : public TransformableCP
{
public:
	Model(const char* filename);

	void draw(const Shader& shader) const;

private:
	std::vector<Mesh> m_meshes;

};

#endif
