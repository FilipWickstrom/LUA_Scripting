#include "PCH.h"
#include "Renderer.h"

// Run the console
void ConsoleThread()
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


		if (luaL_dostring(LUA, command.c_str()) != LUA_OK)
		{
			if (lua_gettop(LUA) && lua_isstring(LUA, -1))
			{
				std::cout << "Lua error: " << lua_tostring(LUA, -1) << '\n';
				lua_pop(LUA, 1);
			}
		}
	}
}

Renderer::Renderer()
{
#ifdef _DEBUG
	m_conThread = std::thread(ConsoleThread);
#endif // _DEBUG

	SceneHandler::LoadStartScene();
}

Renderer::~Renderer()
{
#ifdef _DEBUG
	m_conThread.join();
#endif // _DEBUG
}

void Renderer::Run()
{
	srand((unsigned int)time(nullptr));
	
	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::high_resolution_clock::time_point lastTime;
	float deltaTime = 0.f;

	while (Graphics::GetDevice()->run()) 
	{
		//Handle delta time
		currentTime = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		Graphics::GetDeltaTime() = deltaTime;


		Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 34, 34, 34));
		
		//Update the scene from LUA
		SceneHandler::UpdateScene();
		Graphics::UpdateWindowCaption();

		//Render everything to the screen
		Graphics::GetSceneManager()->drawAll();
		Graphics::GetGUIEnvironment()->drawAll();
		Graphics2D::Draw();
		Graphics2D::AlwaysDraw();

		Graphics::GetDriver()->endScene();
	}

	std::cout << "Application closed down. Dumping LUA stack: " << std::endl;
	LuaHandler::DumpStack();
	std::cout << "Close console with the command 'stop'" << std::endl;
}
