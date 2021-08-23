#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <string>
#include <vector>

class Scene;
class SceneManager
{
public:
	SceneManager();

	void addScene(Scene* scene) { m_scenes.push_back(scene); }
	bool changeScene(const std::string& sceneName);

	bool shouldClose();
	void update();

	float getDeltaTime() { return m_dTime; }

private:
	std::vector<Scene*> m_scenes;
	Scene* m_currentScene;

private:
	float m_previousTime;
	float m_dTime;

};

#endif
