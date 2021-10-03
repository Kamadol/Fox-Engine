#ifndef NORMAL_MAPPING_SCENE
#define NORMAL_MAPPING_SCENE

#include "Graphics.hpp"
#include "Scene.hpp"

class NormalMappingScene : public Scene
{
public:
    NormalMappingScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_camera(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 100.0f),
        m_meshShader("Resources/Shaders/Mesh/planarPointLight.shader"),
        m_singleColorShader("Resources/Shaders/Mesh/singleColor.shader"),
        m_cube(Vector3(10.0f, 1.0f, 10.0f)),
        m_lightMesh(20, 20, 0.1f)
    {
        m_lightAngle = 0.0f;

        m_foxMesh.load("Resources/Models/fox002.stl");
        m_foxMesh.scale(Vector3(0.02f));
        m_foxMesh.rotate(Vector3(1.0f, 0.0f, 0.0f), -3.1415 * 0.5f);

        m_cube.setPosition(Vector3(0.0f, -1.75f, 0.0));
    }

    virtual void onStart()
    {
        glEnable(GL_DEPTH_TEST);

        

        /*pg::Image image;
        size_t xSize = 400;
        size_t ySize = 400;
        image.create(xSize, ySize, pg::Color(0, 0, 255, 255));

        pg::CoherentNoiseMask mask;
        mask.setOctaveCount(2);
        mask.setStartZoom(32.0f);
        for (size_t i = 0; i < ySize; i++)
        {
            for (size_t j = 0; j < xSize; j++)
            {
                float value = mask.getValue((float)j, (float)i);
                unsigned char r = (unsigned char)(value * 255.0f);
                unsigned char g = (unsigned char)(value * 255.0f);
                unsigned char b = (unsigned char)(value * 255.0f);
                image.setPixel(j, i, pg::Color(r, g, b, 255));
            }
        }
        image.saveToFile("Resources/Pg/perlinTest.png");

        for (size_t i = 0; i < ySize - 1; i++)
        {
            for (size_t j = 0; j < xSize - 1; j++)
            {
                pg::Color center = image.getPixel(j, i);
                pg::Color right = image.getPixel(j + 1, i);
                pg::Color down = image.getPixel(j, i + 1);

                Vector3 normal;
                normal.x = ((float)center.r - (float)right.r);
                normal.y = ((float)center.r - (float)down.r);
                normal.z = 1.0f;
                normal = normal.unit();
                //std::cout << normal << std::endl;

                pg::Color out;
                out.r = (unsigned char)((normal.x + 1.0f) * 127.5f);
                out.g = (unsigned char)((normal.y + 1.0f) * 127.5f);
                out.b = (unsigned char)((normal.z + 1.0f) * 127.5f);
                out.a = 255;

                image.setPixel(j, i, out);
            }
        }
        image.saveToFile("Resources/Pg/perlinNormalTest.png");*/

        

        m_lightMesh.setPosition(Vector3(0.0f, 2.0f, 1.0f));

        m_camera.setPosition(Vector3(0.0f, 0.0f, 4.0f));



        m_meshShader.bind();
        m_meshShader.setUniform3f("u_planarLight.direction", Vector3(1.0f, -1.0f, 1.0f));
        m_meshShader.setUniform3f("u_planarLight.ambient", Vector3(0.1f));
        m_meshShader.setUniform3f("u_planarLight.diffuse", Vector3(0.7f));
        m_meshShader.setUniform3f("u_planarLight.specular", Vector3(1.0f));

        m_meshShader.setUniform3f("u_pointLight.ambient", Vector3(0.1f));
        m_meshShader.setUniform3f("u_pointLight.diffuse", Vector3(0.7f));
        m_meshShader.setUniform3f("u_pointLight.specular", Vector3(1.0f));
    }
    virtual void onUpdate()
    {
        m_dTime = m_manager->getDeltaTime();
        if (Input::isButtonPressed(KEY::ESC))
            m_window->setShouldClose(true);
        if (Input::isButtonOncePressed(KEY::P))
            m_manager->changeScene("rayMarchingScene");

        m_lightAngle += 3.1415926535f / 4.0f * m_dTime;
        m_lightMesh.setPosition(Vector3(1.5f * sinf(m_lightAngle), 1.0f, 1.5f * cosf(m_lightAngle)));

        m_meshShader.setUniform3f("u_pointLight.position", m_lightMesh.getPosition());
        m_meshShader.setUniform3f("u_camPos", m_camera.getPosition());
        m_meshShader.setUniform3f("u_camDir", m_camera.getFront());
        
        m_camera.update(m_dTime);
    }
    virtual void onRender()
    {
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);

        m_window->clear();

        //single color shader
        m_singleColorShader.bind();
        m_singleColorShader.setUniform4f("u_color", Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        m_meshRenderer.submit(m_lightMesh, m_singleColorShader, m_camera.getMatrix());

        //light shader
        m_meshShader.bind();
        m_meshShader.setUniformMaterial("u_material", Material::silver());
        m_meshRenderer.submit(m_cube, m_meshShader, m_camera.getMatrix());
        m_meshShader.setUniformMaterial("u_material", Material::obsidian());
        m_meshRenderer.submit(m_foxMesh, m_meshShader, m_camera.getMatrix());

        m_window->pollEvents();
        m_window->swapBuffers();
    }

private:
    MovablePerspCamera m_camera;
    SimpleMeshRenderer m_meshRenderer;

    Shader m_meshShader;
    Shader m_singleColorShader;
    Texture m_perlinTexture;
    Texture m_perlinNormalTexture;

    CubeMesh m_cube;

    SphereMesh m_lightMesh;
    float m_lightAngle;

    Mesh m_foxMesh;

private:
    float m_dTime;

};

#endif
