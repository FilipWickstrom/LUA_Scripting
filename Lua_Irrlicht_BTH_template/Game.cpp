#include "Game.h"
#include <iostream>

void Game::Update()
{
	m_currentScene->Update();
}

Game::Game()
{
	LuaHandler::LoadScript("gameLoop.lua");
	m_currentScene = m_sceneManager.GetScene(0);
	m_currentScene->AddBasicEnemy(0, 0);
	m_currentScene->AddBasicEnemy(3, 1);
	m_currentScene->AddBasicEnemy(6, 1);
	m_currentScene->AddBasicEnemy(9, 1);

	//if (lua_isstring(LUA, -2))
	//	std::cout << "Error: " << lua_tostring(LUA, -2) << "\n";

	lua_getglobal(LUA, "getMonsters");
	lua_pcall(LUA, 0, 4, 0);

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
