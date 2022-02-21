#include "Game.h"
#include <iostream>

void Game::Update()
{

}

Game::Game()
{
	LuaHandler::LoadScript("SpawnScript.lua");
	m_currentScene = m_sceneManager.GetScene(0);
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
