#ifndef MINECRAFT_SCENE
#define MINECRAFT_SCENE

#include "Graphics.hpp"
#include "Scene.hpp"

class MinecraftScene : public Scene
{
public:
    MinecraftScene(Window* window, const std::string& name)
        :Scene(window, name), m_dTime(0.0f),
        m_camera(3.1415f / 4.0f, m_window->getAspectRatio(), 0.1f, 300.0f),
        m_meshShader("Resources/Shaders/Mesh/batchShader.shader"),
        m_ortho(0.0f, 1200.0f, 0.0f, 800.0f, 0.0f, 100.0f),
        m_spriteShader("Resources/Shaders/Sprite/batchSprite.shader"),
        m_font("Resources/Fonts/arial.ttf")
    {
        pg::CoherentNoiseMask mask;
        mask.setOctaveCount(3);
        mask.setStartZoom(32.0f);

        for (size_t i = 0; i < 100; i++)
        {
            for (size_t j = 0; j < 100; j++)
            {
                float height = (size_t)(mask.getValue((float)i, (float)j) * 30.0f);

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

        m_text.setFont(&m_font);
        m_text.setFontSize(30);
        m_text.setColor(Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        m_text.setPosition(Vector3(10.0f, 770.0f, 0.0f));
    }

    virtual void onStart()
    {
        glEnable(GL_DEPTH_TEST);

        //m_stoneTexture.load("Resources/Textures/sand.png");
        m_stoneTexture.create("Resources/Textures/sand.png");
        m_sandTexture.create("Resources/Textures/fox001.jpg");

        m_batchRenderer.submit(CubeMesh(1.0f), &m_offsets[0], m_offsets.size());

        m_camera.setPosition(Vector3(0.0f, 20.0f, 40.0f));

        

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

        //m_window->clear();

        //light shader
        glActiveTexture(GL_TEXTURE0);
        m_stoneTexture.bind();
        m_meshShader.setUniform1i("texture0", 0);

        m_batchRenderer.flush(m_meshShader, m_camera.getMatrix());
        m_stoneTexture.unbind();

        //m_textRenderer.draw(m_text, m_spriteShader, m_ortho.getMatrix());

        //text
        //m_text.setText(std::string((char*)glGetString(GL_VERSION)) + "\nms: " + std::to_string(m_dTime) + "\nFPS: " + std::to_string(1.0f / m_dTime));
        //m_text.draw(m_spriteShader, m_ortho.getMatrix());
        //glActiveTexture(GL_TEXTURE0);
        //m_spriteShader.bind();
        //m_textTexture->bind();
        //m_spriteShader.setUniform1i("texture0", 0);
        //m_textRenderer.flush();

        //m_window->pollEvents();
        //m_window->swapBuffers();
    }

private:
    MovablePerspCamera m_camera;
    SimpleMeshRenderer m_meshRenderer;
    MeshRenderer m_batchRenderer;

    Shader m_meshShader;
    Texture m_stoneTexture;
    Texture m_sandTexture;

    std::vector<CubeMesh> m_cubes;
    std::vector<Vector3> m_offsets;

    OrthographicCamera m_ortho;
    SpriteRenderer m_spriteRenderer;
    TextRenderer m_textRenderer;
    RenderText m_text;
    Font m_font;
    Texture* m_textTexture;
    Shader m_spriteShader;

private:
    float m_dTime;

};

#endif
