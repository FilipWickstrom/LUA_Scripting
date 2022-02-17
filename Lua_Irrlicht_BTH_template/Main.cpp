#include "LuaHandler.h"
#include "Graphics.h"
#include "Model.h"
#include "SceneManager.h"

int main()
{
	SceneManager sceneManager;
	Scene* testScene = sceneManager.GetScene(0);

	srand((unsigned int)time(nullptr));

	while(Graphics::GetDevice()->run()) {
		Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

		Graphics::GetSceneManager()->drawAll();
		Graphics::GetGUIEnvironment()->drawAll();

		Graphics::GetDriver()->endScene();		
	}

	return 0;
}