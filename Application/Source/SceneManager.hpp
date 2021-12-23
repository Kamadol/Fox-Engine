#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <string>
#include <vector>

#include "Window.hpp"

class Scene;
class SceneManager
{
public:
	SceneManager(Window* window);

	void addScene(Scene* scene);
	bool changeScene(const std::string& sceneName);
	bool changeScene(size_t id);

	bool shouldClose();
	void update();
	void draw();

	void startDrawing();
	void endDrawing();

	float getDeltaTime() const;

private:
	Window* m_window;
	std::vector<Scene*> m_scenes;
	Scene* m_currentScene;

private:
	float m_previousTime;
	float m_dTime;

};

#endif
