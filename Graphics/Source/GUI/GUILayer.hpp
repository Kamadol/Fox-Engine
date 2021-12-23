#ifndef GUI_LAYER_HPP
#define GUI_LAYER_HPP

#include <vector>

#include "GUIWindow.hpp"

#include "Renderers/TextRenderer.hpp"
#include "Renderers/LineRenderer.hpp"
#include "Renderers/GUIRenderer.hpp"
#include "RenderText.hpp"
#include "OrthographicCamera.hpp"

class GUILayer
{
public:
	GUILayer();

	void setDeltaTime(float dTime);

	void update();
	void draw();

private:
	OrthographicCamera m_camera;

	float m_dTime;
	float m_currentTime;
	float m_totalTime;

	bool m_wireFrameMode;

	std::vector<GUIWindow> m_GUIWindows;

private:
	RenderText m_info;
	Font m_font;
	Font m_font002;

private:
	Texture m_guiBodyTex;
	Texture m_guiCornerTex;
	Texture m_guiEdgeTex;

private:
	Shader m_textShader;
	Shader m_spriteShader;

private:
	TextRenderer m_textRenderer;
	LineRenderer m_lineRenderer;
	GUIRenderer m_GUIRenderer;
	GUIWindow m_guiWindow001;
	GUIWindow m_guiWindow002;
	GUIWindow m_guiWindow003;


private:


};

#endif
