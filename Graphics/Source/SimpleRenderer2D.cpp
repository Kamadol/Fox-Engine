#include "SimpleRenderer2D.hpp"

#include "GL/glew.h"

#include "Buffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"

SimpleRenderer2D::SimpleRenderer2D()
{

}

void SimpleRenderer2D::submit(const Sprite& sprite)
{
    Vector3 position = sprite.getPosition();
    Vector2 size = sprite.getSize();

    SpriteVertex triangle[4] =
    {
        SpriteVertex(Vector3( size.x, size.y, 0.0f) + position, Vector4(1.0f, 0.0f, 0.0f, 1.0f)),
        SpriteVertex(Vector3(-size.x, size.y, 0.0f) + position, Vector4(0.0f, 1.0f, 0.0f, 1.0f)),
        SpriteVertex(Vector3(-size.x,-size.y, 0.0f) + position, Vector4(0.0f, 0.0f, 1.0f, 1.0f)),
        SpriteVertex(Vector3( size.x,-size.y, 0.0f) + position, Vector4(1.0f, 1.0f, 0.0f, 1.0f)),
    };

    size_t indices[6] =
    {
        0, 1, 2,
        0, 2, 3
    };

    VertexArray vao;
    vao.bind();

    Buffer buffer(triangle, 4 * sizeof(SpriteVertex));
    buffer.bind();

    IndexBuffer ibo(indices, 6);
    ibo.bind();

    VertexLayout layout;
    layout.push<float>(3);
    layout.push<float>(4);
    vao.useLayout(layout);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
