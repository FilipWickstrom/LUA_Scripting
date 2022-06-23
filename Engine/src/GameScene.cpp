#include "PCH.h"
#include "GameScene.h"

void GameScene::Load()
{
	//Read the lua-script
	LoadScript("GameScene.lua");
	//ez

	lua_getglobal(LUA, "Start");
	LuaHandler::CheckErrors(0, 0);

	//Read the scene basics from a file
	//Read the map
}

void GameScene::Clean()
{
	lua_getglobal(LUA, "Clean");
	LuaHandler::CheckErrors(0, 0);
}

void GameScene::Update()
{
	//Update from lua-scrips
	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	LuaHandler::CheckErrors(1, 0);
}
