#ifndef MESHES_SCENE
#define MESHES_SCENE

#include "Graphics.hpp"
#include "Scene.hpp"

class MeshesScene : public Scene
{
public:
    MeshesScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_camera(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 100.0f),
        m_meshShader("Resources/Shaders/Mesh/normalShow.shader"),
        m_cube(Vector3(1.0f, 1.0f, 1.0f)),
        m_sphere(40, 40, 1.0f),
        m_torus(40, 40, 0.7f, 0.2f),
        m_cylinder(40, 1.0f, 1.0f),
        m_singleColorShader("Resources/Shaders/Mesh/singleColor.shader"),
        m_pointerCam(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 100.0f),
        m_right(Vector3(1.0f, 0.1f, 0.1f)),
        m_up(Vector3(0.1f, 1.0f, 0.1f)),
        m_front(Vector3(0.1f, 0.1f, 1.0f)),
        m_fbo(1200, 800),
        m_sprite(Vector3(0.0f, 0.0f, 0.0f), Vector2(2.0f, 2.0f), Vector4(0.0f, 0.0f, 0.0f, 1.0f)),
        m_spriteShader("Resources/Shaders/Sprite/postProcess.shader")
    {
        m_right.setPosition(Vector3(0.0f, 0.0f, -4.0f));
        m_up.setPosition(Vector3(0.0f, 0.0f, -4.0f));
        m_front.setPosition(Vector3(0.0f, 0.0f, -4.0f));

        m_foxMesh.load("Resources/Models/fox.stl");
        m_foxMesh.scale(Vector3(0.05f));
        m_foxMesh.rotate(Vector3(1.0f, 0.0f, 0.0f), -3.1415 * 0.5f);
    }

    virtual void onStart()
    {
        FrameBuffer::unbind();

        //m_foxMesh.rotate(Vector3(0.0f, 1.0f, 0.0f), 3.1415 * 0.5f);

       //m_camera.setPosition(Vector3(0.0f, 0.0f, 0.0f));
       //m_camera.setFront(Vector3(-1.0f, 0.0f, 0.0f));
       //m_camera.setUp(Vector3(0.0f, 1.0f, 0.0f));

        m_cube.setPosition(Vector3(-4.0f, -1.0f, -6.0f));
        m_sphere.setPosition(Vector3(-2.0f, -1.0f, -6.0f));
        m_torus.setPosition(Vector3(0.0f, -1.0f, -6.0f));
        m_cylinder.setPosition(Vector3(2.0f, -1.0f, -6.0f));
        m_plane.setPosition(Vector3(4.0f, -1.0f, -6.0f));
    }
    virtual void onUpdate()
    {
        m_dTime = m_manager->getDeltaTime();
        if (Input::isButtonPressed(KEY::ESC))
            m_window->setShouldClose(true);
        if (Input::isButtonOncePressed(KEY::P))
            m_manager->changeScene("rayMarchingScene");

        m_torus.rotate(Vector3(1.0f, 0.0f, 0.0f), 3.1415f / 8.0f * m_dTime);

        //camera movement and rotation
        m_camera.update(m_dTime);
    }
    virtual void onRender()
    {
        m_fbo.bind();

        //m_window->clear();
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        //phong shader
        m_meshShader.bind();
        m_meshShader.setUniform3f("lightColor", Vector3(1.0f, 1.0f, 1.0f));
        m_meshShader.setUniform3f("lightPos", Vector3(0.0f, 2.0f, -0.5f));
        m_meshShader.setUniform3f("viewPos", m_camera.getPosition());
        m_meshRenderer.submit(m_cube, m_meshShader, m_camera.getMatrix());
        m_meshRenderer.submit(m_sphere, m_meshShader, m_camera.getMatrix());
        m_meshRenderer.submit(m_torus, m_meshShader, m_camera.getMatrix());
        m_meshRenderer.submit(m_cylinder, m_meshShader, m_camera.getMatrix());
        m_meshRenderer.submit(m_plane, m_meshShader, m_camera.getMatrix());
        m_meshRenderer.submit(m_foxMesh, m_meshShader, m_camera.getMatrix());

        //m_singleColorShader.bind();
        //m_singleColorShader.setUniform4f("u_color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        //m_meshRenderer.submit(m_right, m_singleColorShader, m_pointerCam.getMatrix());
        //m_singleColorShader.setUniform4f("u_color", Vector4(0.0f, 1.0f, 0.0f, 1.0f));
        //m_meshRenderer.submit(m_up, m_singleColorShader, m_pointerCam.getMatrix());
        //m_singleColorShader.setUniform4f("u_color", Vector4(0.0f, 0.0f, 1.0f, 1.0f));
        //m_meshRenderer.submit(m_front, m_singleColorShader, m_pointerCam.getMatrix());

        m_fbo.unbind();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        glActiveTexture(GL_TEXTURE0);
        m_fbo.bindTexture();
        m_spriteShader.setUniform1i("texture0", 0);
        m_spriteRenderer.submit(m_sprite, m_spriteShader, Mat4x4::identity());
        m_fbo.unbindTexture();

        //m_window->pollEvents();
        //m_window->swapBuffers();
    }

private:
    MovablePerspCamera m_camera;

    Shader m_meshShader;
    CubeMesh m_cube;
    SphereMesh m_sphere;
    TorusMesh m_torus;
    CylinderMesh m_cylinder;
    PlaneMesh m_plane;

    SimpleMeshRenderer m_meshRenderer;
    Shader m_singleColorShader;
    PerspectiveCamera m_pointerCam;
    CubeMesh m_right;
    CubeMesh m_up;
    CubeMesh m_front;

    Shader m_spriteShader;
    SimpleSpriteRenderer m_spriteRenderer;
    Sprite m_sprite;
    FrameBuffer m_fbo;

    Mesh m_foxMesh;

private:
    float m_dTime;

};

#endif
