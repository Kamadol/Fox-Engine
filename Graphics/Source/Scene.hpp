#ifndef SCENE_HPP
#define SCENE_HPP

#include "Window.hpp"
#include "SceneManager.hpp"

class Scene
{
public:
	Scene(Window* window, const std::string& name);
	~Scene();

	virtual void onStart() = 0;
	virtual void onUpdate() = 0;
	virtual void onRender() = 0;

	void setSceneManager(SceneManager* manager) { m_manager = manager; }
	const std::string& getName() { return m_name; }

	void close();
	void setShouldClose(bool shouldClose) { m_window->setShouldClose(shouldClose); }
	bool isWindowClosed() { return m_isClosed || m_window->shouldClose(); }

protected:
	Window* m_window;
	SceneManager* m_manager;

private:
	std::string m_name;
	bool m_isClosed;

};

#endif
