#include "SceneManager.hpp"

#include <iostream>

#include "Scene.hpp"

SceneManager::SceneManager()
	:m_previousTime(0.0f), m_dTime(0.0f), m_currentScene(nullptr)
{

}
bool SceneManager::changeScene(const std::string& sceneName)
{
	for (size_t i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i]->getName() == sceneName)
		{
			m_currentScene = m_scenes[i];
			m_currentScene->onStart();
			m_currentScene->setShouldClose(false);
			std::cout << m_currentScene->getName() << " initialized" << std::endl;
			return true;
		}
	}

	std::cout << "\"" << sceneName << "\"" << " doesn't exist" << std::endl;

	return false;
}

bool SceneManager::shouldClose()
{ 
	return m_currentScene->isWindowClosed(); 
}
void SceneManager::update()
{
	m_dTime = glfwGetTime() - m_previousTime;
	m_previousTime = glfwGetTime();

	m_currentScene->onUpdate();
	m_currentScene->onRender();
}
