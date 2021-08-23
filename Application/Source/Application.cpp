#include <iostream>

#include "Graphics.hpp"

class TestScene : public Scene
{
public:
    TestScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_camera(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 100.0f),
        m_meshShader("Resources/Shaders/normalShowV.shader", "Resources/Shaders/normalShowF.shader"),
        m_cube(Vector3(1.0f, 1.0f, 1.0f)),
        m_sphere(40, 40, 1.0f),
        m_torus(40, 40, 0.7f, 0.2f),
        m_cylinder(40, 1.0f, 1.0f)
    {

    }

    virtual void onStart()
    {
        m_foxTexture.load("Resources/fox001.jpg");

        m_camera.setPosition(Vector3(0.0f, 0.0f, 4.0f));
        m_camera.setFront(Vector3(0.0f, 0.0f, -1.0f));
        m_camera.setUp(Vector3(0.0f, 1.0f, 0.0f));

        m_sphere.setPosition(  Vector3(0.0f, 0.0f, 0.0f));
        m_sphere.setPosition(  Vector3(0.0f, 0.0f, 2.0f));
        m_torus.setPosition(   Vector3(0.0f, 0.0f, 4.0f));
        m_cylinder.setPosition(Vector3(0.0f, 0.0f, 6.0f));
        m_plane.setPosition(   Vector3(0.0f, 0.0f, 8.0f));
    }
    virtual void onUpdate()
    {
        m_torus.rotate(Vector3(1.0f, 0.0f, 0.0f), 3.1415f / 8.0f * m_dTime);

		m_dTime = m_manager->getDeltaTime();

        if (Input::isButtonPressed(KEY::ESC))
           m_window->setShouldClose(true);

        //camera movement and rotation
        float cameraSpeed = 10.0f * m_dTime;
        float cameraRotationSpeed = 0.8f * m_dTime;
        if (Input::isButtonPressed(KEY::W))
            m_camera.moveFront(cameraSpeed);
        if (Input::isButtonPressed(KEY::S))
            m_camera.moveFront(-cameraSpeed);
        if (Input::isButtonPressed(KEY::A))
            m_camera.moveRight(-cameraSpeed);
        if (Input::isButtonPressed(KEY::D))
            m_camera.moveRight(cameraSpeed);
        if (Input::isButtonPressed(KEY::SPACE))
            m_camera.move(Vector3(0.0f, cameraSpeed, 0.0f));
        if (Input::isButtonPressed(KEY::LSHIFT))
            m_camera.move(Vector3(0.0f, -cameraSpeed, 0.0f));

        Vector2 mouseMovement = Input::getMouseMovement();
        m_camera.rotateX(mouseMovement.y * cameraRotationSpeed);
        m_camera.rotateY(-mouseMovement.x * cameraRotationSpeed);
    }
    virtual void onRender()
    {
        m_window->clear();

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

		m_window->pollEvents();
		m_window->swapBuffers();
    }

private:
    MovablePerspCamera m_camera;

    Shader m_meshShader;
    Texture m_foxTexture;
    CubeMesh m_cube;
    SphereMesh m_sphere;
    TorusMesh m_torus;
    CylinderMesh m_cylinder;
    PlaneMesh m_plane;

    SimpleMeshRenderer m_meshRenderer;

private:
	float m_dTime;

};

int main()
{
    Window window(1200, 800);
    //Window window(1920, 1080);
    SceneManager sceneManager;

    TestScene testScene(&window, "TestScene");
	testScene.setSceneManager(&sceneManager);
    TestScene testScene2(&window, "TestScene2");
    testScene2.setSceneManager(&sceneManager);




    sceneManager.addScene(&testScene);
    sceneManager.addScene(&testScene2);
    sceneManager.changeScene("TestScene");

    while(!sceneManager.shouldClose())
        sceneManager.update();





    glfwTerminate();
    return 0;
}
