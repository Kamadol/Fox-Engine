#include "Scene.hpp"

Scene::Scene(Window* window, const std::string& name)
	:m_window(window), m_manager(nullptr), m_name(name), m_isClosed(false)
{
	
}
Scene::~Scene()
{

} 

void Scene::close()
{
	m_isClosed = true;
	m_window->close();
}
