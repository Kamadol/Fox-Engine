#include "Window.hpp"

#include <iostream>

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
    

    float triangle[6] =
    {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    size_t bufferId;
    glGenBuffers(1, &bufferId);
    glBindBuffer(GL_ARRAY_BUFFER, bufferId);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), triangle, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    while (!glfwWindowShouldClose(m_window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }
}
