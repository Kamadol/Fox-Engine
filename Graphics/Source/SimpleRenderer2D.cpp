#include "SimpleRenderer2D.hpp"

#include "GL/glew.h"

#include "Buffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

SimpleRenderer2D::SimpleRenderer2D()
{
    m_indices[0] = 0;
    m_indices[1] = 1;
    m_indices[2] = 2;
    m_indices[3] = 0;
    m_indices[4] = 2;
    m_indices[5] = 3;

    m_vao.bind();
    m_quadData.reset(new Buffer(0, 4 * sizeof(SpriteVertex)));
    m_ibo.reset(new IndexBuffer(m_indices, 6));

    VertexLayout layout;
    layout.push<float>(3);
    layout.push<float>(4);
    layout.push<float>(2);
    m_vao.useLayout(layout);

    m_vao.unbind();
}

void SimpleRenderer2D::submit(const Sprite& sprite, Shader& shader, const Mat4x4& camera)
{
    shader.setUniformMat4("u_MVP", camera * sprite.getTransform());

    Vector3 position = sprite.getPosition();
    Vector2 size = sprite.getSize() * 0.5f;

    SpriteVertex quad[4] =
    {
        SpriteVertex(Vector3( size.x,  size.y, 0.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector2(1.0f, 1.0f)),
        SpriteVertex(Vector3(-size.x,  size.y, 0.0f), Vector4(0.0f, 1.0f, 0.0f, 1.0f), Vector2(0.0f, 1.0f)),
        SpriteVertex(Vector3(-size.x, -size.y, 0.0f), Vector4(0.0f, 0.0f, 1.0f, 1.0f), Vector2(0.0f, 0.0f)),
        SpriteVertex(Vector3( size.x, -size.y, 0.0f), Vector4(1.0f, 1.0f, 0.0f, 1.0f), Vector2(1.0f, 0.0f))
    };

    m_vao.bind();
    //m_quadData->bind();
    //m_ibo->bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(SpriteVertex), quad);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    //m_quadData->unbind();
    //m_ibo->unbind();
    m_vao.unbind();
}
