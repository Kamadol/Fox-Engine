#ifndef GUI_RENDERER_HPP
#define GUI_RENDERER_HPP

#include <Renderables/GUIRectangle.hpp>

#include "Texture.hpp"
#include "Shader.hpp"
#include "OrthographicCamera.hpp"
#include "Vertices/SpriteVertex.hpp"

class GUIRenderer
{
public:
	GUIRenderer();

	void setTextures(Texture* bodyTexture, Texture* cornerTexture, Texture* edgeTexture);

	void draw(const GUIRectangle& rectangle, const Shader& shader, const OrthographicCamera& camera);

private:
	void createBody(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr);
	void createCorners(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr);
	void createEdges(Vec2i pos, Vec2i size, Vec2i margin, SpriteVertex* ptr);

private:
	unsigned int m_VAO;
	unsigned int m_IBO;
	unsigned int m_VBO;

private:
	Texture* m_bodyTex;
	Texture* m_cornerTex;
	Texture* m_edgeTex;

};

#endif
