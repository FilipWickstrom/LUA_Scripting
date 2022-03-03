#include "PCH.h"
#include "Game.h"

void Game::Update()
{
	Input::CheckKeyboard();

	m_currentScene->Update();

	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	lua_pcall(LUA, 1, 1, 0);
	int lua_return = static_cast<int>(lua_tonumber(LUA, -1));
	lua_pop(LUA, 1);

	if (lua_return == true)
	{
		// Player died.
		printf("DED");
	}
}

Game::Game()
{
	LuaHandler::LoadScript("gameLoop.lua");
	lua_getglobal(LUA, "Start");
	lua_pcall(LUA, 0, 0, 0);
	m_currentScene = m_sceneManager.GetScene(0);
	m_currentScene->AddBasicEnemy(0, 0);
	m_currentScene->AddBasicEnemy(3, 1);
	m_currentScene->AddBasicEnemy(6, 1);
	m_currentScene->AddBasicEnemy(9, 1);


	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";

	//lua_getglobal(LUA, "getMonsters");
	//lua_pcall(LUA, 0, 4, 0);

	DumpStack(LUA);
}

void Game::Run()
{
	// First begin draw.
	Graphics::GetDriver()->beginScene(true, true, irr::video::SColor(255, 90, 101, 140));

	Graphics::GetSceneManager()->drawAll();
	Graphics::GetGUIEnvironment()->drawAll();

	this->Update();

	Graphics::GetDriver()->endScene();
}
