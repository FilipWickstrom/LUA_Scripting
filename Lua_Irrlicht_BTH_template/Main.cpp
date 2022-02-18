#include "LuaHandler.h"
#include "Graphics.h"
#include "Model.h"
#include "SceneManager.h"

int main()
{
	SceneManager sceneManager;
	Scene* testScene = sceneManager.GetScene(0);
	testScene->AddObject("shitty_tree.obj", { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 1.0f });

	srand((unsigned int)time(nullptr));

	while(Graphics::GetDevice()->run()) {
		// First begin draw.
		Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

		Graphics::GetSceneManager()->drawAll();
		Graphics::GetGUIEnvironment()->drawAll();


		// Update on CPU while the GPU is busy drawing.
		testScene->Update();
		Graphics::GetDriver()->endScene();	
	}

	return 0;
}