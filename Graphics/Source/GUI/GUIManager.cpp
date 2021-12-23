#include "GUIManager.hpp"

GUIManager::GUIManager()
	:m_camera(0.0f, 1200.0f, 0.0f, 800.0f, 0.0f, 10.0f),
	m_windowShader("Resources/Shaders/Sprite/GUIShader.shader")
{
	m_guiBodyTex.create("Resources/Textures/GUIBody.png");
	m_guiCornerTex.create("Resources/Textures/GUICorner.png");
	m_guiEdgeTex.create("Resources/Textures/GUIEdge.png");
	m_GUIRenderer.setTextures(&m_guiBodyTex, &m_guiCornerTex, &m_guiEdgeTex);
}

void GUIManager::update()
{

}
void GUIManager::draw()
{
	for (size_t i = 0; i < m_windows.size(); i++)
	{
		//m_GUIRenderer.draw(*m_windows[i], , );
	}
}
