#include "Window.hpp"

#include <iostream>

#include "Input.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Shader.hpp"
#include "Texture.hpp"

#include "SimpleSpriteRenderer.hpp"
#include "SimpleMeshRenderer.hpp"

#include "OrthographicCamera.hpp"
#include "PerspectiveCamera.hpp"
#include "MovablePerspCamera.hpp"

#include "CubeMesh.hpp"

#include "Quaternion.hpp"

struct Vertex
{
	Vertex(Vector2 position, size_t something, Vector4 color)
		:position(position), something(something), color(color)
	{

	}

	Vector2 position;
	size_t something;
	Vector4 color;
};

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

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);




	OrthographicCamera orthoCam(0.0f, 800.0f, 0.0f, 800.0f, 0.0f, 100.0f);
	PerspectiveCamera perspCam(3.1415f / 4.0f, width / height, 0.1f, 100.0f);
	MovablePerspCamera movablePerspCam(3.1415f / 4.0f, width / height, 0.1f, 100.0f);

	Shader shader("../Application/Resources/Shaders/spriteShaderV.shader", "../Application/Resources/Shaders/spriteShaderF.shader");
	shader.bind();
	Shader meshShader("../Application/Resources/Shaders/phongV.shader", "../Application/Resources/Shaders/phongF.shader");
	Shader meshTimeShader("../Application/Resources/Shaders/timeTestV.shader", "../Application/Resources/Shaders/timeTestF.shader");
	
	Texture texture;
	Texture texture2;
	Texture texture3;
	texture.load("../Application/Resources/fox001.jpg");
	texture2.load("../Application/Resources/rocks001.jpg");
	texture3.load("../Application/Resources/textAtlas77.jpg");
	texture3.unbind();



	SimpleSpriteRenderer renderer;
	Sprite sprite1(Vector3(400.0f, 400.0f, -1.0f), Vector2(500.0f, 500.0f));
	Sprite sprite2(Vector3(0.0f, 0.0f, -1.0f), Vector2(0.5f, 0.5f));



	Vector3 lightPosition = Vector3(0.0f, 1.0f, -1.4f);
	SimpleMeshRenderer meshRenderer;
	CubeMesh cube001(Vector3(0.5f, 0.5f, 0.5f));
	CubeMesh cube002(Vector3(0.5f, 0.5f, 0.5f));
	CubeMesh cube003(Vector3(0.1f, 0.1f, 0.1f));
	CubeMesh cube004(Vector3(1.0f, 1.0f, 1.0f));
	CubeMesh floor(Vector3(10.0f, 0.2f, 10.0f));
	cube001.addTexture(&texture);
	cube002.addTexture(&texture3);
	floor.addTexture(&texture2);
	cube004.addTexture(&texture);
	cube001.setPosition(Vector3(-0.8f, 0.0f, 0.0f));
	cube002.setPosition(Vector3( 0.8f, 0.0f, 0.0f));
	floor.setPosition(Vector3(0.0f, -1.0f, 0.0f));
	cube004.setPosition(Vector3( 0.0f, 1.0f, -3.0f));
	cube002.setTextureCoord(CUBE_FACE::TOP, Vector2(1.0f, 1.0f) / 7.0f, Vector2(1.0f, 1.0f) / 7.0f);
	cube002.setTextureCoord(CUBE_FACE::FRONT, Vector2(5.0f, 2.0f) / 7.0f, Vector2(1.0f, 1.0f) / 7.0f);

	perspCam.setPosition(Vector3(0.0f, 0.0f, 3.4f));

	meshShader.bind();
	meshShader.setUniform3f("objectColor", Vector3(1.0f, 1.0f, 1.0f));
	meshShader.setUniform3f("lightColor", Vector3(1.0f, 1.0f, 1.0f));
	meshTimeShader.bind();
	meshTimeShader.setUniform3f("objectColor", Vector3(0.5f, 0.0f, 0.0f));
	meshTimeShader.setUniform3f("lightColor", Vector3(1.0f, 1.0f, 1.0f));

	movablePerspCam.setPosition(Vector3(0.0f, 0.0f, 4.0f));
	movablePerspCam.setFront(Vector3(0.0f, 0.0f, -1.0f));
	movablePerspCam.setUp(Vector3(0.0f, 1.0f, 0.0f));




	
	float dTime = 0.0f;
	float previousTime = 0.0f;
	float savedTime = 0.0f;
	glEnable(GL_DEPTH_TEST);
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
		if (savedTime > 0.4f)
		{
			std::cout << dTime << "ms   " << 1.0f/dTime << "fps" << std::endl;
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

		cube001.rotate(Vector3(0.0f, 3.1415f / 4.0f, 0.0f) * dTime);
		cube002.rotate(Vector3(0.0f, 3.1415f / 6.0f, 0.0f) * dTime);

		Vector3 tmpLightPosition = lightPosition;
		float angle = 3.1415f / 4.0f * dTime;
		lightPosition.x = lightPosition.x * cosf(angle) + lightPosition.z * sinf(angle);
		lightPosition.z = -tmpLightPosition.x * sinf(angle) + tmpLightPosition.z * cosf(angle);
		cube003.setPosition(lightPosition);
		
		//phong shader
		meshShader.bind();
		meshShader.setUniform3f("lightPos", lightPosition);
		meshShader.setUniform3f("viewPos", movablePerspCam.getPosition());
		meshRenderer.submit(cube001, meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(cube002, meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(cube003, meshShader, movablePerspCam.getMatrix());
		meshRenderer.submit(floor,   meshShader, movablePerspCam.getMatrix());
		
		//time test shader
		meshTimeShader.bind();
		meshTimeShader.setUniform3f("lightPos", lightPosition);
		meshTimeShader.setUniform3f("viewPos", movablePerspCam.getPosition());
		meshTimeShader.setUniform1f("time", previousTime);
		meshTimeShader.setUniform2f("screenSize", Vector2(m_width, m_height));
		meshRenderer.submit(cube004, meshTimeShader, movablePerspCam.getMatrix());





		glfwSwapBuffers(m_window);

		glfwPollEvents();
	}

	glfwDestroyWindow(m_window);
	glfwTerminate();
}
Window::~Window()
{
	glfwTerminate();
}
