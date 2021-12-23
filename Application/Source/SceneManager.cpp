#include "SceneManager.hpp"

#include <iostream>

#include "Scene.hpp"

SceneManager::SceneManager(Window* window)
	:m_previousTime(0.0f), m_dTime(0.0f),
	m_window(window),
	m_currentScene(nullptr)
{

}

void SceneManager::addScene(Scene* scene)
{ 
	scene->setSceneManager(this);
	m_scenes.push_back(scene);
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
bool SceneManager::changeScene(size_t id)
{
	return 0;
}

bool SceneManager::shouldClose()
{ 
	return m_currentScene->isWindowClosed(); 
}
void SceneManager::update()
{
	float currentTome = (float)glfwGetTime();

	m_dTime = currentTome - m_previousTime;
	m_previousTime = currentTome;

	m_currentScene->onUpdate();
}
void SceneManager::draw()
{
	m_currentScene->onRender();
}

void SceneManager::startDrawing()
{
	m_window->clear();
}
void SceneManager::endDrawing()
{
	m_window->pollEvents();
	m_window->swapBuffers();
}

float SceneManager::getDeltaTime() const
{
	return m_dTime;
}
