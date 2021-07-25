#include "Window.hpp"

#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Buffer.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

#include "SimpleRenderer2D.hpp"

struct Vertex
{
    Vertex(Vector2 position, size_t something, Vector4 color)
        :position(position), something(something), color(color)
    {

    }

    Vector2 position;
    size_t something;
    Vector4 color;
};

Window::Window(size_t width, size_t height)
	:m_width(width), m_height(height)
{
    if (!glfwInit())
        glfwTerminate();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, "Fox Engine", NULL, NULL);
    if (!m_window)
        glfwTerminate();

    glfwMakeContextCurrent(m_window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glfwSwapInterval(1);



    Vertex triangle[4] =
    {
        Vertex(Vector2(-0.9f, -0.9f), 1, Vector4(1.0f, 0.0f, 0.0f, 1.0f)),
        Vertex(Vector2( 0.0f,  0.9f), 2, Vector4(0.0f, 1.0f, 0.0f, 1.0f)),
        Vertex(Vector2( 0.9f, -0.9f), 3, Vector4(0.0f, 0.0f, 1.0f, 1.0f)),
        Vertex(Vector2( 0.9f,  0.9f), 4, Vector4(1.0f, 0.0f, 0.0f, 1.0f)),
    };

    size_t indices[6] =
    {
        0, 1, 2,
        1, 2, 3
    };


    //Shader shader("../Application/Shaders/solidColor_002.vert", "../Application/Shaders/solidColor_002.frag");
    Shader shader("../Application/Shaders/testShader.vert", "../Application/Shaders/testShader.frag");
    shader.bind();
    //shader.setUniform4f("u_Color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    VertexArray vao;
    vao.bind();

    Buffer buffer(triangle, 4 * sizeof(Vertex));
    buffer.bind();
    
    IndexBuffer ibo(indices, 6);
    ibo.bind();
    
    VertexLayout layout;
    layout.push<float>(2);
    layout.push<size_t>(1);
    layout.push<float>(4);
    vao.useLayout(layout);

    //glEnableVertexAttribArray(0);
    //glEnableVertexAttribArray(1);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4,                               0);
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void*)(sizeof(float) * 2));

    Shader shader2("../Application/Shaders/solidColor_002.vert", "../Application/Shaders/solidColor_002.frag");
    shader2.bind();
    SimpleRenderer2D renderer;
    Sprite sprite(Vector3(0.0f, 0.0f, 0.0f), Vector2(0.2f, 0.2f));


    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        renderer.submit(Sprite(Vector3(0.0f,  0.0f, 0.0f), Vector2(0.2f, 0.2f)));
        renderer.submit(Sprite(Vector3(0.0f,  0.5f, 0.0f), Vector2(0.2f, 0.2f)));
        renderer.submit(Sprite(Vector3(0.0f, -0.5f, 0.0f), Vector2(0.2f, 0.2f)));

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }

    glfwDestroyWindow(m_window); 
    glfwTerminate();
}
 Window::~Window()
{
    glfwTerminate();
}
