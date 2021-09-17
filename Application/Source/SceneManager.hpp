#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <string>
#include <vector>

class Scene;
class SceneManager
{
public:
	SceneManager();

	void addScene(Scene* scene);
	bool changeScene(const std::string& sceneName);
	bool changeScene(size_t id);

	bool shouldClose();
	void update();

	float getDeltaTime() const;

private:
	std::vector<Scene*> m_scenes;
	Scene* m_currentScene;

private:
	float m_previousTime;
	float m_dTime;

};

#endif
