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

	void setSceneManager(SceneManager* manager);
	const std::string& getName() const;
	size_t getId() const;

	void close();
	void setShouldClose(bool shouldClose);
	bool isWindowClosed() const;

protected:
	Window* m_window;
	SceneManager* m_manager;

private:
	std::string m_name;
	size_t m_id;
	bool m_isClosed;

};

#endif
