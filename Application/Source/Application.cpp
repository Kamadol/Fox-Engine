#include <iostream>

#include "MeshesScene.hpp"
#include "NormalMappingScene.hpp"
#include "RayMarchingScene.hpp"
#include "MinecraftScene.hpp"

int main()
{
    Window window(1200, 800);
    //Window window(1920, 1080);
    SceneManager sceneManager(&window);
    GUILayer GUI;

    MeshesScene meshesScene(&window, "meshesScene");
    NormalMappingScene normalMappingScene(&window, "normalMappingScene");
    RayMarchingScene rayMarchingScene(&window, "rayMarchingScene");
    MinecraftScene minecraftScene(&window, "minecraftScene");

    sceneManager.addScene(&meshesScene);
    sceneManager.addScene(&normalMappingScene);
    sceneManager.addScene(&rayMarchingScene);
    sceneManager.addScene(&minecraftScene);

    sceneManager.changeScene("meshesScene");
    sceneManager.changeScene("normalMappingScene");
    sceneManager.changeScene("minecraftScene");
    sceneManager.changeScene("rayMarchingScene");

    while (!sceneManager.shouldClose())
    {
        //updating
        sceneManager.update();
        GUI.setDeltaTime(sceneManager.getDeltaTime());
        GUI.update();

        //rendering
        sceneManager.startDrawing();

        sceneManager.draw();
        GUI.draw();

        sceneManager.endDrawing();
    }

    


    /*
    Text text1 = "0123456789";
    text1.setFont(font);
    text1.setFontSize(50);
    
    
    
    */







    //glfwTerminate();
    return 0;
}
