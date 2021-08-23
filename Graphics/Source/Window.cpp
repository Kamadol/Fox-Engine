#include "Window.hpp"

#include <iostream>

#include "Input.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "Texture.hpp"

#include "Renderers/SimpleSpriteRenderer.hpp"
#include "Renderers/SimpleMeshRenderer.hpp"
#include "Renderers/SimpleTextRenderer.hpp"

#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"
#include "MovablePerspCamera.hpp"

#include "Meshes/CubeMesh.hpp"
#include "Meshes/SphereMesh.hpp"

#include "Quaternion.hpp"

Window::Window(size_t width, size_t height)
	:m_width(width), m_height(height)
{
	if (!glfwInit())
		glfwTerminate();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_window = glfwCreateWindow(width, height, "Fox Engine", NULL, NULL);
	//m_window = glfwCreateWindow(width, height, "Fox Engine", glfwGetPrimaryMonitor(), NULL);
	if (!m_window)
		glfwTerminate();

	glfwMakeContextCurrent(m_window);

	//opengl init
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	std::cout << glGetString(GL_VERSION) << std::endl;
	
	//some flags and window stuff inits
	glfwSwapInterval(1);
	glfwSetWindowPos(m_window, 300, 100);
	glfwSetKeyCallback(m_window, Input::key_callback);
	glfwSetMouseButtonCallback(m_window, Input::mouse_button_callback);
	glfwSetCursorPosCallback(m_window, Input::cursor_position_callback);

	//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	

	OrthographicCamera orthoCam(0.0f, 1200.0f, 0.0f, 1200.0f, 0.0f, 100.0f);
	PerspectiveCamera perspCam(3.1415f / 4.0f, width / height, 0.1f, 100.0f);
	MovablePerspCamera movablePerspCam(3.1415f / 4.0f, width / height, 0.1f, 100.0f);

	Shader shader("../Application/Resources/Shaders/spriteShaderV.shader", "../Application/Resources/Shaders/spriteShaderF.shader");
	Shader meshShader("../Application/Resources/Shaders/phongV.shader", "../Application/Resources/Shaders/phongF.shader");
	Shader meshTimeShader("../Application/Resources/Shaders/timeTestV.shader", "../Application/Resources/Shaders/timeTestF.shader");
	Shader textShader("../Application/Resources/Shaders/textShaderV.shader", "../Application/Resources/Shaders/textShaderF.shader");
	
	Texture foxTexture;
	Texture stoneTexture;
	Texture textureAtlas77;
	Texture glassTexture;
	BitmapFont font001(Vector2(12.0f, 20.0f));
	foxTexture.load("../Application/Resources/fox001.jpg");
	stoneTexture.load("../Application/Resources/rocks001.jpg");
	textureAtlas77.load("../Application/Resources/textAtlas77.jpg");
	glassTexture.load("../Application/Resources/glass.png");
	font001.load("../Application/Resources/font002.png");
	font001.unbind();



	SimpleSpriteRenderer renderer;
	SimpleMeshRenderer meshRenderer;
	SimpleTextRenderer textRenderer;
	


	Sprite sprite1(Vector3(600.0f, 400.0f, 0.0f), Vector2(10.0f, 10.0f));
	Sprite sprite2(Vector3(0.0f, 0.0f, -1.0f), Vector2(0.5f, 0.5f));



	Vector3 lightPosition = Vector3(0.0f, 1.0f, -1.4f);
	CubeMesh cube001(Vector3(0.5f, 0.5f, 0.5f));
	CubeMesh cube002(Vector3(0.5f, 0.5f, 0.5f));
	CubeMesh cube003(Vector3(0.1f, 0.1f, 0.1f));
	CubeMesh cube004(Vector3(1.0f, 1.0f, 1.0f));
	CubeMesh floor(Vector3(10.0f, 0.2f, 10.0f));
	SphereMesh sphere001(20, 20, 0.5f);
	sphere001.setPosition(Vector3(0.0f, 0.0f, 0.0f));;
	sphere001.addTexture(&foxTexture);
	cube001.addTexture(&glassTexture);
	cube002.addTexture(&textureAtlas77);
	floor.addTexture(&stoneTexture);
	cube004.addTexture(&foxTexture);
	cube001.setPosition(Vector3(-1.8f, 0.0f, 0.0f));
	cube002.setPosition(Vector3( 1.8f, 0.0f, 0.0f));
	floor.setPosition(Vector3(0.0f, -1.0f, 0.0f));
	cube004.setPosition(Vector3( 0.0f, 1.0f, -3.0f));
	cube002.setTextureCoord(CUBE_FACE::TOP, Vector2(1.0f, 1.0f) / 7.0f, Vector2(1.0f, 1.0f) / 7.0f);
	cube002.setTextureCoord(CUBE_FACE::FRONT, Vector2(5.0f, 2.0f) / 7.0f, Vector2(1.0f, 1.0f) / 7.0f);

	perspCam.setPosition(Vector3(0.0f, 0.0f, 3.4f));

	meshShader.bind();
	meshShader.setUniform3f("lightColor", Vector3(1.0f, 1.0f, 1.0f));
	meshTimeShader.bind();
	meshTimeShader.setUniform3f("lightColor", Vector3(1.0f, 1.0f, 1.0f));

	Text text001;
	text001.setFont(&font001);
	text001.setPosition(Vector3(0.0f, 800.0f - (20.0f + 2.0f) * 2.0f, 0.0f));
	//text001.setScale(Vector3(2.0f, 2.0f, 2.0f));

	movablePerspCam.setPosition(Vector3(0.0f, 0.0f, 4.0f));
	movablePerspCam.setFront(Vector3(0.0f, 0.0f, -1.0f));
	movablePerspCam.setUp(Vector3(0.0f, 1.0f, 0.0f));




	
	float dTime = 0.0f;
	float previousTime = 0.0f;
	float savedTime = 0.0f;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.3f, 1.0f, 1.0f);
	while (!glfwWindowShouldClose(m_window))
	{
		//escape closes application
		if (Input::isButtonPressed(KEY::ESC))
			glfwSetWindowShouldClose(m_window, GLFW_TRUE);

		//time handling
		dTime = glfwGetTime() - previousTime;
		previousTime = glfwGetTime();
		savedTime += dTime;
		if (savedTime > 0.2f)
		{
			//std::cout << dTime << "ms   " << 1.0f/dTime << "fps" << std::endl;
			text001.setText(std::to_string(1.0f / dTime) + "FPS\n" +std::to_string(dTime) + "ms");
			savedTime = 0.0f;
		}

		//vieport size adjusting
		int width, height;
		glfwGetFramebufferSize(m_window, &width, &height);
		if(width > height)
			glViewport(0, 0, width, width);
		else
			glViewport(0, 0, height, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		break;

		//camera movement and rotation
		float cameraSpeed = 10.0f * dTime;
		float cameraRotationSpeed = 0.8f * dTime;
		if (Input::isButtonPressed(KEY::W))
			movablePerspCam.moveFront(cameraSpeed);
		if (Input::isButtonPressed(KEY::S))
			movablePerspCam.moveFront(-cameraSpeed);
		if (Input::isButtonPressed(KEY::A))
			movablePerspCam.moveRight(-cameraSpeed);
		if (Input::isButtonPressed(KEY::D))
			movablePerspCam.moveRight(cameraSpeed);
		if (Input::isButtonPressed(KEY::SPACE))
			movablePerspCam.move(Vector3(0.0f, cameraSpeed, 0.0f));
		if (Input::isButtonPressed(KEY::LSHIFT))
			movablePerspCam.move(Vector3(0.0f, -cameraSpeed, 0.0f));

		Vector2 mouseMovement = Input::getMouseMovement();
		movablePerspCam.rotateX( mouseMovement.y * cameraRotationSpeed);
		movablePerspCam.rotateY(-mouseMovement.x * cameraRotationSpeed);



		

		//lightPosition += Vector3(0.0f, 0.0f, -0.002f);
		//cube003.setPosition(lightPosition);
		//meshShader.setUniform3f("lightPos", lightPosition);

		cube001.rotate(Vector3(0.0f, 1.0f, 0.0f), 3.1415f / 4.0f * dTime);
		cube002.rotate(Vector3(0.0f, 1.0f, 0.0f), 3.1415f / 4.0f * dTime);

		Vector3 tmpLightPosition = lightPosition;
		float angle = 3.1415f / 4.0f * dTime;
		lightPosition.x = lightPosition.x * cosf(angle) + lightPosition.z * sinf(angle);
		lightPosition.z = -tmpLightPosition.x * sinf(angle) + tmpLightPosition.z * cosf(angle);
		cube003.setPosition(lightPosition);
		
		//time test shader
		meshTimeShader.bind();
		meshTimeShader.setUniform3f("lightPos", lightPosition);
		meshTimeShader.setUniform3f("viewPos", movablePerspCam.getPosition());
		meshTimeShader.setUniform1f("time", previousTime);
		meshTimeShader.setUniform2f("screenSize", Vector2(m_width, m_height));
		meshRenderer.submit(cube004, meshTimeShader, movablePerspCam.getMatrix());

		//phong shader
		meshShader.bind();
		meshShader.setUniform3f("lightPos", lightPosition);
		meshShader.setUniform3f("viewPos", movablePerspCam.getPosition());
		meshRenderer.submit(cube002,   meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(cube003,   meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(floor,     meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(sphere001, meshShader, movablePerspCam.getMatrix());		
		meshRenderer.submit(cube001,   meshShader, movablePerspCam.getMatrix());

		//sprites
		renderer.submit(sprite1, shader, orthoCam.getMatrix());

		//text
		textRenderer.submit(text001, textShader, orthoCam.getMatrix());





		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}

	//glfwDestroyWindow(m_window);
	//glfwTerminate();
}
Window::~Window()
{
	glfwDestroyWindow(m_window);
}

bool Window::isOpen() const
{
	return glfwWindowShouldClose(m_window);
}
void Window::close()
{
	glfwDestroyWindow(m_window);
}
void Window::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(m_window, shouldClose);
}
bool Window::shouldClose()
{
	return glfwWindowShouldClose(m_window);
}

void Window::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::pollEvents()
{
	glfwPollEvents();
}
void Window::swapBuffers()
{
	glfwSwapBuffers(m_window);
}

float Window::getAspectRatio()
{
	return m_width / m_height;
}
