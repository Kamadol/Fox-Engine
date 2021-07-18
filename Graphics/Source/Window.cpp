#include "Window.hpp"

#include <iostream>

#include "Buffer.hpp"
#include "Shader.hpp"

Window::Window(size_t width, size_t height)
	:m_width(width), m_height(height)
{
    if (!glfwInit())
        glfwTerminate();

    m_window = glfwCreateWindow(width, height, "Fox Engine", NULL, NULL);
    if (!m_window)
        glfwTerminate();

    glfwMakeContextCurrent(m_window);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;

    std::cout << glGetString(GL_VERSION) << std::endl;
    
    glfwSwapInterval(1);

    float triangle[6] =
    {
        -1.0f, -1.0f,
         0.0f,  1.0f,
         1.0f, -1.0f
    };

    //size_t bufferId;
    //glGenBuffers(1, &bufferId);
    //glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    //glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triangle, GL_STATIC_DRAW);

    Shader shader("../Application/Shaders/solidColor.vert", "../Application/Shaders/solidColor.frag");
    shader.bind();
    shader.setUniform4f("u_Color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));

    Buffer buffer(triangle, 6 * sizeof(float));
    buffer.bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    while (!glfwWindowShouldClose(m_window))
    {
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

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
