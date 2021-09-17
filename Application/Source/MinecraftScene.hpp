#ifndef MINECRAFT_SCENE
#define MINECRAFT_SCENE

#include "Graphics.hpp"
#include "Scene.hpp"

class MinecraftScene : public Scene
{
public:
    MinecraftScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_camera(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 100.0f),
        m_meshShader("Resources/Shaders/Mesh/batchShader.shader")
    {
        pg::CoherentNoiseMask mask;
        mask.setOctaveCount(2);
        mask.setStartZoom(32.0f);

        for (size_t i = 0; i < 32; i++)
        {
            for (size_t j = 0; j < 32; j++)
            {
                float height = (size_t)(mask.getValue((float)i, (float)j) * 10.0f);

                for (size_t k = 0; k < height; k++)
                {
                    CubeMesh mesh(Vector3(1.0f));

                    Vector3 position = Vector3((float)i, (float)k, (float)j);

                    m_offsets.push_back(position);

                    mesh.setPosition(position);
                    m_cubes.push_back(mesh);
                }
            }
        }
    }

    virtual void onStart()
    {
        glEnable(GL_DEPTH_TEST);

        std::cout << m_offsets.size() << std::endl;

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

        m_stoneTexture.load("Resources/Textures/sand.png");



        m_batchRenderer.submit(CubeMesh(1.0f), &m_offsets[0], m_offsets.size());

        m_camera.setPosition(Vector3(0.0f, 0.0f, 20.0f));

        /*m_meshShader.bind();
        m_meshShader.setUniform3f("u_planarLight.direction", Vector3(1.0f, -1.0f, 1.0f));
        m_meshShader.setUniform3f("u_planarLight.ambient", Vector3(0.1f));
        m_meshShader.setUniform3f("u_planarLight.diffuse", Vector3(0.7f));
        m_meshShader.setUniform3f("u_planarLight.specular", Vector3(1.0f));

        m_meshShader.setUniform3f("u_pointLight.ambient", Vector3(0.1f));
        m_meshShader.setUniform3f("u_pointLight.diffuse", Vector3(0.7f));
        m_meshShader.setUniform3f("u_pointLight.specular", Vector3(1.0f));*/
    }
    virtual void onUpdate()
    {
        m_dTime = m_manager->getDeltaTime();
        if (Input::isButtonPressed(KEY::ESC))
            m_window->setShouldClose(true);
        if (Input::isButtonOncePressed(KEY::P))
            m_manager->changeScene("meshesScene");



        /*m_meshShader.setUniform3f("u_pointLight.position", Vector3(0.0f, 50.0f, 0.0f));
        m_meshShader.setUniform3f("u_camPos", m_camera.getPosition());
        m_meshShader.setUniform3f("u_camDir", m_camera.getFront());*/

        m_camera.update(m_dTime);
    }
    virtual void onRender()
    {
        glClearColor(0.1f, 0.3f, 1.0f, 1.0f);

        m_window->clear();

        //light shader
        glActiveTexture(GL_TEXTURE0);
        m_meshShader.bind();
        m_meshShader.setUniform1i("texture0", 0);
        m_batchRenderer.flush(m_meshShader, m_camera.getMatrix());

        /*m_meshShader.setUniformMaterial("u_material", Material::silver());
        for (size_t i = 0; i < m_cubes.size(); i++)
        {
            m_meshRenderer.submit(m_cubes[i], m_meshShader, m_camera.getMatrix());
        }*/

        m_window->pollEvents();
        m_window->swapBuffers();
    }

private:
    MovablePerspCamera m_camera;
    SimpleMeshRenderer m_meshRenderer;
    MeshRenderer m_batchRenderer;

    Shader m_meshShader;
    Texture m_stoneTexture;

    std::vector<CubeMesh> m_cubes;
    std::vector<Vector3> m_offsets;

private:
    float m_dTime;

};

#endif
