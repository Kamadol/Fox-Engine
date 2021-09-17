#include "Scene.hpp"

Scene::Scene(Window* window, const std::string& name)
	:m_window(window), m_manager(nullptr), m_name(name), m_isClosed(false)
{
	
}
Scene::~Scene()
{

} 

void Scene::setSceneManager(SceneManager* manager)
{ 
	m_manager = manager; 
}
const std::string& Scene::getName() const
{ 
	return m_name; 
}
size_t Scene::getId() const
{
	return m_id;
}

void Scene::close()
{
	m_isClosed = true;
	m_window->close();
}
void Scene::setShouldClose(bool shouldClose)
{ 
	m_window->setShouldClose(shouldClose); 
}
bool Scene::isWindowClosed() const
{ 
	return m_isClosed || m_window->getShouldClose();
}
