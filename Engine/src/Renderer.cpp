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
#ifdef _DEBUG
	m_conThread = std::thread(ConsoleThread, LUA);
#endif // _DEBUG

	SceneHandler::LoadStartScene();
}

Renderer::~Renderer()
{
#ifdef _DEBUG
	m_conThread.join();
#endif // _DEBUG
}

void Renderer::Update()
{
	SceneHandler::UpdateScene();
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
		
		this->Update();
		this->Render();

		//Update window caption text
		Graphics::UpdateWindowCaption();
	}

	std::cout << "Application closed down. Dumping LUA stack: " << std::endl;
	LuaHandler::DumpStack();
	std::cout << "Close console with the command 'stop'" << std::endl;
}
