#ifndef SIMPLE_RENDERER_2D_HPP
#define SIMPLE_RENDERER_2D_HPP

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Buffer.hpp"
#include "Sprite.hpp"
#include "Shader.hpp"

class SimpleRenderer2D
{
public:
	SimpleRenderer2D();

	void submit(const Sprite& sprite, Shader& shader, const Mat4x4& camera = Mat4x4::identity());

private:
	VertexArray m_vao;
	std::unique_ptr<Buffer> m_quadData;
	size_t m_indices[6];
	std::unique_ptr<IndexBuffer> m_ibo;

};

#endif
