#include "PCH.h"
#include "Renderer.h"

Renderer::Renderer()
{
	//Superweird, only works when m_sceneHandler exist in Renderer
	SceneAccess::SetSceneHandler(&m_sceneHandler);
	
	//[TODO]: Always start in menu
	SceneAccess::GetSceneHandler()->SetScene(EScene::Game);
}

Renderer::~Renderer()
{
}

void Renderer::Update()
{
	Input::CheckKeyboard();

	//Update all the objects in the scene
	SceneAccess::GetSceneHandler()->UpdateScene();
}

void Renderer::Render()
{
	Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

	Graphics::GetSceneManager()->drawAll();
	Graphics::GetGUIEnvironment()->drawAll();

	Graphics::GetDriver()->endScene();
}

void Renderer::Run()
{
	srand((unsigned int)time(nullptr));
	double start = omp_get_wtime();
	double end = omp_get_wtime() - start;

	while (Graphics::GetDevice()->run()) 
	{
		start = omp_get_wtime();
		Graphics::GetDeltaTime() = end;
		
		this->Update();
		this->Render();
		
		end = omp_get_wtime() - start;
	}
}
