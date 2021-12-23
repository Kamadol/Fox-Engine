#ifndef GUI_MANAGER_HPP
#define GUI_MANAGER_HPP

#include "OrthographicCamera.hpp"
#include "Shader.hpp"

#include "GUIWindow.hpp"
#include "Renderers/GUIRenderer.hpp"

class GUIManager
{
public:
	GUIManager();

	void addWindow(GUIWindow* window);

	void update();
	void draw();

private:
	Texture m_guiBodyTex;
	Texture m_guiCornerTex;
	Texture m_guiEdgeTex;
	Shader m_windowShader;
	OrthographicCamera m_camera;

	GUIRenderer m_GUIRenderer;

	std::vector<GUIWindow*> m_windows;

	//OrthographicCamera m_camera;
	//Shader m_GUIShader;

};

#endif
