#include "PCH.h"
#include "Renderer.h"

// Run the console
void ConsoleThread(lua_State* L)
{
	std::string command = "";
	bool keepLooping = true;
	
	while (keepLooping)
	{
		std::cout << "> ";
		std::getline(std::cin, command);

		if (command == "stop")
		{
			keepLooping = false;
			break;
		}

		if (luaL_dostring(L, command.c_str()) != LUA_OK)
		{
			if (lua_gettop(L) && lua_isstring(L, -1))
			{
				std::cout << "Lua error: " << lua_tostring(L, -1) << '\n';
				lua_pop(L, 1);
			}
		}
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
	
	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::high_resolution_clock::time_point lastTime;
	float deltaTime = 0.f;

	while (Graphics::GetDevice()->run()) 
	{
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;

		Graphics::GetDeltaTime() = deltaTime;
		if (this->Update())
			this->Render();
		else
			Graphics::GetDevice()->closeDevice();

		//Update window caption text
		Graphics::UpdateWindowCaption();
	}

	std::cout << "Application closed down. Dumping LUA stack: " << std::endl;
	LuaHandler::DumpStack();
	std::cout << "Close console with the command 'stop'" << std::endl;
}
