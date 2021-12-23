#ifndef GUI_WINDOW_HPP
#define GUI_WINDOW_HPP

#include "Sprite.hpp"
#include "Renderers/SpriteRenderer.hpp"
#include "Texture.hpp"
#include "Renderables/GUIRectangle.hpp"

#include "Utility/Draggable.hpp"

class GUIWindow : public GUIRectangle
{
private:
	class DraggableBody : public Draggable
	{
	public:
		DraggableBody(GUIWindow* window);

		virtual void onClickInside() override;
		virtual void onClickMouseDown() override;

	private:
		GUIWindow* window;
		Vec2i prevPosition;

	};
	class DraggableCorner : public Draggable
	{
	public:
		DraggableCorner(GUIWindow* window);

		void setMinMaxSize(Vec2i min, Vec2i max);
		void setCurrentCorner(uint16_t corner);

		virtual void onClickInside() override;
		virtual void onClickMouseDown() override;

	private:
		GUIWindow* window;
		Vec2i prevPosition;
		Vec2i min, max;
		uint16_t corner;

	};

public:
	GUIWindow(Vec2i position, Vec2i size, Vec2i margin);

	void update();

private:
	DraggableBody m_bodyDrag;
	DraggableCorner m_cornersDrag[4];
	uint8_t m_order; //lower - higher priority

	Vec2i m_minSize;
	Vec2i m_maxSize;

private:
	static GUIWindow* m_currentDraggedWindow;

};

#endif
