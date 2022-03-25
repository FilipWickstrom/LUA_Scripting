#include "PCH.h"
#include "Renderer.h"

// Run the console
void ConsoleThread(lua_State* L)
{
	char command[1000];
	while (GetConsoleWindow())
	{
		memset(command, 0, 1000);
		std::cin.getline(command, 1000);
		if (luaL_loadstring(L, command) || lua_pcall(L, 0, 0, 0))
			std::cout << lua_tostring(L, -1) << '\n';
	}
}

Renderer::Renderer()
{
	//Superweird, only works when m_sceneHandler exist in Renderer
	SceneAccess::SetSceneHandler(&m_sceneHandler);
	SceneAccess::GetSceneHandler()->SetScene(EScene::Menu);

#ifdef _DEBUG
	m_conThread = std::thread(ConsoleThread, LUA);
#endif // _DEBUG
}

Renderer::~Renderer()
{
#ifdef _DEBUG
	m_conThread.join();
#endif // _DEBUG
}

bool Renderer::Update()
{
	Input::CheckKeyboard();

	//Update all the objects in the scene
	SceneAccess::GetSceneHandler()->UpdateScene();
	
	//Return false when we switch scene to none
	return (SceneAccess::GetSceneHandler()->GetSceneType() == EScene::None ? false : true);
}

void Renderer::Render()
{
	Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

	Graphics::GetSceneManager()->drawAll();
	Graphics::GetGUIEnvironment()->drawAll();
	Graphics2D::Draw();

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
		
		if (this->Update())
			this->Render();
		else
			Graphics::GetDevice()->closeDevice();

		end = omp_get_wtime() - start;
	}
}
