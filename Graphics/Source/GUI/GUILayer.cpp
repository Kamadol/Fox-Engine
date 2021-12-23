#include "GUILayer.hpp"

#include "Window.hpp"
#include "Input.hpp"

#include "Utility.hpp"

#include "Utility/Constants.hpp"

GUILayer::GUILayer()
	:m_dTime(0.0f), m_currentTime(0.0f), m_totalTime(0.0f), m_wireFrameMode(false),
	m_camera(0.0f, 1200.0f, 0.0f, 800.0f, 0.0f, 10.0f),
	m_font("Resources/Fonts/Pixellari.ttf"),
	m_font002("Resources/Fonts/arial.ttf"),
	m_textShader("Resources/Shaders/Sprite/text.shader"),
	m_spriteShader("Resources/Shaders/Sprite/GUIShader.shader"),
	m_guiWindow001(Vec2i(200.0f, 200.0f), Vec2i(300.0f, 500.0f), Vec2i(50, 50)),
	m_guiWindow002(Vec2i(300.0f,   0.0f), Vec2i(200.0f, 300.0f), Vec2i(50, 50)),
	m_guiWindow003(Vec2i(400.0f,   0.0f), Vec2i(300.0f, 300.0f), Vec2i(50, 50))
{
	m_info.setFont(&m_font002);
	m_info.setFontSize(20);
	m_info.setColor(Vector4(0.0f, 1.0f, 0.0f, 1.0f));
	m_info.setPosition(Vector3(5.0f, 780.0f, 0.0f));

	m_guiBodyTex.create("Resources/Textures/GUIBody.png");
	m_guiCornerTex.create("Resources/Textures/GUICorner.png");
	m_guiEdgeTex.create("Resources/Textures/GUIEdge.png");
	m_GUIRenderer.setTextures(&m_guiBodyTex, &m_guiCornerTex, &m_guiEdgeTex);

	m_guiWindow001.addChildren(&m_guiWindow002);
	m_guiWindow001.addChildren(&m_guiWindow003);
	//m_guiWindow002.setWorldPosition(Vec2i(100, 100));
}

void GUILayer::setDeltaTime(float dTime)
{
	m_dTime = dTime;
}

void GUILayer::update()
{
	if (Input::isButtonOncePressed(KEY::M))
	{
		if (m_wireFrameMode)
		{
			Window::wireFrameMode(false);
			m_wireFrameMode = false;
		}
		else
		{
			Window::wireFrameMode(true);
			m_wireFrameMode = true;
		}
	}

	for (size_t i = 0; i < m_GUIWindows.size(); i++)
	{
		m_GUIWindows[i].update();
	}

	m_currentTime += m_dTime;
	m_totalTime += m_dTime;

	if (m_currentTime >= updateTime)
	{
		m_info.setText(std::string((char*)glGetString(GL_VERSION)) + "\nms: " + std::to_string(m_dTime) + "\nFPS: " + std::to_string((int)(1.0f / m_dTime)));
		m_currentTime = 0.0f;
	}

	m_guiWindow001.update();
	m_guiWindow002.update();
	m_guiWindow003.update();
}
void GUILayer::draw()
{
	m_textRenderer.flush(m_info, m_textShader, m_camera.getMatrix());



	/*Line line;
	for (float i = -4.0f * 3.1415926535f; i <= 4.0f * 3.1415926535f; i += 3.1415926535f / 64.0f)
	{
		line.m_points.push_back(Vector3(i, sinf(m_totalTime) * 2.0f * sinf(4.0f * i) / i, 0.0f) * 50.0f);
	}

	line.m_thickness = 2.0f;
	line.m_color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
	line.setPosition(Vector3(600.0f, 400.0f, 0.0f));

	m_lineRenderer.draw(line, m_textShader, m_camera.getMatrix());*/



	/*Line line;
	Vector2 p1(100.0f, 100.0f);
	Vector2 p2(100.0f, 600.0f);
	Vector2 p3(700.0f, 100.0f);
	Vector2 p4(600.0f, 800.0f);
	for (float i = 0.0f; i <= 1.0f; i += 0.01f)
	{
		Vector2 bezier = cubicBezier2D(p1, p2, p3, p4, i);
		line.m_points.push_back(Vector3(bezier.x, bezier.y, 0.0f));
	}

	line.m_thickness = 2.0f;
	line.m_color = Vector4(1.0f, 1.0f, 0.0f, 1.0f);
	line.setPosition(Vector3(0.0f, 0.0f, 0.0f));

	Line line2;
	line2.m_points.push_back(Vector3(p1.x, p1.y, 0.0f));
	line2.m_points.push_back(Vector3(p2.x, p2.y, 0.0f));
	line2.m_points.push_back(Vector3(p3.x, p3.y, 0.0f));
	line2.m_points.push_back(Vector3(p4.x, p4.y, 0.0f));

	line2.m_thickness = 3.0f;
	line2.m_color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
	line2.setPosition(Vector3(0.0f, 0.0f, 0.0f));

	m_lineRenderer.draw(line, m_textShader, m_camera.getMatrix());
	m_lineRenderer.draw(line2, m_textShader, m_camera.getMatrix());*/

	

	m_GUIRenderer.draw(m_guiWindow003, m_spriteShader, m_camera);
	m_GUIRenderer.draw(m_guiWindow002, m_spriteShader, m_camera);
	m_GUIRenderer.draw(m_guiWindow001, m_spriteShader, m_camera);
}
