#include "PCH.h"
#include "MenuScene.h"

/*
	[TODO] Add options if we got time
*/

void MenuScene::Load()
{
	//Read the lua-script
	LoadScript("MenuScene.lua");

	//Execute the start-function
	lua_getglobal(LUA, "Start");
	LuaHandler::CheckErrors(0, 0);
}

void MenuScene::Clean()
{
	//Execute the start-function
	lua_getglobal(LUA, "Clean");
	LuaHandler::CheckErrors(0, 0);
}

void MenuScene::Update()
{
	lua_getglobal(LUA, "Update");
	lua_pushnumber(LUA, Graphics::GetDeltaTime());
	LuaHandler::CheckErrors(1, 0);
}
