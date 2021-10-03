#ifndef RAY_MARCHING_SCENE
#define RAY_MARCHING_SCENE

#include "Graphics.hpp"
#include "Scene.hpp"

class RayMarchingScene : public Scene
{
public:
    RayMarchingScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_time(0.0f), m_steps(0),
        m_rayMarching("Resources/Shaders/Sprite/rayMarching.shader")
    {
        Vector2 quadData[4]
        {
            Vector2( 1.0f,  1.0f),
            Vector2(-1.0f,  1.0f),
            Vector2(-1.0f, -1.0f),
            Vector2( 1.0f, -1.0f)
        };

        unsigned int indices[6]
        {
            0, 1, 2,
            0, 2, 3
        };

        glGenVertexArrays(1, &m_vao);
        glBindVertexArray(m_vao);

        glGenBuffers(1, &m_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vector2) * 4, quadData, GL_STATIC_DRAW);

        glGenBuffers(1, &m_ibo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vector2), 0);

        glBindVertexArray(0);
    }

    virtual void onStart()
    {
        glEnable(GL_DEPTH_TEST);
        FrameBuffer::unbind();

        m_camera.setPosition(Vector3(0.0f, 0.0f, 0.0f));

        m_rayMarching.bind();
        m_rayMarching.setUniform2f("u_screenSize", m_window->getSize());

        m_steps = 0;
        m_rayMarching.setUniform1i("u_steps", m_steps);
    }
    virtual void onUpdate()
    {
        m_dTime = m_manager->getDeltaTime();
        if (Input::isButtonPressed(KEY::ESC))
            m_window->setShouldClose(true);
        if (Input::isButtonOncePressed(KEY::P))
            m_manager->changeScene("minecraftScene");

        m_time += m_dTime;

        float rotSpeed = 2.0f;
        Vector2 mouseMovement = Input::getMouseMovement();
        m_cameraAngle.y += mouseMovement.x * rotSpeed * m_dTime;
        m_cameraAngle.x -= mouseMovement.y * rotSpeed * m_dTime;

        Quaternion destRotation = Quaternion::identity();
        destRotation *= Quaternion(Vector3(0.0f, 1.0f, 0.0f), m_cameraAngle.y);

        float maxAngle = 88.0f / 180.0f * 3.1415f;
        if (m_cameraAngle.x > maxAngle)
            m_cameraAngle.x = maxAngle;
        if (m_cameraAngle.x < -maxAngle)
            m_cameraAngle.x = -maxAngle;

        Vector3 right = -destRotation.rotate(Vector3(1.0f, 0.0f, 0.0f));
        Vector3 front =  destRotation.rotate(Vector3(0.0f, 0.0f, 1.0f));

        float moveSpeed = 10.0f;
        if (Input::isButtonPressed(KEY::W))
            m_camera.move(front * moveSpeed * m_dTime);
        if (Input::isButtonPressed(KEY::S))
            m_camera.move(-front * moveSpeed * m_dTime);
        if (Input::isButtonPressed(KEY::A))
            m_camera.move(right * moveSpeed * m_dTime);
        if (Input::isButtonPressed(KEY::D))
            m_camera.move(-right * moveSpeed * m_dTime);
        if (Input::isButtonPressed(KEY::SPACE))
            m_camera.move(Vector3(0.0f, moveSpeed * m_dTime, 0.0f));
        if (Input::isButtonPressed(KEY::LSHIFT))
            m_camera.move(Vector3(0.0f, -moveSpeed * m_dTime, 0.0f));

        destRotation *= Quaternion(Vector3(1.0f, 0.0f, 0.0f), m_cameraAngle.x);

        m_camera.setRotation(destRotation);

        m_rayMarching.setUniform1f("u_time", m_time);
        //m_rayMarching.setUniform3f("u_lightPos", Vector3(5.0f * sinf(m_time / 2.0f), 5.0f, 5.0f * cosf(m_time / 2.0f) + 11.0f));
        m_rayMarching.setUniform3f("u_lightPos", Vector3(0.0, 20.0, 10.0));
        m_rayMarching.setUniformMat4("u_camTransform", m_camera.getTransform());

        if (Input::isButtonOncePressed(KEY::T))
        {
            m_steps++;
            m_rayMarching.setUniform1i("u_steps", m_steps);
            std::cout << m_steps << std::endl;
        }
        if (Input::isButtonOncePressed(KEY::Y))
        {
            m_steps--;
            m_rayMarching.setUniform1i("u_steps", m_steps);
            std::cout << m_steps << std::endl;
        }
    }
    virtual void onRender()
    {
        //glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        m_window->pollEvents();
        m_window->swapBuffers();
    }

private:
    float m_dTime;
    float m_time;
    Transformable m_camera;
    Vector2 m_cameraAngle;
    int m_steps;

    Shader m_rayMarching;
    GLuint m_vbo;
    GLuint m_vao;
    GLuint m_ibo;

};

#endif
