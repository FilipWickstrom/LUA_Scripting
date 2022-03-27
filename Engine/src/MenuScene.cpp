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
	lua_pcall(LUA, 0, 0, 0);
	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";	
}

void MenuScene::Clean()
{
	//Execute the start-function
	lua_getglobal(LUA, "Clean");
	lua_pcall(LUA, 0, 0, 0);
	if (lua_isstring(LUA, -1))
		std::cout << "Error: " << lua_tostring(LUA, -1) << "\n";
}

void MenuScene::Update()
{
	lua_getglobal(LUA, "Update");
	lua_pcall(LUA, 0, 0, 0);
}
