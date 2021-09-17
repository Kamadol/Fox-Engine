#include <iostream>

#include "MeshesScene.hpp"
#include "NormalMappingScene.hpp"
#include "RayMarchingScene.hpp"
#include "MinecraftScene.hpp"

int main()
{
    Window window(1200, 800);
    //Window window(1920, 1080);
    SceneManager sceneManager;

    //scene
    MeshesScene meshesScene(&window, "meshesScene");
	meshesScene.setSceneManager(&sceneManager);

    //scene
    NormalMappingScene normalMappingScene(&window, "normalMappingScene");
    normalMappingScene.setSceneManager(&sceneManager);

    //scene
    RayMarchingScene rayMarchingScene(&window, "rayMarchingScene");
    rayMarchingScene.setSceneManager(&sceneManager);
    
    //scene
    MinecraftScene minecraftScene(&window, "minecraftScene");
    minecraftScene.setSceneManager(&sceneManager);



    sceneManager.addScene(&meshesScene);
    sceneManager.addScene(&normalMappingScene);
    sceneManager.addScene(&rayMarchingScene);
    sceneManager.addScene(&minecraftScene);

    sceneManager.changeScene("meshesScene");
    //sceneManager.changeScene("normalMappingScene");
    //sceneManager.changeScene("rayMarchingScene");
    sceneManager.changeScene("minecraftScene");

    while (!sceneManager.shouldClose())
    {
        sceneManager.update();
    }





    //glfwTerminate();
    return 0;
}
